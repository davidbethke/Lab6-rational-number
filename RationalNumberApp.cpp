// RationalNumberApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RationalNumber.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
bool isIntChar(char );
int getMyNum(istream& is,char delim)  // deliminator is '/' or '\n' 
{
	stringstream ss;
	char c='0';
	int myNum=-99;
	
	while(is.get(c) && !is.fail() &&  c!=delim)
		{
			
			if(!isIntChar(c))
			{
				is.ignore(256,delim);
				is.setstate(ios::failbit);
				
			}
			else
				ss<<c;
		}
		ss>> myNum;
		is.clear();
		//is.ignore(256,delim); //clear
	return myNum;
}
int getMyDenom(ifstream& is) // delim is '\n'
{
	return 0;
}
bool isIntChar(char c)
{
	return (c=='0'||c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9');
}
int _tmain(int argc, _TCHAR* argv[])
{
	//ifstream myFile("\goodFile.txt");
	int num=0, denom=1;
	char c='\n';
	while(c!='n' || (!cin))
	{
		char divideBy='/';
		char newline='\n';
		cin.ignore(256,'\n');
		
		cout << "Enter rational number:";
		num=getMyNum(cin,divideBy);
		denom=getMyNum(cin,newline);
		cout <<"Num:"<<num;
		cout <<"Denom:"<<denom;

		//cin.clear();
		// clear any lingering newlines
		//cin.ignore(256,'\n');
		//cout << endl;
		//cin.ignore(256,'\n');
		cout <<endl<< "continue (y/n)"<<endl;
		cin.get(c);
		
	}
	
	//num=getNum(myFile);
	RationalNumber oneFourth(1,4);
	RationalNumber negOneFourth(1,-4);
	RationalNumber oneFourth2(-1,-4);
	cout << oneFourth<<endl;
	cout <<negOneFourth<<endl;
	cout <<oneFourth2<<endl;
	getchar();
	return 0;
}

