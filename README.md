# A demo of Accelerated optimization coding in R by using Rcpp and related C library

### Preliminary
R Package reauired: Rcpp, rbenchmark

Three objective functions are used here which is controlled by `funIdx` in `objfun_r` and `objfun_cpp`.  Please refer to https://en.wikipedia.org/wiki/Test_functions_for_optimization
+ `funIdx = 0`: Booth's function
+ `funIdx = 1`: Matyas function
+ `funIdx = 2`: Sphere function



Thanks to the open source library, libLBFGS, provided by Naoaki Okazaki (http://www.chokkan.org/software/liblbfgs/)
