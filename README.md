# fdakmapp
The fdakmapp package provides the kmap function that jointly performs clustering and alignment of a functional 
dataset (multidimensional or unidimensional). The centers can be computed by mean and medoid center methods.
Many options are available and also the parallal version.

## Getting Started
The package can be cloned and downloaded directly from github.
An R studio project file is provided to open the project in RStudio.

### Prerequisites

The package is linked against OpenMP, the BLAS and LAPACK libraries, to use RcppArmadillo, in Makevars.

To install the package locally the packages Rcpp and RcppArmadillo needs to be installed.
Using install_github() will install the dependencies (Rcpp and RcppArmadillo) automatically.

### Installing

The package can be installed directly from github but devtools is required.

```
install.packages(devtools)
library(devtools)
install_github('zitale/fdakmapp')
```

### Automatic tests

```
devtools::test()
```
### Example

```
res<-kmap(x=aneurisk65$x, y=aneurisk65$y, n_clust=2)
kmap_show_results(res,FALSE)
```

## Documentation

The R documentation can be found in the main directory in fdakmapp.pdf.
The C++ documentation can be found at https://zitale.github.io/fdakmapp/.