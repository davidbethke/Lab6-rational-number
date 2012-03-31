#include "RationalNumber.h"
#include <stdexcept>
#include <cmath>

using namespace std;
RationalNumber::RationalNumber(int n, int d):num(n),denom(d)
{
	if (denom == 0)
		throw invalid_argument("Denominator Zero");
}


RationalNumber::~RationalNumber(void)
{
}
ostream& operator<<( ostream& os, const RationalNumber& rn)
{
	if(rn.denom ==1)
		cout<< rn.num;
	else if((rn.num<0)&&(rn.denom<0))
		cout <<abs(rn.num)<<"/"<<abs(rn.denom);
	else if(rn.num<0 || rn.denom <0) //negative
		cout <<"-"<<abs(rn.num)<<"/"<<abs(rn.denom);
	else 
		cout<<rn.num<<"/"<<rn.denom;
	return os;

}