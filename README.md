# A demo of Accelerated optimization coding in R by using Rcpp and related C library

### Preliminary

R Package reauired: **Rcpp**, **rbenchmark**

### Demonstration

The main file is **optim_demo.r**.  Please make sure that you have specified the correct file path in `sourceCpp("optim_demo.cpp", verbose = F)`.

Three objective functions are used here which is controlled by `funIdx` in `objfun_r` and `objfun_cpp`.  Please refer to https://en.wikipedia.org/wiki/Test_functions_for_optimization.

+ `funIdx = 0`: Booth's function (2 dimensional problem)
+ `funIdx = 1`: Matyas function (2 dimensional problem)
+ `funIdx = 2`: Sphere function (n dimensional problem)

Four coding methods are demonstrated.

1. **OBJ_R**: Regular `optim` function with objective function written in **R**.
2. **OBJ_Cpp**: Regular `optim` function with objective function written in **C++**.  One can find the codes of this objective function, `objfun_cpp`, in **optim_demo.cpp**.
3. **OPTIM_Cpp**: Optimization using **Rcpp** and `optim` **C** interfaces (defined in header R_ext/Applic.h).  I only used three of the interfaces which can be found in **optim_demo.cpp** (`optim_cpp`).  There are more and the coding is similar.  For more information, please refer to
https://cran.r-project.org/doc/manuals/r-release/R-exts.html#Optimization.
4. **libLBFGS**: Optimization using **Rcpp** and **libLBFGS** library.  The codes can be found in `optim_cpp_lbfgs` in the file **optim_demo.cpp**.  One needs to include the header file **lbfgsKernel.h**.  To make the library available for **Rcpp**, please put `#include<Rcpp.h>` in the file **lbfgsKernel.c**.

###Comparison
A: exactly, B: kind of, C: haha no

| Method        | Easy-to-code | Fast | 
| ------------- | ------------ | ---- |
| **OBJ_R**     | A | C |
| **OBJ_Cpp**   | B | B |
| **OPTIM_Cpp** | C | A |
| **libLBFGS**  | C | A |

Thanks to the open source library, **libLBFGS**, provided by Naoaki Okazaki (http://www.chokkan.org/software/liblbfgs/)
