
#include <math.h>
#include <Rcpp.h>
#include "R_ext/Applic.h"
#include "lbfgsKernel.h"

using namespace Rcpp;

// DECLARE FUNCTIONS
double objfunList(int n, double *x, int funIdx);
lbfgsfloatval_t evaluate(void *ex, const lbfgsfloatval_t *x, lbfgsfloatval_t *g, 
												 const int n, const lbfgsfloatval_t step);
double fminfn(int n, double *par, void *ex);			
void fmingr(int n, double *par, lbfgsfloatval_t *gr, void *ex);

// DEFINE STUCTURES
typedef struct {
  int funIdx;
} OPTIM_EX, *Ptr_OPTIM_EX;

// RCPP FUNCTIONS
//[[Rcpp::export]]
double objfun_cpp(NumericVector x, int funIdx)
{
	int n = x.size();
	double par[n];
	for (int i = 0; i < n; i++) par[i] = x[i];
  return objfunList(n, par, funIdx);
}

//[[Rcpp::export]]
List optim_cpp(NumericVector iniVal, int funIdx, std::string method, int maxit,
							 NumericVector lowerInput, NumericVector upperInput, NumericVector nbdInput) 
{
	int n = iniVal.size();
	double par[n], par_in[n];
	for (int i = 0; i < n; i++) { par[i] = iniVal[i]; par_in[i] = iniVal[i]; }
	OPTIM_EX ex = {}; ex.funIdx = funIdx;
	
	double Fmin;
	int trace = 0; int nREPORT = 10;
	int fail, fncount, grcount;
	double abstol = 1e-6; double reltol = 1e-8;
	
	if (method == "Nelder-Mead") {
		
		double alpha = 1.0; double beta = 0.5; double gamma = 2.0;
		
		nmmin(n, par_in, par, &Fmin, fminfn, &fail, abstol, reltol, 
	   &ex, alpha, beta, gamma, trace, &fncount, maxit);
		 
	} else if (method == "BFGS") {
		
		int mask[n]; for (int i = 0; i < n; i++) mask[i] = 1;
		
		vmmin(n, par, &Fmin, fminfn, fmingr, maxit, trace, mask, 
	   abstol, reltol, nREPORT, &ex, &fncount, &grcount, &fail);
		 
	} else if (method == "L-BFGS-B") {
		
		int lmm = 5; double pgtol = 1e-7; double factr = 1e7; char msg[60]; 
		double lower[n], upper[n]; int nbd[n];
		for (int i = 0; i < n; i++) {
		  lower[i] = lowerInput[i]; upper[i] = upperInput[i]; nbd[i] = nbdInput[i];
		}
		
		lbfgsb(n, lmm, par, lower, upper, nbd, &Fmin, fminfn, fmingr, &fail, 
	    &ex, factr, pgtol, &fncount, &grcount, maxit, msg, trace, nREPORT);
			
	}
	Rcpp::NumericVector outPar(n);
	for (int i = 0; i < n; i++) outPar(i) = par[i];
	
	return List::create(Named("par") = wrap(outPar),
                      Named("value") = wrap(Fmin),
                      Named("conv") = wrap(fail));
}

//[[Rcpp::export]]
List optim_cpp_lbfgs(NumericVector iniVal, int funIdx)
{
	int n = iniVal.size();
	lbfgsfloatval_t *par = lbfgs_malloc(n);
	for (int i = 0; i < n; i++) par[i] = iniVal[i];

	OPTIM_EX ex = {}; ex.funIdx = funIdx;
	
	lbfgs_parameter_t LBFGS_PAR;
	lbfgs_parameter_init(&LBFGS_PAR);
	LBFGS_PAR.epsilon = 1e-10; // default 1e-5
	LBFGS_PAR.gtol = 1e-1; // default 0.9
	LBFGS_PAR.ftol = 1e-6; // default 1e-4
	LBFGS_PAR.delta = 1e-6; // default 0
	
  lbfgsfloatval_t fx;
  int ret;
  ret = lbfgs(n, par, &fx, evaluate, NULL, &ex, &LBFGS_PAR);
	
	Rcpp::NumericVector outPar(n);
	for (int i = 0; i < n; i++) outPar(i) = par[i];
	
	lbfgs_free(par);
	
	return List::create(Named("par") = wrap(outPar),
                      Named("value") = wrap(fx),
                      Named("conv") = wrap(ret));
}

// BODY
double objfunList(int n, double *x, int funIdx)
{
	double out = 0;
	switch (funIdx) {
		case 0: {
			double p1 = (x[0] + 2*x[1] - 7);
			double p2 = (2*x[0] + x[1] - 5);
			out = p1*p1 + p2*p2;
			break;
		}
		case 1: {
			out = 0.26*(x[0]*x[0] + x[1]*x[1]) - 0.48*x[0]*x[1];
			break;
		}
		case 2: {
			for (int i = 0; i < n; i++) { out += x[i]*x[i]; }
			break;
		}
	}
  return out;
}

lbfgsfloatval_t evaluate(void *ex, const lbfgsfloatval_t *x, lbfgsfloatval_t *g, 
												 const int n, const lbfgsfloatval_t step)
{
	lbfgsfloatval_t fx = fminfn(n, (double*)x, ex);
	fmingr(n, (double*)x, g, ex);
  return fx;
}

// ====== The Objective function used in Quasi-Newton Algorithm ====== //
double fminfn(int n, double *par, void *ex)
{
  OPTIM_EX exList = *(OPTIM_EX*)(ex);
	return objfunList(n, par, exList.funIdx);
}	
		
// ====== The Gradient function used in Quasi-Newton Algorithm ====== //
void fmingr(int n, double *par, lbfgsfloatval_t *gr, void *ex) 
{
  double par1[n], par0[n];
  double fv, bv;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) { par1[j] = par[j]; par0[j] = par[j]; }
    par1[i] = par1[i] + 1e-3; par0[i] = par0[i] - 1e-3;
    //central difference method
    fv = fminfn(n, par1, ex); bv = fminfn(n, par0, ex);
    gr[i] = (fv - bv)*2e3; 
  }
} 
