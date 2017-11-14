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

int fftshift(float complex * ht_fft, int N){
  if(N%2 != 0){
    printf("%s\n","Array must have an even number of elements");
    return 0;
  }

  // (Very non-stylish way to fftshift an array)
  float complex tmp[N-1];
  // Moving N/2 -- N-1 to 0 to N/2 - 1
  for(int i = N/2; i <= (N-1); i++){
    tmp[i-N/2] = ht_fft[i]; // From 0 to N-1-N/2 = (2N-2)/2 = N/2-1
  }
  // moving 0-- N/2 -1 to N/2 -- N-1
  for(int i = 0; i<=(N/2-1); i++){
    tmp[N/2+i] = ht_fft[i]; // From N/2 to N -1
  }
  // Inserting values in original array
  for(int i = 1; i<(N-1); i++){
    ht_fft[i] = tmp[i];
  }
  return 1;
}

int main(){

  int a = 1;  // Amplitude of wave
  float psi = 0; // Phase of wave
  int N = 250;  // Number of elements
  int f = 2;  // Frequency
  float delta_t = 0.1;  // Time increment

  float ht[N-1];
  for (int i = 0; i < N; i++) {
    ht[i] = a*cos(f*delta_t*i + psi);
  }

  float complex ht_fft[N-1];
  fft1D(ht, ht_fft, N);
  fftshift(ht_fft,N);

  FILE *file1 = fopen("task3_data_fft_f_2_psi_0.txt", "w");
  for (int i = 0; i < N; i++) {
    fprintf(file1, "%f%c%f\n", creal(ht_fft[i]), ',',cimag(ht_fft[i]));
  }
  fclose(file1);

  f = 1;

  for (int i = 0; i < N; i++) {
    ht[i] = a*cos(f*delta_t*i + psi);
  }

  fft1D(ht, ht_fft, N);
  fftshift(ht_fft,N);

  FILE *file2 = fopen("task3_data_fft_f_1_psi_0.txt", "w");
  for (int i = 0; i < N; i++) {
    fprintf(file2, "%f%c%f\n", creal(ht_fft[i]), ',',cimag(ht_fft[i]));
  }
  fclose(file2);

  psi = pi/2;

  for (int i = 0; i < N; i++) {
    ht[i] = a*cos(f*delta_t*i + psi);
  }

  fft1D(ht, ht_fft, N);
  fftshift(ht_fft,N);

  FILE *file3 = fopen("task3_data_fft_f_1_psi_pi2.txt", "w");
  for (int i = 0; i < N; i++) {
    fprintf(file3, "%f%c%f\n", creal(ht_fft[i]), ',',cimag(ht_fft[i]));
  }
  fclose(file3);
}
