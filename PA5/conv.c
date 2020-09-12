
#include "conv.h"
#include <stdint.h>


void convolution(const int M, const int N, const int *input, int *output, const int filter[3][3])
{
	int f00 = filter[0][0];
	int f01 = filter[0][1];
	int f02 = filter[0][2];
	int f10 = filter[1][0];
	int f11 = filter[1][1];
	int f12 = filter[1][2];
	int f20 = filter[2][0];
	int f21 = filter[2][1];
	int f22 = filter[2][2];
    register int tmp;
    // i=0 i=M-1 j=0 j=N-1

    //i=0 j=0
    register int sum = 0;
    sum += input[0] * f11;		//1,1
    sum += input[1] * f12;		//1,2
    sum += input[N] * f21;		//2,1
    sum += input[N+1] * f22; 	//2,2
    output[0] += sum;
    
    //i=M-1 j=0
    sum = 0;
    tmp = (M-2)*N;
    sum += input[tmp] * f01;	//0,1
    sum += input[tmp+1] * f02; 	//0,2
    tmp+=N;
    sum += input[tmp] * f11;	//1,1
    sum += input[tmp+1] * f12;	//1,2
    output[tmp] += sum;

    //i=0 j=N-1
    sum = 0;
    tmp = (N<<1)-1;
    sum += input[tmp-1] * f20; 	//2,0
    sum += input[tmp] * f21;	//2,1
    tmp-=N;
    sum += input[tmp-1] * f10;	//1,0
    sum += input[tmp] * f11;	//1,1
    output[tmp] += sum;

    
    //i=M-1 j=N-1
    sum = 0;
    tmp = (M-1)*N-1;
    sum += input[tmp-1] * f00; 	//0,0
    sum += input[tmp] * f01;	//0,1
    tmp+=N;
    sum += input[tmp-1] * f10;	//1,0
    sum += input[tmp] * f11;	//1,1
    output[tmp] += sum;
    
    for(register int i = 1; i < M-1; i++){ // j=0||j=N-1
        //j=0
        sum = 0;
        tmp=(i-1)*N;
        sum += input[tmp] * f01;	//0,1
        sum += input[tmp+1] * f02; 	//0,2
        tmp+=(N<<1);
        sum += input[tmp] * f21;	//2,1
        sum += input[tmp+1] * f22; 	//2,2
        tmp-=N;
        sum += input[tmp] * f11;	//1,1
        sum += input[tmp+1] * f12;	//1,2
        output[tmp] += sum;
        //j=N-1
        sum = 0;
        tmp=i*N-1;
        sum += input[tmp-1] * f00; 	//0,0
        sum += input[tmp] * f01;	//0,1
        tmp+=(N<<1);
        sum += input[tmp-1] * f20; 	//2,0
        sum += input[tmp] * f21;	//2,1
        tmp-=N;
        sum += input[tmp-1] * f10;	//1,0
        sum += input[tmp] * f11;	//1,1
        output[tmp] += sum;
    }

    for(register int j = 1; j < N-1; j++){
        //i=0
        sum = 0;
        tmp = j-1;
        sum += input[tmp] * f10;	//1,0
        sum += input[N + tmp] * f20;//2,0
        sum += input[++tmp] * f11;	//1,1
        sum += input[N + tmp] * f21;//2,1
        sum += input[++tmp] * f12;	//1,2
        sum += input[N + tmp] * f22;//2,2
        output[--tmp] += sum;
        //i=M-1
        sum = 0;
        tmp=(M-2)*N+(j-1);
        sum += input[tmp] * f00; 	//0,0
        sum += input[++tmp] * f01;	//0,1
        sum += input[tmp+1] * f02; 	//0,2
        tmp+=N;
        sum += input[tmp-1] * f10;	//1,0
        sum += input[tmp] * f11;	//1,1
        sum += input[tmp+1] * f12;	//1,2
        output[tmp] += sum;
    }

	for (register int i = 1; i < M-1; i++)
	{
		for (register int j = 1; j < N-1; j++)
		{
			sum = 0;
			tmp = (i-1)*N + j;
			sum += input[tmp-1] * f00; 	//0,0
			sum += input[tmp] * f01;	//0,1
			sum += input[tmp+1] * f02; 	//0,2
			tmp+=(N<<1);
			sum += input[tmp-1] * f20; 	//2,0
			sum += input[tmp] * f21;	//2,1
			sum += input[tmp+1] * f22; 	//2,2
			tmp-=N;
			sum += input[tmp-1] * f10;	//1,0
			sum += input[tmp] * f11;	//1,1
			sum += input[tmp+1] * f12;	//1,2
			output[tmp] += sum;
		}
	}
}