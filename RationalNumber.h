#pragma once
#include <iostream>


class RationalNumber
{
	friend std::ostream & operator<<(const std::ostream &, const RationalNumber&);
	friend std::istream & operator>>(const std::istream &, RationalNumber &);
public:
	RationalNumber(int =1, int =1);
	~RationalNumber(void);
	operator void*() const;
private:
	int num, denom;

};

