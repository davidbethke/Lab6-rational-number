// RationalNumberApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RationalNumber.h"

using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	RationalNumber oneFourth(1,4);
	RationalNumber negOneFourth(1,-4);
	cout << oneFourth;
	cout <<negOneFourth;
	getchar();
	return 0;
}

