// Copyright (c) Facebook, Inc. and its affiliates.
//
// This source code is licensed under the MIT license found in the
// LICENSE file in the root directory of this source tree.

#include <stdio.h>

#include "../EnumO.h"

MY_ENUM_O(Fruits, int, (apple, banana, pear));

__global__ void add(int n, float a, float* x) {
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  if (i < n) {
    x[i] = a * x[i];
  }
}

int main(int argc, char** args) {
  int N = 1 << 20;
  float *x, *d_x;
  x = (float*)malloc(N * sizeof(float));

  cudaMalloc(&d_x, N * sizeof(float));

  for (int i = 0; i < N; i++) {
    x[i] = 1.0f;
  }

  cudaMemcpy(d_x, x, N * sizeof(float), cudaMemcpyHostToDevice);

  add<<<(N + 255) / 256, 256>>>(N, 2.0f, d_x);

  cudaFree(d_x);
  free(x);
}
