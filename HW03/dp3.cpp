// dp3.cpp  
// Nicholas Alexeev with contributions from Glen G Chappell
// 2019-09-24
//
// For CS 311 Fall 2019
// Source for Project 3 Functions

#include "dp3.h"       // For Project 3 prototypes & templates

#include <functional>
using std::function;

//prereq ff is a staic function that does not modify any state anywhere
//throws whatever ff throws when operator() is called
void didItThrow(const function<void()> & ff,
                bool & threw)
{
	threw = false;
	try{
		ff();
	}
	catch(...){
		threw=true;
	}
	ff();
}

//prereq: a>0 && b>0
int gcd(int a,
        int b)
{
	if(a==0){
		return b;
	}
	else if(a>b){
		return gcd(b,a);
	}else{
		return gcd(b%a,a);
	}
}

