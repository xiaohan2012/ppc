#include <iostream>
#include <math.h>
#include "stdlib.h"
using namespace std;

/*
This is the function you need to implement. Quick reference:
- input rows: 0 <= y < ny
- input columns: 0 <= x < nx
- element at row y and column x is stored in data[x + y*nx]
- correlation between rows i and row j has to be stored in result[i + j*ny]
- only parts with 0 <= j <= i < ny need to be filled
*/
void correlate(int ny, int nx, const float *data_, float *result) {
  double* data = (double*) malloc(nx*ny * sizeof(double));

  for(int y=0; y<ny; y++){
    double sum = 0, sum_sq = 0, mean, sum_sq_sqrt;
    for(int x=0; x<nx; x++){
      sum += data_[y*nx + x];      
    }
    // normalization: zero-mean    
    mean = sum / (double) nx;
    // std::cout << "mean of row " << y << " is " << mean << "\n";
    for(int x=0; x<nx; x++){
      data[y*nx + x] = data_[y*nx + x] - mean;
      sum_sq += (data[y*nx + x] * data[y*nx + x]);
    }
    sum_sq_sqrt = sqrt(sum_sq);
    // normalization: unit-norm
    for(int x=0; x<nx; x++){
      data[y*nx + x] /= sum_sq_sqrt;
    }
  }

  #pragma omp parallel for
  for(int i=0; i<ny; i++){
    for(int j=0; j<=i; j++){
      asm("#foo start");
      double res = 0;;
      for(int x=0; x<nx; x++){
	double p = data[i*nx + x] * data[j*nx + x];
	res += p;
      }
      result[i + j*ny] = res;
      asm("#foo end");
    }
  }

  free(data);
}
