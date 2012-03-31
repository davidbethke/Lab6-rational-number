#include "RationalNumber.h"
#include <stdexcept>

using namespace std;
RationalNumber::RationalNumber(int n, int d):num(n),denom(d)
{
	if (denom == 0)
		throw invalid_argument("Denominator Zero");
}


RationalNumber::~RationalNumber(void)
{
}
RationalNumber::operator void *() const
{
	return (num==0?NULL:this);
}
