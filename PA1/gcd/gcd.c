#include "gcd.h"

long gcd(const long lhs_, const long rhs_)
{
	long lhs = lhs_;
	long rhs = rhs_;

	while(lhs != rhs)
	{
		if(lhs > rhs)
		{
			lhs = lhs - rhs;
			continue;
		}
		rhs = rhs - lhs;
	}

	return lhs;
}
