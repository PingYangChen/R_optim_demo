# A demo of Accelerated optimization coding in R by using Rcpp and related C library

### Preliminary
R Package reauired: Rcpp, rbenchmark

Three objective functions are used here which is controlled by `funIdx` in `objfun_r` and `objfun_cpp`.  Please refer to https://en.wikipedia.org/wiki/Test_functions_for_optimization.
+ `funIdx = 0`: Booth's function (2 dimensional problem)
+ `funIdx = 1`: Matyas function (2 dimensional problem)
+ `funIdx = 2`: Sphere function (n dimensional problem)

Four coding methods are demonstrated.
+ Regular `optim` function with objective function written in **R**.
+ Regular `optim` function with objective function written in **C++**.
+ Optimization using **Rcpp** and `optim` **C** interfaces (defined in header R_ext/Applic.h).  I only used three of the interfaces.  There are more and the coding is similar.  For more information, please refre to
https://cran.r-project.org/doc/manuals/r-release/R-exts.html#Optimization.
+ Optimization using **Rcpp** and **libLBFGS** library.  To make the library available for **Rcpp**, please put `#include<Rcpp.h>` in the file **lbfgsKernel.c**.

Thanks to the open source library, libLBFGS, provided by Naoaki Okazaki (http://www.chokkan.org/software/liblbfgs/)
