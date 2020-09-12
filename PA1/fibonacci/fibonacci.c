#include "fibonacci.h"

long *fibonacci(long *opt, const unsigned long count)
{
	opt[0] = 1;

	if(count < 2)
	{
		goto fibonacci_ret;
	}

	opt[1] = 1;

	for(int i = 2 ; i < count ; i++)
	{
		opt[i] = opt[i - 1] + opt[i - 2];
	}

fibonacci_ret:
	return opt;
}
