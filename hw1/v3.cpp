#include <stdio.h>
#include "blockmatrix.h"
#include <x86intrin.h>
#include <string>
#include <stdlib.h>

using namespace std;

int main(int argc, char **argv) {
  const int ay = argc > 1 ? std::stoi(argv[1]) : 1000,
            ax = argc > 2 ? std::stoi(argv[2]) : 900,
            by = ax,
            bx = argc > 3 ? std::stoi(argv[3]) : 1200,
            cy = ay, cx = bx;
  
  Matrix<double, 64> a(ay, ax), b(by, bx);
  
  for (int i = 0; i < ay; i++) {
    for (int j = 0; j < ax; j++) {
      a(i, j) = i*j;
    } 
  }
    
  for (int i = 0; i < by; i++) {
    for (int j = 0; j < bx; j++) {
      b(i, j) = i*j;
    }
  }

  double sum = 0.0;
  long long start = __rdtsc();
  auto c = a * b;
  long long end = __rdtsc();
    for (int i = 0; i < cy; i++)
        for (int j = 0; j < cx; j++)
            sum += c(i,j);
  printf("sum=%.0lf time=%.6f\n", sum, (end - start)/2000000000.);
  
  return 0;
}
