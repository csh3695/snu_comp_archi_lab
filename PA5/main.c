#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/time.h>

#include "conv.h"

int main(int argc, char **argv)
{
	if(argc < 2)
	{
		fprintf(stderr, "Usage: %s [input file]\n", argv[0]);
		return 1;
	}

	FILE *fp = fopen(argv[1], "r");
	if(!fp)
	{
		fprintf(stderr, "Failed to open %s: ", argv[1]);
		perror((void*)0);
		return 0;
	}

	int filter[3][3] = {	{0, -1, 2},
				{-1, 1, 2},
				{1, 0, 0}};

	int M, N;
	fscanf(fp, "%d %d\n", &M, &N);
	
	int *conv_input = (int*)malloc(sizeof(int) * M * N);
	int *conv_output = (int*)malloc(sizeof(int) * M * N);
	int *conv_ref_output = (int*)malloc(sizeof(int) * M * N);
	int *conv_TA_output = (int*)malloc(sizeof(int) * M * N);

	for(int i = 0 ; i < M ; i++)
	{
		for(int j = 0 ; j < N ; j++)
		{
			fscanf(fp, "%d", conv_input + (i * N + j));
		}
	}
	memset(conv_output, 0, sizeof(int) * M * N);
	memset(conv_ref_output, 0, sizeof(int) * M * N);
	memset(conv_TA_output, 0, sizeof(int) * M * N);
	
	fclose(fp);



	//Time:
	struct timeval start, end, ref_end, TA_end;

	gettimeofday(&start, NULL);
	convolution(M, N, conv_input, conv_output, filter);
	gettimeofday(&end, NULL);
	convolution_ref(M, N, conv_input, conv_ref_output, filter);
	gettimeofday(&ref_end, NULL);
	convolution_TA(M, N, conv_input, conv_TA_output, filter);
	gettimeofday(&TA_end, NULL);


	double your_time = ((double)(end.tv_sec - start.tv_sec)) + 
		(((double)(end.tv_usec - start.tv_usec)) / ((double)1000000.0));
	
	double ref_time = ((double)(ref_end.tv_sec - end.tv_sec)) + 
		(((double)(ref_end.tv_usec - end.tv_usec)) / ((double)1000000.0));
	
	double TA_time = ((double)(TA_end.tv_sec - ref_end.tv_sec)) + 
		(((double)(TA_end.tv_usec - ref_end.tv_usec)) / ((double)1000000.0));

	printf("Your time: %lf, Reference time: %lf, TA time: %lf, Your speedup: %lfx, TA speedup: %lfx\n",
		your_time, ref_time, TA_time, (ref_time / your_time), (ref_time / TA_time));

	for(int i = 0 ; i < M ; i++)
	{
		for(int j = 0 ; j < N ; j++)
		{
			if(conv_output[i * N + j] != conv_ref_output[i * N + j])
			{
				fprintf(stderr, "Data miscompare at input[%d][%d]! %d : %d\n",
					i, j, conv_output[i * N + j], conv_ref_output[i * N + j]);
				return -1;
			}
		}
	}

	return 0;
}
