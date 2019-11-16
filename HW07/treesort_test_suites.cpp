// treesort_test_suites.cpp
// Glenn G. Chappell
// 2019-11-10
//
// For CS 311 Fall 2019
// Tests for function template treesort: test suites
// For Project 7, Exercise A
// Uses the "Catch" unit-testing framework, version 2
// Requires treesort_test_main.cpp, catch.hpp, treesort.h

// Includes for code to be tested
#include "treesort.h"       // For treesort
#include "treesort.h"       // Double inclusion test

#define CATCH_CONFIG_FAST_COMPILE
                           // Disable some features for faster compile
#include "catch.hpp"       // For the "Catch" unit-testing framework

// Additional includes for this test program
#include <cstddef>
using std::size_t;
#include <stdexcept>
using std::runtime_error;
#include <iterator>
using std::advance;
#include <algorithm>
using std::stable_sort;
using std::equal;
#include <vector>
using std::vector;
#include <list>
using std::list;
#include <forward_list>
using std::forward_list;
#include <string>
using std::string;
#include <cmath>
using std::sqrt;
using std::floor;


// *********************************************************************
// Helper Functions/Classes for This Test Program
// *********************************************************************


// class TypeCheck
// This class exists in order to have static member function "check",
// which takes a parameter of a given type, by reference. Objects of
// type TypeCheck<T> cannot be created.
// Usage:
//     TypeCheck<MyType>::check(x)
//      returns true if the type of x is (MyType) or (const MyType),
//      otherwise false.
// Invariants: None.
// Requirements on Types: None.
template<typename T>
class TypeCheck {

private:

    // No default ctor
    TypeCheck() = delete;

    // Uncopyable. Do not define copy/move ctor/assn.
    TypeCheck(const TypeCheck &) = delete;
    TypeCheck(TypeCheck &&) = delete;
    TypeCheck<T> & operator=(const TypeCheck &) = delete;
    TypeCheck<T> & operator=(TypeCheck &&) = delete;

    // Compiler-generated dctor is used (but irrelevant).
    ~TypeCheck() = default;

public:

    // check
    // The function and function template below simulate a single
    // function that takes a single parameter, and returns true iff the
    // parameter has type T or (const T).

    // check (reference-to-const T)
    // Pre: None.
    // Post:
    //     Return is true.
    // Does not throw (No-Throw Guarantee)
    static bool check([[maybe_unused]] const T & param)
    {
        return true;
    }

    // check (reference-to-const non-T)
    // Pre: None.
    // Post:
    //     Return is false.
    // Requirements on types: None.
    // Does not throw (No-Throw Guarantee)
    template <typename OtherType>
    static bool check([[maybe_unused]] const OtherType & param)
    {
        return false;
    }

};  // End class TypeCheck


// class MovableCounter
// Item type for counting ctor, dctor, op= calls, counting existing
//  objects, and possibly throwing on copy. Has operator< (which always
//  returns false), allowing it to be the value type of a sorted container.
// If static member _copyThrow is set, then copy ctor and copy assn throw
//  std::runtime_error. Exception object's "what" member is set to "C" by
//  the copy ctor and "A" by copy assn.
// Increments static data member _ctorCount on default construction and
//  successful copy construction. Increments static data member _assnCount
//  on successful copy assignment. Increments static data member
//  _dctorCount on destruction.
// Increments static data member _existing on construction, and decrements
//  it on destruction.
// Static data member _maxExisting is highest value of _existing since last
//  reset, or start of program if reset has never been called.
// Invariants:
//     MovableCounter::_existing is number of existing objects of this class.
//     MovableCounter::_ctorCount is number of successful ctor calls since
//      most recent call to reset, or start of program if reset has never
//      been called.
//     MovableCounter::_dctorCount is (similarly) number of dctor calls.
//     MovableCounter::_assnCount is (similarly) number of copy assn calls.
//     MovableCounter::_maxExisting is (similarly) highest value _existing has
//      assumed.
class MovableCounter {

// ***** MovableCounter: Ctors, dctor, op= *****
public:

    // Default ctor
    // Pre: None.
    // Post:
    //     (_ctorCount has been incremented.)
    //     (_existing has been incremented.)
    // Does not throw (No-Throw Guarantee)
    MovableCounter()
    {
        ++_existing;
        if (_existing > _maxExisting)
            _maxExisting = _existing;
        ++_ctorCount;
    }

    // Dctor
    // Pre: None.
    // Post:
    //     (_dctorCount has been incremented.)
    //     (_existing has been decremented.)
    // Does not throw (No-Throw Guarantee)
    ~MovableCounter()
    {
        --_existing;
        ++_dctorCount;
    }

    // Copy ctor
    // Throws std::runtime_error if _copyThrow.
    // Pre: None.
    // Post:
    //     (_ctorCount has been incremented.)
    //     (_existing has been incremented.)
    // May throw std::runtime_error
    // Strong Guarantee
    MovableCounter(const MovableCounter & other)
    {
        (void)other;  // Avoid unused-parameter warning
        if (_copyThrow)
            throw runtime_error("C");
        ++_existing;
        if (_existing > _maxExisting)
            _maxExisting = _existing;
        ++_ctorCount;
    }

    // Copy assignment
    // Throws std::runtime_error if _copyThrow.
    // Pre: None.
    // Post:
    //     Return value is *this.
    //     (_assnCount has been incremented.)
    // May throw std::runtime_error
    // Strong Guarantee
    MovableCounter & operator=([[maybe_unused]] const MovableCounter & rhs)
    {
        if (_copyThrow)
            throw runtime_error("A");
        ++_assnCount;
        return *this;
    }

    // Move ctor
    // Pre: None.
    // Post:
    //     (_ctorCount has been incremented.)
    //     (_existing has been incremented.)
    // No-Throw Guarantee
    MovableCounter(MovableCounter && other) noexcept
    {
        (void)other;  // Avoid unused-parameter warning
        ++_existing;
        if (_existing > _maxExisting)
            _maxExisting = _existing;
        ++_ctorCount;
    }

    // Move assignment
    // Pre: None.
    // Post:
    //     Return value is *this.
    //     (_assnCount has been incremented.)
    // No-Throw Guarantee
    MovableCounter & operator=([[maybe_unused]] MovableCounter && rhs)
    {
        ++_assnCount;
        return *this;
    }

// ***** MovableCounter: Functions dealing with count *****
public:

    // reset
    // Pre: None.
    // Post:
    //     _maxExisting == _existing.
    //     _ctorCount == 0.
    //     _dctorCount == 0.
    //     _assnCount == 0.
    //     _copyThrow == shouldThrow.
    // Does not throw (No-Throw Guarantee)
    static void reset(bool shouldThrow = false)
    {
        _maxExisting = _existing;
        _ctorCount = 0;
        _dctorCount = 0;
        _assnCount = 0;
        _copyThrow = shouldThrow;
    }

    // getExisting
    // Pre: None.
    // Post:
    //     return == _existing.
    // Does not throw (No-Throw Guarantee)
    static size_t getExisting()
    { return _existing; }

    // getMaxExisting
    // Pre: None.
    // Post:
    //     return == _maxExisting.
    // Does not throw (No-Throw Guarantee)
    static size_t getMaxExisting()
    { return _maxExisting; }

    // getCtorCount
    // Pre: None.
    // Post:
    //     return == _ctorCount.
    // Does not throw (No-Throw Guarantee)
    static size_t getCtorCount()
    { return _ctorCount; }

    // getDctorCount
    // Pre: None.
    // Post:
    //     return == _dctorCount.
    // Does not throw (No-Throw Guarantee)
    static size_t getDctorCount()
    { return _dctorCount; }

    // getAssnCount
    // Pre: None.
    // Post:
    //     return == _assnCount.
    // Does not throw (No-Throw Guarantee)
    static size_t getAssnCount()
    { return _assnCount; }

    // setCopyThrow
    // Pre: None.
    // Post:
    //     _copyThrow == shouldThrow
    // Does not throw (No-Throw Guarantee)
    static void setCopyThrow(bool shouldThrow)
    { _copyThrow = shouldThrow; }

// ***** MovableCounter: Data Members *****
private:

    static size_t _existing;     // # of existing objects
    static size_t _maxExisting;  // Max # of existing objects
    static size_t _ctorCount;    // # of successful (non-throwing) ctor calls
    static size_t _dctorCount;   // # of dctor calls
    static size_t _assnCount;    // # of successful (non-throwing) copy = calls
    static bool _copyThrow;      // true if copy operations (ctor, =) throw

};  // End class MovableCounter

// Definition of static data member of class MovableCounter
size_t MovableCounter::_existing = size_t(0);
size_t MovableCounter::_maxExisting = size_t(0);
size_t MovableCounter::_ctorCount = size_t(0);
size_t MovableCounter::_dctorCount = size_t(0);
size_t MovableCounter::_assnCount = size_t(0);
bool MovableCounter::_copyThrow = false;


// operator< (MovableCounter)
// Dummy-ish operator<, forming a strict weak order for MovableCounter class
// Returns false (which is legal for a strict weak order; all objects of
//  type MovableCounter are equivalent).
// Pre: None.
// Post:
//     Return value == false.
// Does not throw (No-Throw Guarantee)
bool operator<([[maybe_unused]] const MovableCounter & a,
               [[maybe_unused]] const MovableCounter & b)
{
    return false;
}


// class IntPair
// Holds pair of ints. operator== as usual, operator< only compares
// first item in each pair.
// Invariants: None.
class IntPair {

public:

    // Default ctor, ctor from 1 int, ctor from 2 ints
    // Sets _x, _y to given values; 0 if not given.
    // Pre: None.
    // Post:
    //     _x, _y set as indicated.
    // Does not throw (No-Throw Guarantee)
    explicit IntPair(int theX = 0,
                     int theY = 0)
        :_x(theX),
         _y(theY)
    {}

    ~IntPair() = default;
    IntPair(const IntPair &) = default;
    IntPair(IntPair &&) = default;
    IntPair & operator=(const IntPair &) = default;
    IntPair & operator=(IntPair &&) = default;

    // getX
    // returns _x
    // Pre: None.
    // Post:
    //     Return value == _x.
    // Does not throw (No-Throw Guarantee)
    int getX() const
    { return _x; }

    // getY
    // returns _y
    // Pre: None.
    // Post:
    //     Return value == _y.
    // Does not throw (No-Throw Guarantee)
    int getY() const
    { return _y; }

private:

    int _x;  // First item in pair
    int _y;  // Second item in pair

};  // End class IntPair


// operator== (IntPair)
// The usual == op for a pair: compares both items.
// Pre: None.
// Post:
//     Return value == (a._x == b._x && a._y == b._y).
bool operator==(const IntPair & a,
                const IntPair & b)
{ return a.getX() == b.getX() && a.getY() == b.getY(); }


// operator< (IntPair)
// Calls op< on _x only.
// Pre: None.
// Post:
//     Return value == (a._x == b._x).
bool operator<(const IntPair & a,
               const IntPair & b)
{ return a.getX() < b.getX(); }


// *********************************************************************
// Test Cases
// *********************************************************************


TEST_CASE( "treesort: small lists of int",
           "[actions]" )
{
    const size_t DATASIZE = size_t(20);  // List size
    const vector<int> dataCheck
        { 3, 6, 19, -2, 8, 6, 7, 1, 141, -2,
          -200, 4, 6, 6, 11, -5, 32, 2, 7, 0 };
    //assert (dataCheck.size() == DATASIZE);
    // Sorted data (all but first, last)
    vector<int> dataSorted1(dataCheck.begin(), dataCheck.end());
    stable_sort(dataSorted1.begin()+1, dataSorted1.end()-1);

    // Sorted data (all)
    vector<int> dataSorted2(dataCheck.begin(), dataCheck.end());
    stable_sort(dataSorted2.begin(), dataSorted2.end());

    SECTION( "std::list<int>" )
    {
        {
        INFO( "std::list, empty range" );
        list<int> data_l(dataCheck.begin(), dataCheck.end());
        auto lit1 = data_l.begin();
        advance(lit1, 3);
        auto lit2 = lit1;
        treesort(lit1, lit2);
        REQUIRE( equal(data_l.begin(), data_l.end(), dataCheck.begin()) );
        }

        {
        INFO( "std::list, range of size 1" );
        list<int> data_l(dataCheck.begin(), dataCheck.end());
        auto lit1 = data_l.begin();
        advance(lit1, 3);
        auto lit2 = lit1;
        advance(lit2, 1);
        treesort(lit1, lit2);
        REQUIRE( equal(data_l.begin(), data_l.end(), dataCheck.begin()) );
        }

        {
        INFO( "std::list, larger range" );
        list<int> data_l(dataCheck.begin(), dataCheck.end());
        auto lit1 = data_l.begin();
        advance(lit1, 1);
        auto lit2 = data_l.begin();
        advance(lit2, DATASIZE-1);
        treesort(lit1, lit2);
        REQUIRE( equal(data_l.begin(), data_l.end(), dataSorted1.begin()) );
        }

        {
        INFO( "std::list, entire list" );
        list<int> data_l(dataCheck.begin(), dataCheck.end());
        treesort(data_l.begin(), data_l.end());
        REQUIRE( equal(data_l.begin(), data_l.end(), dataSorted2.begin()) );
        }
    }

    SECTION( "std::forward_list<int>" )
    {
        {
        INFO( "std::forward_list, empty range" );
        forward_list<int> data_l(dataCheck.begin(), dataCheck.end());
        auto lit1 = data_l.begin();
        advance(lit1, 3);
        auto lit2 = lit1;
        treesort(lit1, lit2);
        REQUIRE( equal(data_l.begin(), data_l.end(), dataCheck.begin()) );
        }

        {
        INFO( "std::forward_list, range of size 1" );
        forward_list<int> data_l(dataCheck.begin(), dataCheck.end());
        auto lit1 = data_l.begin();
        advance(lit1, 3);
        auto lit2 = lit1;
        advance(lit2, 1);
        treesort(lit1, lit2);
        REQUIRE( equal(data_l.begin(), data_l.end(), dataCheck.begin()) );
        }

        {
        INFO( "std::forward_list, larger range" );
        forward_list<int> data_l(dataCheck.begin(), dataCheck.end());
        auto lit1 = data_l.begin();
        advance(lit1, 1);
        auto lit2 = data_l.begin();
        advance(lit2, DATASIZE-1);
        treesort(lit1, lit2);
        REQUIRE( equal(data_l.begin(), data_l.end(), dataSorted1.begin()) );
        }

        {
        INFO( "std::forward_list, entire list" );
        forward_list<int> data_l(dataCheck.begin(), dataCheck.end());
        treesort(data_l.begin(), data_l.end());
        REQUIRE( equal(data_l.begin(), data_l.end(), dataSorted2.begin()) );
        }
    }
}


TEST_CASE( "treesort: small lists of string",
           "[actions]" )
{
    const size_t DATASIZE = size_t(20);  // List size
    const vector<string> dataCheck
        { "xyz", "A", "large", "dragon", "waits", "to", "devour", "you",
          "with", "lots", "of", "salt", "and", "pepper", "and", "a",
          "pinch", "of", "oregano", "abc" };
    //assert (dataCheck.size() == DATASIZE);
    // Sorted data (all but first, last)
    vector<string> dataSorted1(dataCheck.begin(), dataCheck.end());
    stable_sort(dataSorted1.begin()+1, dataSorted1.end()-1);

    // Sorted data (all)
    vector<string> dataSorted2(dataCheck.begin(), dataCheck.end());
    stable_sort(dataSorted2.begin(), dataSorted2.end());

    SECTION( "std::list<string>" )
    {
        {
        INFO( "std::list, empty range" );
        list<string> data_l(dataCheck.begin(), dataCheck.end());
        auto lit1 = data_l.begin();
        advance(lit1, 3);
        auto lit2 = lit1;
        treesort(lit1, lit2);
        REQUIRE( equal(data_l.begin(), data_l.end(), dataCheck.begin()) );
        }

        {
        INFO( "std::list, range of size 1" );
        list<string> data_l(dataCheck.begin(), dataCheck.end());
        auto lit1 = data_l.begin();
        advance(lit1, 3);
        auto lit2 = lit1;
        advance(lit2, 1);
        treesort(lit1, lit2);
        REQUIRE( equal(data_l.begin(), data_l.end(), dataCheck.begin()) );
        }

        {
        INFO( "std::list, larger range" );
        list<string> data_l(dataCheck.begin(), dataCheck.end());
        auto lit1 = data_l.begin();
        advance(lit1, 1);
        auto lit2 = data_l.begin();
        advance(lit2, DATASIZE-1);
        treesort(lit1, lit2);
        REQUIRE( equal(data_l.begin(), data_l.end(), dataSorted1.begin()) );
        }

        {
        INFO( "std::list, entire list" );
        list<string> data_l(dataCheck.begin(), dataCheck.end());
        treesort(data_l.begin(), data_l.end());
        REQUIRE( equal(data_l.begin(), data_l.end(), dataSorted2.begin()) );
        }
    }

    SECTION( "std::forward_list<string>" )
    {
        {
        INFO( "std::forward_list, empty range" );
        forward_list<string> data_l(dataCheck.begin(), dataCheck.end());
        auto lit1 = data_l.begin();
        advance(lit1, 3);
        auto lit2 = lit1;
        treesort(lit1, lit2);
        REQUIRE( equal(data_l.begin(), data_l.end(), dataCheck.begin()) );
        }

        {
        INFO( "std::forward_list, range of size 1" );
        forward_list<string> data_l(dataCheck.begin(), dataCheck.end());
        auto lit1 = data_l.begin();
        advance(lit1, 3);
        auto lit2 = lit1;
        advance(lit2, 1);
        treesort(lit1, lit2);
        REQUIRE( equal(data_l.begin(), data_l.end(), dataCheck.begin()) );
        }

        {
        INFO( "std::forward_list, larger range" );
        forward_list<string> data_l(dataCheck.begin(), dataCheck.end());
        auto lit1 = data_l.begin();
        advance(lit1, 1);
        auto lit2 = data_l.begin();
        advance(lit2, DATASIZE-1);
        treesort(lit1, lit2);
        REQUIRE( equal(data_l.begin(), data_l.end(), dataSorted1.begin()) );
        }

        {
        INFO( "std::forward_list, entire list" );
        forward_list<string> data_l(dataCheck.begin(), dataCheck.end());
        treesort(data_l.begin(), data_l.end());
        REQUIRE( equal(data_l.begin(), data_l.end(), dataSorted2.begin()) );
        }
    }
}


TEST_CASE( "treesort: object counts",
           "[other]" )
{
    SECTION( "Count additional value-type objects used in sort" )
    {
        MovableCounter::reset();
        const size_t DATASIZE = size_t(100);  // List size
        std::vector<MovableCounter> vc(DATASIZE);
        size_t base_existing = MovableCounter::getExisting();
        treesort(vc.begin(), vc.end());
        size_t add_objs = MovableCounter::getMaxExisting() - base_existing;

        {
        INFO( "At least n additional objects used in sorting" );
        REQUIRE( add_objs >= DATASIZE );
        }

        {
        INFO( "At most 2n+10 additional objects used in sorting" );
        REQUIRE( add_objs <= 2*DATASIZE+10 );
        }
    }

    SECTION( "Check for proper clean-up after sort" )
    {
        MovableCounter::reset();
        const size_t DATASIZE = size_t(200);  // List size
        std::vector<MovableCounter> vc(DATASIZE);
        size_t base_existing = MovableCounter::getExisting();
        treesort(vc.begin(), vc.end());

        {
        INFO( "All additional objects destroyed after sort" );
        REQUIRE( MovableCounter::getExisting() == base_existing );
        }
    }
}


TEST_CASE( "treesort: stability",
           "[actions]" )
{
    SECTION( "treesort is stable" )
    {
        const size_t DATASIZE = size_t(32);  // List size

        std::vector<int> dataX
            { 16,  8,  7,  7,  6, 10, 15,  2,  3, 14,  2, 11,  9, 11,
               3, 15,  4, 10,  8, 16,  3,  1,  1, 12, 14, 13, 12,  4,
               5,  6,  5,  9 };
        //assert (dataX.size() == DATASIZE);
        std::vector<int> dataY
            {  1,  1,  1,  2,  1,  1,  1,  1,  1,  1,  2,  1,  1,  2,
               1,  2,  1,  2,  2,  2,  2,  1,  2,  1,  2,  2,  2,  2,
               1,  2,  2,  2 };
        //assert (dataY.size() == DATASIZE);

        vector<IntPair> vp1(DATASIZE);
        vector<IntPair> vp2;

        {
        INFO( "Treesort is stable - test #1" );
        for (size_t i = 0; i < DATASIZE; ++i)
            vp1[i] = IntPair(dataX[i], dataY[i]);
        vp2 = vp1;
        treesort(vp1.begin(), vp1.end());
        stable_sort(vp2.begin(), vp2.end());
        REQUIRE( equal(vp1.begin(), vp1.end(), vp2.begin()) );
        }

        {
        INFO( "Treesort is stable - test #2" );
        for (size_t i = 0; i < DATASIZE; ++i)
            vp1[i] = IntPair(9-dataX[i], dataY[i]);
        vp2 = vp1;
        treesort(vp1.begin(), vp1.end());
        stable_sort(vp2.begin(), vp2.end());
        REQUIRE( equal(vp1.begin(), vp1.end(), vp2.begin()) );
        }
    }
}


TEST_CASE( "treesort: large lists",
           "[actions]" )
{
    SECTION( "Larger list" )
    {
        const size_t DATASIZE = size_t(1000000);
        vector<int> data;
        const double phi = (1.+sqrt(5.))/2.;

        for (size_t i = 0; i < DATASIZE; ++i)
        {
            double pp = phi * double(i);
            int n = int((pp-floor(pp))*double(DATASIZE));
            data.push_back(n);
        }
        vector<int> data2 = data;

        {
        INFO( "Sorting a list of size " << DATASIZE );
        treesort(data.begin(), data.end());
        stable_sort(data2.begin(), data2.end());
        REQUIRE( equal(data.begin(), data.end(), data2.begin()) );
        }
    }
}

