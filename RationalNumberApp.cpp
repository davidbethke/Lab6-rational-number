// RationalNumberApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RationalNumber.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
//////////////////////////
//    Flag Combinations
//////////////////////////
// Empty Flags
//    Num	Denom	Result
//		t		t	throw empty exception
//		t		f	throw empty exception
//		f		t	see delimFlag table
//		f		f	normal
////////////////////////////////////
// Delim Flags
//    Num	Denom	Result
//		t		t	normal
//		t		f	
//		f		t	
//		f		f
///////////////////////////////////////
// allowWS
// defaults to false, do not allow intra number spaces, ie 12 3 != 123 invalid
// set to true to allow intra number spaces				ie 12 3  = 123 valid
/////////////////////////////////////////
//  const char sysEOL set to system end of line char


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
	int myNum=-99; // init number
	is>>ws;  // built in skip leading whitespace
	//while(is.get(c) &&  !(delimFlag=delimFound(c,delim)) && c!=sysEOL)//c!=delim)
	while(is.get(c) &&  !(delimFlag=delimFound(c,delim)) && c!=sysEOL)//c!=delim)
		{
			//cout<<":"<<c<<":"<<endl;
			//cout<<"!"<<is.tellg()<<"!"<<endl;
			if((!foundFirst)&& c=='-') //check for a leading negative
			{
				ss<<c; //first char can b negative (-)
				foundFirst=true;
			}
			else if(!isIntChar(c))
			{
				if(!( allowWS && isWhiteSpaceChar(c))) // TODO could be combined w/ above if?
				
				{
					//TODO do not strip \n
					is.ignore(256,delim); // fails for >256 chars, okay by me
					is.setstate(ios::failbit);
				}
				
			}
			else
			{
				foundFirst=true; //set found first, if no negative and 
				ss<<c;
			}
		}
	// get size
	/*
	ss.seekg(0,ios::end);
	int size=ss.tellg();
	ss.seekg(0,ios::beg);
	*/
	int size=ss.str().size();
	if( size==0 ||(size=1 && ss.str()=="-")) // check for empty, or single '-'
	{
		emptyFlag=true;
		
	}
	
	
	
	
	ss>> myNum; //stuff result into an int
	
	//if(delim== sysEOL || c== sysEOL) // put back EOL or (c == sysEOL) kinda duplication
	
	if(c== sysEOL&&(emptyFlag&&delim==sysEOL)) // put back EOL or (c == sysEOL) kinda duplication
		{
			//cout<<"putting LF back"<<endl;
			is.unget();

		}
		
	//kluge
	/*
	if( emptyFlag && delim == sysEOL) // check for empty, or single '-' for case of 7 <lf>, is.get(c) processed before delimFlag=delimFound...
	{
		is.unget();
		delimFlag=true;
		myNum=1;
		
	}
	*/
		
		is.clear(); //clear all flags
		
	return myNum;
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
	ifstream myFile("\good_input2.txt",ios::in|ios::binary);
	if(!myFile)
	{
		cout << "Failed to open file";
		getchar();
		exit(1);
	}
	int num=0, denom=1; 
	char c='\n';
	char divideBy='/';
	char newline='\n';
	bool emptyFlagNum=false;
	bool delimFlagNum=false;
	bool emptyFlagDenom=false;
	bool delimFlagDenom=false;
	bool allowWS=true;
	//while(c!='n' || (!cin))

	while(myFile.get(c) && !myFile.eof())//myFile.get(c))
	{
		myFile.unget(); //put char back into stream
		//myFile.putback(c); //determine end of file w/ myFile.get(c), decrement get c
		
		
		try
		{
			num=getMyNum(myFile,divideBy,emptyFlagNum,delimFlagNum,allowWS);
			if(!delimFlagNum)
				;//denom=1; // no '/' found set denom to 1, could be single digit if emptyFlagNum not empty
			else
				denom=getMyNum(myFile,newline,emptyFlagDenom,delimFlagDenom,allowWS);
			
			cout<<"numDelim:"<<delimFlagNum<<"denomDelim:"<<delimFlagDenom<<endl;
			cout<<"numEmpty:"<<emptyFlagNum<<"denomEmpty:"<<emptyFlagDenom<<endl;
			cout <<"num:"<<num<<"denom:"<<denom<<endl;
		
			if(!denom)
				throw runtime_error("Denominator=0");
			// check empty Flag conditions
			if((emptyFlagNum && emptyFlagDenom)|| (emptyFlagNum&& !emptyFlagDenom)||
				(!emptyFlagNum&&emptyFlagDenom&&(delimFlagNum&&!delimFlagDenom))) //empty can't recover
			{
				cout <<"Num:"<<num<<" "<<"Denom:"<<denom<<endl;
				throw runtime_error("Empty error");
			}
			else if ((!emptyFlagNum&& emptyFlagDenom)&&!delimFlagNum&&delimFlagDenom)  //num good, no /,denom missing, single digit? 7 valid, 7/ not valid
			{
				denom=1; //set denom to 1, should print correctly
				cout<<"numDelim:"<<delimFlagNum<<"denomDelim:"<<delimFlagDenom<<endl;
				cout<<"numEmpty:"<<emptyFlagNum<<"denomEmpty:"<<emptyFlagDenom<<endl;
				cout <<"Rational Number:Single Digit Found:"<< RationalNumber(num,denom)<<endl;
			}
			else
			{
				//cout<<"numDelim:"<<delimFlagNum<<"denomDelim:"<<delimFlagDenom<<endl;
				//cout<<"numEmpty:"<<emptyFlagNum<<"denomEmpty:"<<emptyFlagDenom<<endl;
				cout <<"Rational Number:"<< RationalNumber(num,denom)<<endl;
			}

		}
		catch(exception & e)
		{
			cout <<"Exception caught:"<<e.what()<<endl;
		}
		
	}
	
	
	getchar();
	myFile.close();
	return 0;
}

