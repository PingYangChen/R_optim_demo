
library(Rcpp)
library(rbenchmark)

sourceCpp("optim_demo.cpp", verbose = F)
# Booth's function
objfun_r <- function(x, funIdx) {
	out <- switch(funIdx,
		"0" = (x[1] + 2*x[2] - 7)^2 + (2*x[1] + x[2] - 5)^2,
		"1" = 0.26*(x[1]^2 + x[2]^2) - 0.48*x[1]*x[2],
		"2" = sum(x^2)
	)
	out
}

fid <- 0
# initial value
ini_x <- runif(2)
benchmark(
	# Method 1
	OBJ_R = optim(ini_x, objfun_r, funIdx = as.character(fid), method = "L-BFGS-B"),
	# Method 2
	OBJ_Cpp = optim(ini_x, objfun_cpp, funIdx = fid, method = "L-BFGS-B"),
	# Method 3
	OPTIM_Cpp = optim_cpp(ini_x, fid, "L-BFGS-B", 100, -c(Inf, Inf), c(Inf, Inf), c(0,0)),
	# Method 4
	libLBFGS  = optim_cpp_lbfgs(ini_x, fid),
	replications = 10000, order = "elapsed"
)

fid <- 1
# initial value
ini_x <- runif(2)
benchmark(
	# Method 1
	OBJ_R = optim(ini_x, objfun_r, funIdx = as.character(fid), method = "L-BFGS-B"),
	# Method 2
	OBJ_Cpp = optim(ini_x, objfun_cpp, funIdx = fid, method = "L-BFGS-B"),
	# Method 3
	OPTIM_Cpp = optim_cpp(ini_x, fid, "L-BFGS-B", 100, -c(Inf, Inf), c(Inf, Inf), c(0,0)),
	# Method 4
	libLBFGS  = optim_cpp_lbfgs(ini_x, fid),
	replications = 10000, order = "elapsed"
)

fid <- 2
# initial value
ini_x <- runif(5)
benchmark(
	# Method 1
	OBJ_R = optim(ini_x, objfun_r, funIdx = as.character(fid), method = "L-BFGS-B"),
	# Method 2
	OBJ_Cpp = optim(ini_x, objfun_cpp, funIdx = fid, method = "L-BFGS-B"),
	# Method 3
	OPTIM_Cpp = optim_cpp(ini_x, fid, "L-BFGS-B", 100, -c(Inf, Inf), c(Inf, Inf), c(0,0)),
	# Method 4
	libLBFGS  = optim_cpp_lbfgs(ini_x, fid),
	replications = 10000, order = "elapsed"
)


