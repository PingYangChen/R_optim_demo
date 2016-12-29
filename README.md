# A demo of Accelerated optimization coding in R by using Rcpp and related C library

### Preliminary
R Package reauired: Rcpp, rbenchmark

Three objective functions are used here which is controlled by \code{funIdx} in \code{objfun_r} and \code{objfun_cpp}.
+ 0: Booth's function: $f(x,y)=(x + 2y -7)^2+(2x + y -5)^2$
+ 1: Matyas function: $0.26(x^2+y^2)-0.48xy$
+ 2: Sphere function: $\sum_{i=1}^n x_i^2$



Thanks to the open source library, libLBFGS, provided by Naoaki Okazaki (http://www.chokkan.org/software/liblbfgs/)
