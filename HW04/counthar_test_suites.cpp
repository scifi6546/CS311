// counthar_test_suites.cpp
// Glenn G. Chappell
// 2019-10-01
//
// For CS 311 Fall 2019
// Tests for function countHAR: test suites
// For Project 4, Exercise A
// Uses the "Catch" unit-testing framework, version 2
// Requires counthar_test_main.cpp, catch.hpp, counthar.h,
//  counthar.cpp

// Includes for code to be tested
#include "counthar.h"      // For function countHAR
#include "counthar.h"      // Double inclusion test

#define CATCH_CONFIG_FAST_COMPILE
                           // Disable some features for faster compile
#include "catch.hpp"       // For the "Catch" unit-testing framework

// Additional includes for this test program
// (None)


// *********************************************************************
// Helper Functions/Classes for This Test Program
// *********************************************************************


// (None)


// *********************************************************************
// Test Cases
// *********************************************************************


TEST_CASE( "n x 1 and 1 x n boards",
           "[values]" )
{
    SECTION( "All 3 x 1 boards" )
    {
        REQUIRE( countHAR(3,1, 0,0, 1,0, 2,0) == 1 );
        REQUIRE( countHAR(3,1, 0,0, 2,0, 1,0) == 1 );
        REQUIRE( countHAR(3,1, 1,0, 0,0, 2,0) == 0 );
        REQUIRE( countHAR(3,1, 1,0, 2,0, 0,0) == 0 );
        REQUIRE( countHAR(3,1, 2,0, 0,0, 1,0) == 1 );
        REQUIRE( countHAR(3,1, 2,0, 1,0, 0,0) == 1 );
    }

    SECTION( "All 1 x 3 boards" )
    {
        REQUIRE( countHAR(1,3, 0,0, 0,1, 0,2) == 1 );
        REQUIRE( countHAR(1,3, 0,0, 0,2, 0,1) == 1 );
        REQUIRE( countHAR(1,3, 0,1, 0,0, 0,2) == 0 );
        REQUIRE( countHAR(1,3, 0,1, 0,2, 0,0) == 0 );
        REQUIRE( countHAR(1,3, 0,2, 0,0, 0,1) == 1 );
        REQUIRE( countHAR(1,3, 0,2, 0,1, 0,0) == 1 );
    }

    SECTION( "All 4 x 1 boards" )
    {
        REQUIRE( countHAR(4,1, 0,0, 1,0, 2,0) == 0 );
        REQUIRE( countHAR(4,1, 0,0, 1,0, 3,0) == 1 );
        REQUIRE( countHAR(4,1, 0,0, 2,0, 1,0) == 0 );
        REQUIRE( countHAR(4,1, 0,0, 2,0, 3,0) == 0 );
        REQUIRE( countHAR(4,1, 0,0, 3,0, 1,0) == 1 );
        REQUIRE( countHAR(4,1, 0,0, 3,0, 2,0) == 0 );
        REQUIRE( countHAR(4,1, 1,0, 0,0, 2,0) == 0 );
        REQUIRE( countHAR(4,1, 1,0, 0,0, 3,0) == 0 );
        REQUIRE( countHAR(4,1, 1,0, 2,0, 0,0) == 0 );
        REQUIRE( countHAR(4,1, 1,0, 2,0, 3,0) == 0 );
        REQUIRE( countHAR(4,1, 1,0, 3,0, 0,0) == 0 );
        REQUIRE( countHAR(4,1, 1,0, 3,0, 2,0) == 0 );
        REQUIRE( countHAR(4,1, 2,0, 0,0, 1,0) == 0 );
        REQUIRE( countHAR(4,1, 2,0, 0,0, 3,0) == 0 );
        REQUIRE( countHAR(4,1, 2,0, 1,0, 0,0) == 0 );
        REQUIRE( countHAR(4,1, 2,0, 1,0, 3,0) == 0 );
        REQUIRE( countHAR(4,1, 2,0, 3,0, 0,0) == 0 );
        REQUIRE( countHAR(4,1, 2,0, 3,0, 1,0) == 0 );
        REQUIRE( countHAR(4,1, 3,0, 0,0, 1,0) == 0 );
        REQUIRE( countHAR(4,1, 3,0, 0,0, 2,0) == 1 );
        REQUIRE( countHAR(4,1, 3,0, 1,0, 0,0) == 0 );
        REQUIRE( countHAR(4,1, 3,0, 1,0, 2,0) == 0 );
        REQUIRE( countHAR(4,1, 3,0, 2,0, 0,0) == 1 );
        REQUIRE( countHAR(4,1, 3,0, 2,0, 1,0) == 0 );
    }

    SECTION( "All 1 x 4 boards" )
    {
        REQUIRE( countHAR(1,4, 0,0, 0,1, 0,2) == 0 );
        REQUIRE( countHAR(1,4, 0,0, 0,1, 0,3) == 1 );
        REQUIRE( countHAR(1,4, 0,0, 0,2, 0,1) == 0 );
        REQUIRE( countHAR(1,4, 0,0, 0,2, 0,3) == 0 );
        REQUIRE( countHAR(1,4, 0,0, 0,3, 0,1) == 1 );
        REQUIRE( countHAR(1,4, 0,0, 0,3, 0,2) == 0 );
        REQUIRE( countHAR(1,4, 0,1, 0,0, 0,2) == 0 );
        REQUIRE( countHAR(1,4, 0,1, 0,0, 0,3) == 0 );
        REQUIRE( countHAR(1,4, 0,1, 0,2, 0,0) == 0 );
        REQUIRE( countHAR(1,4, 0,1, 0,2, 0,3) == 0 );
        REQUIRE( countHAR(1,4, 0,1, 0,3, 0,0) == 0 );
        REQUIRE( countHAR(1,4, 0,1, 0,3, 0,2) == 0 );
        REQUIRE( countHAR(1,4, 0,2, 0,0, 0,1) == 0 );
        REQUIRE( countHAR(1,4, 0,2, 0,0, 0,3) == 0 );
        REQUIRE( countHAR(1,4, 0,2, 0,1, 0,0) == 0 );
        REQUIRE( countHAR(1,4, 0,2, 0,1, 0,3) == 0 );
        REQUIRE( countHAR(1,4, 0,2, 0,3, 0,0) == 0 );
        REQUIRE( countHAR(1,4, 0,2, 0,3, 0,1) == 0 );
        REQUIRE( countHAR(1,4, 0,3, 0,0, 0,1) == 0 );
        REQUIRE( countHAR(1,4, 0,3, 0,0, 0,2) == 1 );
        REQUIRE( countHAR(1,4, 0,3, 0,1, 0,0) == 0 );
        REQUIRE( countHAR(1,4, 0,3, 0,1, 0,2) == 0 );
        REQUIRE( countHAR(1,4, 0,3, 0,2, 0,0) == 1 );
        REQUIRE( countHAR(1,4, 0,3, 0,2, 0,1) == 0 );
    }

    SECTION( "Various n x 1 boards with n > 4" )
    {
        REQUIRE( countHAR(  5,1,   0,0,   1,0,   4,0) == 1 );
        REQUIRE( countHAR(  5,1,   2,0,   0,0,   4,0) == 0 );
        REQUIRE( countHAR(  7,1,   2,0,   0,0,   4,0) == 0 );
        REQUIRE( countHAR(  8,1,   7,0,   6,0,   0,0) == 1 );
        REQUIRE( countHAR( 20,1,   0,0,  19,0,   1,0) == 1 );
        REQUIRE( countHAR( 25,1,  24,0,   0,0,  22,0) == 0 );
        REQUIRE( countHAR(299,1, 298,0,   0,0, 297,0) == 1 );
        REQUIRE( countHAR(299,1, 297,0, 298,0,   0,0) == 0 );
    }

    SECTION( "Various 1 x n boards with n > 4" )
    {
        REQUIRE( countHAR(1,  5, 0,  4, 0,  3, 0,0) == 1 );
        REQUIRE( countHAR(1,  5, 0,  0, 0,  1, 0,4) == 1 );
        REQUIRE( countHAR(1,  6, 0,  1, 0,  5, 0,0) == 0 );
        REQUIRE( countHAR(1,  6, 0,  5, 0,  0, 0,4) == 1 );
        REQUIRE( countHAR(1, 33, 0, 15, 0,  0, 0,1) == 0 );
        REQUIRE( countHAR(1, 50, 0,  0, 0, 49, 0,1) == 1 );
        REQUIRE( countHAR(1,298, 0,296, 0,297, 0,0) == 0 );
        REQUIRE( countHAR(1,299, 0,  0, 0,298, 0,1) == 1 );
    }
}


TEST_CASE( "Small boards",
           "[values]" )
{
    SECTION( "Various small boards" )
    {
        REQUIRE( countHAR(2,2, 0,0, 1,0, 1,1) ==   0 );
        REQUIRE( countHAR(2,2, 1,0, 1,1, 0,0) ==   1 );
        REQUIRE( countHAR(8,2, 1,0, 1,1, 0,0) ==   0 );
        REQUIRE( countHAR(8,2, 1,0, 0,0, 5,0) ==   0 );
        REQUIRE( countHAR(2,8, 0,1, 1,1, 0,0) ==   0 );
        REQUIRE( countHAR(2,8, 0,1, 0,0, 1,4) ==   0 );
        REQUIRE( countHAR(3,3, 2,0, 1,0, 0,2) ==   1 );
        REQUIRE( countHAR(4,4, 0,2, 2,1, 3,3) ==   0 );
        REQUIRE( countHAR(3,5, 0,0, 1,1, 2,4) ==   0 );
    }
}


TEST_CASE( "Large boards",
           "[values]" )
{
    SECTION( "Various large boards" )
    {
        REQUIRE( countHAR(13, 3,  0,0,  0, 1, 12, 0) == 1024 );
        REQUIRE( countHAR( 6, 6,  5,5,  0, 5,  5, 0) ==  650 );
        REQUIRE( countHAR( 2,19,  0,0,  1,18,  1, 0) ==    1 );
        REQUIRE( countHAR( 9, 4,  8,0,  8, 1,  0, 1) ==  158 );
        REQUIRE( countHAR( 3,12,  2,0,  1, 0,  0,11) ==  512 );
        REQUIRE( countHAR( 7, 5,  0,0,  0, 1,  6, 4) ==  819 );
        REQUIRE( countHAR( 7, 5,  3,1,  2, 4,  6, 3) ==   43 );
        REQUIRE( countHAR(19, 2, 11,0, 12, 0,  0, 0) ==    1 );
        REQUIRE( countHAR(19, 2, 11,0, 12, 0,  0, 1) ==    0 );
    }
}


TEST_CASE( "Slide Examples",
           "[values]" )
{
    SECTION( "Examples from \"Thoughts on Project 4\" slides" )
    {
        REQUIRE( countHAR(4,3, 3,0, 2,0, 3,1) ==     2 );
        REQUIRE( countHAR(3,2, 2,0, 1,0, 2,1) ==     1 );
        REQUIRE( countHAR(4,1, 1,0, 0,0, 3,0) ==     0 );
        REQUIRE( countHAR(6,5, 0,0, 5,0, 0,1) ==   201 );
    }
}

