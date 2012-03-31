#pragma once
#include <iostream>


class RationalNumber
{
	friend std::ostream & operator<<( std::ostream &, const RationalNumber&);
	friend std::istream & operator>>( std::istream &, RationalNumber &);
public:
	explicit RationalNumber(int =1, int =1);
	~RationalNumber(void);
	operator void*()  {return (num==0?NULL:this);}
	operator const void*() const {return (num==0?NULL:this);}

private:
	int num, denom;

};

