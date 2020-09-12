#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "gcd.h"

int main(int argc, char **argv)
{
	if(argc < 3)
	{
		fprintf(stderr, "Usage: %s [lhs] [rhs]\n", argv[0]);
		return -1;
	}

	assert(sizeof(long) == 8);

	long lhs = atol(argv[1]);
	long rhs = atol(argv[2]);

	printf("GCD of %ld, %ld = %ld\n", lhs, rhs, gcd(lhs, rhs));
}
