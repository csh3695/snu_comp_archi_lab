#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "fibonacci.h"

int main(int argc, char **argv)
{
	if(argc < 2)
	{
		fprintf(stderr, "Usage: %s [count]\n", argv[0]);
		return -1;
	}

	long count = atoi(argv[1]);

	if(count <= 0)
	{
		fprintf(stderr, "Count must be positive integer!");
		return -1;
	}

	assert(sizeof(long) == 8);

	long *result = (long*)malloc(sizeof(long) * count);
	long *ret = fibonacci(result, count);

	if(result != ret)
	{
		fprintf(stderr, "Return value error! (%p:%p)\n", result, ret);
	}
	for(int i = 0 ; i < count ; printf("%ld\n", result[i++]));

	free(result);
	return 0;
}
