#include <iostream>
#include <math.h>
#include <vector>
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
  constexpr int nb = 4; // chunk size
  int na = (nx + nb - 1) / nb; // number of chunks
  int nab = na * nb; // number of colums
  // cout << "na: " << na << " nab: " << nab << "\n";
  vector<double> data(ny*nab, 0.0);

  for(int y=0; y<ny; y++){
    double sum = 0, sum_sq = 0, mean, sum_sq_sqrt;
    for(int x=0; x<nx; x++){
      sum += data_[y*nx + x];      
    }
    // normalization: zero-mean    
    mean = sum / (double) nx;
    // std::cout << "mean of row " << y << " is " << mean << "\n";
    for(int x=0; x<nx; x++){
      data[y*nab + x] = data_[y*nx + x] - mean;
      sum_sq += (data[y*nab + x] * data[y*nab + x]);
    }

    sum_sq_sqrt = sqrt(sum_sq);
    // normalization: unit-norm
    for(int x=0; x<nx; x++)
      data[y*nab + x] /= sum_sq_sqrt;

    // padded region set to zero
    for(int x=nx; x<nab; x++)
      data[y*nab + x] = 0;    
  }

  // for(int y=0; y<ny; y++){
  //   for(int x=0; x<nab; x++){
  //     cout << data[y*nab + x] << ", ";
  //   }
  //   cout << "\n";
  // }

    
  for(int i=0; i<ny; i++){
    for(int j=0; j<=i; j++){

      double vv[nb];      
      for(int kb=0; kb<nb; kb++)
	vv[kb] = 0;


      for(int ka=0; ka<na; ka++){
	asm("# foo start");      	
	for(int kb=0; kb<nb; kb++){
	  int offset = ka*nb + kb;
	  double x = data[i*nab + offset];
	  double y = data[j*nab + offset];
	  double p = x * y;
	  vv[kb] += p;
	}
	asm("# foo end");            	
      }

      double res = 0;
      for(int kb=0; kb<nb; kb++)
	res += vv[kb];
      result[i + j*ny] = res;

      // double res = 0;
      // for(int x=0; x<nx; x++){
      // 	res += data[i*nx + x] * data[j*nx + x];
      // }
      // result[i + j*ny] = res;
    }
  }  
}
