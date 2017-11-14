#include <math.h>
#include <stdio.h>
#include <complex.h>

#ifndef pi
#define  pi 3.14159265
#endif

int fft1D(float * ht, float complex * ht_fft, int N){
  printf("%s\n", "Calculating discrete fourier transform");

  for(int n = 0; n < N; n++){
    ht_fft[n] = 0;
    for(int k = 0; k < N; k++){
      ht_fft[n] = ht_fft[n] + ht[k]*cexp(1i*2*pi*k*n/(float)N);
    }
  }
  return 1;
}

int main(){
  // TASK 1
  int a = 1;  // Amplitude of wave
  float psi = 0; // Phase of wave
  int N = 250;  // Number of elements
  int f = 2;  // Frequency
  float delta_t = 0.1;  // Time increment

  float ht[N-1];
  // 1.1
  for (int i = 0; i < N; i++) {
    ht[i] = a*cos(f*delta_t*i + psi);
  }
  FILE *file1 = fopen("task2_data.txt", "w");

  for (int i = 0; i < N; i++) {
    fprintf(file1, "%f\n", ht[i]);
  }
  fclose(file1);


  // TASK 2
  float complex ht_fft[N-1];
  fft1D(ht, ht_fft, N);
  FILE *file2 = fopen("task2_data_fft.txt", "w");
  for (int i = 0; i < N; i++) {
    fprintf(file2, "%f%c%f\n", creal(ht_fft[i]), ',',cimag(ht_fft[i]));
  }
  fclose(file2);
}
