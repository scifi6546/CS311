// dp3.cpp  SKELETON
// Glenn G. Chappell
// 2019-09-24
//
// For CS 311 Fall 2019
// Source for Project 3 Functions

#include "dp3.h"       // For Project 3 prototypes & templates

#include <functional>
using std::function;


void didItThrow(const function<void()> & ff,
                bool & threw)
{
	threw = false;
	try{
		ff();
	}
	catch(std::exception &e){
		threw= true;
		throw e;
	}
}


int gcd(int a,
        int b)
{
    return 42;  // Dummy return
    // TODO: Write this!!!
}

