// RationalNumberApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RationalNumber.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;
bool isIntChar(char );
bool isWhiteSpaceChar(char);
int getMyNum(istream& is,char delim,bool allowWS=false)  // deliminator is '/' or '\n' 
{
	stringstream ss;
	bool foundFirst=false;
	char c='0';
	int myNum=-99;
	is>>ws;  // built in skip leading whitespace
	while(is.get(c) &&  c!=delim)
		{
			if((!foundFirst)	&& c=='-') //check for a leading negative
			{
				ss<<c; //first char can b negative (-)
				foundFirst=true;
				is.get(c); //get next
			}
			if(!isIntChar(c))
			{
				if( allowWS && isWhiteSpaceChar(c))
					; // skip ignore is WS is allowed w/in the number, 12 3/456 => 123/456
				else
				{
					is.ignore(256,delim); // fails for >256 chars, okay by me
					is.setstate(ios::failbit);
				}
				
			}
			else
				(!foundFirst?foundFirst=true:foundFirst=true);
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
	//return (c=='0'||c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9');
	return (c>='0' && c<='9');
}
bool isWhiteSpaceChar(char c)
{
	return (c==' ' || c=='\t' || c=='\r');
}
void setSkipWs(istream& is)
{
	//is.setf(ios::skipws);
	is>>ws; // built in function
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

		num=getMyNum(cin,divideBy,true);
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

