#ifndef CONV_H
#define CONV_H

void convolution(const int M, const int N, const int *input, int *output, const int filter[3][3]);
void convolution_TA(const int M, const int N, const int *input, int *output, const int filter[3][3]);
void convolution_ref(const int M, const int N, const int *input, int *output, const int filter[3][3]);
#endif
