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
bool delimFound(char,char);
const char sysEOL='\n';
int getMyNum(istream& is,char delim,bool & emptyFlag,bool & delimFlag,bool allowWS=false)  // deliminator is '/' or '\n' 
{
	stringstream ss;
	bool foundFirst=false;
	delimFlag=false;  //ensure it starts out FALSE
	char c='0';
	int myNum=-99;
	is>>ws;  // built in skip leading whitespace
	while(is.get(c) &&  !(delimFlag=delimFound(c,delim))&& (c!=sysEOL))//c!=delim)
		{
			if((!foundFirst)&& c=='-') //check for a leading negative
			{
				ss<<c; //first char can b negative (-)
				foundFirst=true;
				//is.get(c); //get next
			}
			else if(!isIntChar(c))
			{
				if(!( allowWS && isWhiteSpaceChar(c)))
				//	cout << "Got intra ws"; // skip ignore is WS is allowed w/in the number, 12 3/456 => 123/456
				//else
				{
					//TODO do not strip \n
					is.ignore(256,delim); // fails for >256 chars, okay by me
					is.setstate(ios::failbit);
				}
				
			}
			else
			{
				(!foundFirst?foundFirst=true:foundFirst=true);
				ss<<c;
			}
		}
	// get size
	ss.seekg(0,ios::end);
	int size=ss.tellg();
	ss.seekg(0,ios::beg);
	//std::cout <<"count:"<<size;
	//std::cout <<"ssize:"<<ss.str().size();
	if( size==0 ||(size=1 && ss.str()=="-")) // check for empty, or single '-'
	{
		emptyFlag=true;
		//std::cout << "empty value";
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
bool delimFound(char c,char d)
{
	return (c==d);
}

int _tmain(int argc, _TCHAR* argv[])
{
	ifstream myFile("\good_input.txt");
	if(!myFile)
	{
		cout << "Failed to open file";
		getchar();
		exit(1);
	}
	int num=0, denom=1;
	char c='\n';
	bool emptyFlagNum=false;
	bool delimFlagNum=false;
	bool emptyFlagDenom=false;
	bool delimFlagDenom=false;
	bool allowWS=true;
	//while(c!='n' || (!cin))

	while(myFile.get(c))
	{
		myFile.putback(c); //determine end of file w/ myFile.get(c), decrement get c
		char divideBy='/';
		char newline='\n';
		//cin.ignore(256,'\n');
		
		//cout << "Enter rational number:";
		try
		{
			num=getMyNum(myFile,divideBy,emptyFlagNum,delimFlagNum,allowWS);
			denom=getMyNum(myFile,newline,emptyFlagDenom,delimFlagDenom,allowWS);
			if(!denom)
				throw runtime_error("Denominator=0");
			// check empty
			if((emptyFlagNum && emptyFlagDenom)|| (emptyFlagNum&& !emptyFlagDenom)) //empty can't recover
				throw runtime_error("Empty error");
			else if ((!emptyFlagNum&& emptyFlagDenom)&&!delimFlagNum)  //num good, no /,denom missing, single digit? 7 valid, 7/ not valid
				denom=1; //set denom to 1, should print correctly
			else
				cout <<"Rational Number:"<< RationalNumber(num,denom)<<endl;

		/*
		cout <<"Num:"<<num;
		cout <<"Denom:"<<denom;
		cout <<endl<< "continue (y/n)"<<endl;
		cin.get(c);
		*/
			getchar();
		}
		catch(exception & e)
		{
			cout <<"exception caught"<<e.what()<<endl;
		}
		
	}
	
	//num=getNum(myFile);
	RationalNumber oneFourth(1,4);
	RationalNumber negOneFourth(1,-4);
	RationalNumber oneFourth2(-1,-4);
	cout << oneFourth<<endl;
	cout <<negOneFourth<<endl;
	cout <<oneFourth2<<endl;
	//test
	stringstream myss('-');
	int myint=0;
	myss >> myint;
	cout <<"myss:"<<myss.str();
	cout << "Myint:"<<myint;
	myss.clear();
	myss.ignore(12,'\n');
	
	myss<<'-'<<'1';
	myss>>myint;
	cout << "Myint:"<<myint;

	cout << "Myint2:"<<myint;
	
	getchar();
	return 0;
}

