#include <math.h>
#include <stdio.h>

#ifndef pi
#define  pi 3.14159265
#endif

int main(){
  int a = 1;  // Amplitude of wave
  float psi = 0; // Phase of wave
  int N = 250;  // Number of elements
  int f = 2;  // Frequency
  float delta_t = 0.1;  // Time increment
  float h_t[N];

  // 1.1
  for (int i = 0; i <= N; i++) {
    h_t[i] = a*cos(f*delta_t*i + psi);
  }

  FILE *file1 = fopen("task11_data.txt", "w");
  for (int i = 0; i <= N; i++) {
    fprintf(file1, "%f\n", h_t[i]);
  }
  fclose(file1);

  // 1.2
  f = 1;

  for (int i = 0; i <= N; i++) {
    h_t[i] = a*cos(f*delta_t*i+psi);
  }

  FILE *file2 = fopen("task12_data.txt", "w");
  for (int i = 0; i <= N; i++) {
    fprintf(file2, "%f\n", h_t[i]);
  }
  fclose(file2);

  // 1.3
  psi = pi/2.0;
  printf("%f\n", psi);

  for (int i = 0; i <= N; i++) {
    h_t[i] = a*cos(f*delta_t*i+psi);
  }

  FILE *file3 = fopen("task13_data.txt", "w");
  for (int i = 0; i <= N; i++) {
    fprintf(file3, "%f\n", h_t[i]);
  }
  fclose(file3);
}
