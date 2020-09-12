#include "conv.h"

//This is reference code for convolution. Do not fix!
void convolution_ref(const int M, const int N, const int *input, int *output, const int filter[3][3])
{
	for(int i = 0 ; i < M ; i++)
	{
		for(int j = 0 ; j < N ; j++)
		{
			//For each pixel
			for(int x = 0 ; x < 3 ; x++)
			{
				for(int y = 0 ; y < 3 ; y++)
				{
					//Boundary check
					if(i + x - 1 < 0)
						continue;
					if(i + x - 1 >= M)
						continue;
					if(j + y - 1 < 0)
						continue;
					if(j + y - 1 >= N)
						continue;

					output[i * N + j] += input[(i + x - 1) * N + (j + y - 1)] * filter[x][y];
				}
			}
		}
	}
}
