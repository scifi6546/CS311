// treesort_test_main.cpp
// Glenn G. Chappell
// 2019-11-10
//
// For CS 311 Fall 2019
// Tests for function template treesort: main program
// For Project 7, Exercise A
// Uses the "Catch" unit-testing framework, version 2
// Requires treesort_test_suites.cpp, catch.hpp, treesort.h

#define CATCH_CONFIG_FAST_COMPILE
                             // Disable some features for faster compile
#define CATCH_CONFIG_RUNNER  // We write our own main
#include "catch.hpp"         // For the "Catch" unit-testing framework
#include <iostream>          // For std::cout, endl, cin


// userPause
// Wait for user to press ENTER: read all chars through first newline.
void userPause()
{
    std::cout.flush();
    while (std::cin.get() != '\n') ;
}


// Main program
// Run all tests. Prompt for ENTER before exiting.
int main(int argc,
         char *argv[])
{
    const std::string tname = "class template treesort"
                              " - CS 311 Proj 7, Ex A";
                             // Printable name for this test suite
    Catch::Session session;  // Primary Catch object
    int catchresult;         // Catch return code; for return by main

    // Handle command line
    catchresult = session.applyCommandLine(argc, argv);

    if (!catchresult)  // Continue only if no command-line error
    {
        // Run test suites
        std::cout << "BEGIN tests for "
                  << tname << std::endl << std::endl;
        catchresult = session.run();
        std::cout << "END tests for "
                  << tname << std::endl << std::endl;
    }

    // Wait for user
    std::cout << "Press ENTER to quit ";
    userPause();

    // Program return value is return code from Catch
    return catchresult;
}

