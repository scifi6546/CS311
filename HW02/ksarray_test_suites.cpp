// ksarray_test_suites.cpp
// Glenn G. Chappell
// 2019-09-11
//
// For CS 311 Fall 2019
// Tests for class template KSArray: test suites
// For Project 2, Exercise A
// Uses the "Catch" unit-testing framework, version 2
// Requires ksarray_test_main.cpp, catch.hpp, ksarray.h

// Includes for code to be tested
#include "ksarray.h"       // For class template KSArray
#include "ksarray.h"       // Double-inclusion check (for testing only)

#define CATCH_CONFIG_FAST_COMPILE
                           // Disable some features for faster compile
#include "catch.hpp"       // For the "Catch" unit-testing framework

// Additional includes for this test program
#include <cstddef>
using std::size_t;
using std::ptrdiff_t;
#include <utility>
using std::move;
#include <vector>
using std::vector;
#include <stdexcept>
using std::runtime_error;
#include <algorithm>
using std::fill;
#include <cassert>
#include <stdio.h>
// For assert


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


// class Counter
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
//     Counter::_existing is number of existing objects of this class.
//     Counter::_ctorCount is number of successful ctor calls since
//      most recent call to reset, or start of program if reset has never
//      been called.
//     Counter::_dctorCount is (similarly) number of dctor calls.
//     Counter::_assnCount is (similarly) number of copy assn calls.
//     Counter::_maxExisting is (similarly) highest value _existing has
//      assumed.
class Counter {

// ***** Counter: Ctors, dctor, op= *****
public:

    // Default ctor
    // Pre: None.
    // Post:
    //     (_ctorCount has been incremented.)
    //     (_existing has been incremented.)
    // Does not throw (No-Throw Guarantee)
    Counter()
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
    ~Counter()
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
    Counter(const Counter & other)
    {
        (void)other;  // Avoid unused-parameter warnings
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
    Counter & operator=([[maybe_unused]] const Counter & rhs)
    {
        if (_copyThrow)
            throw runtime_error("A");
        ++_assnCount;
        return *this;
    }

    // No move operations
    Counter(Counter && other) = delete;
    Counter & operator=(Counter && other) = delete;

// ***** Counter: Functions dealing with count *****
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

// ***** Counter: Data Members *****
private:

    static size_t _existing;     // # of existing objects
    static size_t _maxExisting;  // Max # of existing objects
    static size_t _ctorCount;    // # of successful (non-throwing) ctor calls
    static size_t _dctorCount;   // # of dctor calls
    static size_t _assnCount;    // # of successful (non-throwing) copy = calls
    static bool _copyThrow;      // true if copy operations (ctor, =) throw

};  // End class Counter

// Definition of static data member of class Counter
size_t Counter::_existing = size_t(0);
size_t Counter::_maxExisting = size_t(0);
size_t Counter::_ctorCount = size_t(0);
size_t Counter::_dctorCount = size_t(0);
size_t Counter::_assnCount = size_t(0);
bool Counter::_copyThrow = false;


// operator< (Counter)
// Dummy-ish operator<, forming a strict weak order for Counter class
// Returns false (which is legal for a strict weak order; all objects of
//  type Counter are equivalent).
// Pre: None.
// Post:
//     Return value == false.
// Does not throw (No-Throw Guarantee)
bool operator<([[maybe_unused]] const Counter & a,
               [[maybe_unused]] const Counter & b)
{
    return false;
}


// class OnlyEq
// Item type that has op== and op!= defined, but has no ordered
//  comparison operators.
// Invariants: None.
class OnlyEq {

// ***** Counter: Ctors, dctor, op= *****
public:

    // Auto-generated default ctor & Big 5 used
    OnlyEq() = default;
    ~OnlyEq() = default;
    OnlyEq(const OnlyEq &) = default;
    OnlyEq(OnlyEq &&) = default;
    OnlyEq & operator=(const OnlyEq &) = default;
    OnlyEq & operator=(OnlyEq &&) = default;

};  // End class OnlyEq


// operator== (OnlyEq)
// Dummy-ish operator==. Always returns true.
// Pre: None.
// Post:
//     Return value == true.
// Does not throw (No-Throw Guarantee)
bool operator==([[maybe_unused]] const OnlyEq & a,
                [[maybe_unused]] const OnlyEq & b)
{
    return true;
}


// operator!= (OnlyEq)
// Dummy-ish operator!=. Always returns false.
// Pre: None.
// Post:
//     Return value == false.
// Does not throw (No-Throw Guarantee)
bool operator!=([[maybe_unused]] const OnlyEq & a,
                [[maybe_unused]] const OnlyEq & b)
{
    return false;
}


// *********************************************************************
// Test Cases
// *********************************************************************


const size_t DEFAULTSIZE = 8;  // Size of default-constructed KSArray<T>


TEST_CASE( "Member types (passes if it compiles)",
           "[types]" )
{
    SECTION( "Member type value_type" )
    {
        // value_type (KSArray<int>)
        KSArray<int>::value_type x1;
        [[maybe_unused]] int & r1(x1);

        // value_type (KSArray<double>)
        KSArray<double>::value_type x2;
        [[maybe_unused]] double & r2(x2);

        REQUIRE( true );  // Section passes if it compiles
    }

    SECTION( "Member type size_type" )
    {
        // size_type (KSArray<int>)
        KSArray<int>::size_type x1;
        [[maybe_unused]] size_t & r1(x1);

        // size_type (KSArray<double>)
        KSArray<double>::size_type x2;
        [[maybe_unused]] size_t & r2(x2);

        REQUIRE( true );  // Section passes if it compiles
    }
}


TEST_CASE( "Function return types are correct",
           "[types]" )
{
    KSArray<int> mi1;
    const KSArray<int> cmi2;
    const KSArray<int> cmi3;
    KSArray<double> md4;
    const KSArray<double> cmd5;

    SECTION( "Copy assn returns KSArray by reference" )
    {
        [[maybe_unused]] KSArray<int> & r(mi1 = cmi2);
        REQUIRE( TypeCheck<KSArray<int>>::check(mi1 = cmi2) );
    }

    SECTION( "Move assn returns KSArray by reference" )
    {
        KSArray<int> mi_movable1;
        KSArray<int> mi_movable2;
        [[maybe_unused]] KSArray<int> & r(mi1 = move(mi_movable1));
        REQUIRE( TypeCheck<KSArray<int>>::check(mi1 = move(mi_movable2)) );
    }

    SECTION( "Bracket op (const) returns item by ref-to-const" )
    {
        // Also check KSArray<T>::value_type
        [[maybe_unused]] const int & r1(cmi2[0]);
        REQUIRE( TypeCheck<int>::check(cmi2[0]) );
        [[maybe_unused]] const KSArray<int>::value_type & r2(cmi2[0]);
        REQUIRE( TypeCheck<KSArray<int>::value_type>::check(cmi2[0]) );

        [[maybe_unused]] const double & r3(cmd5[0]);
        REQUIRE( TypeCheck<double>::check(cmd5[0]) );
        [[maybe_unused]] const KSArray<double>::value_type & r4(cmd5[0]);
        REQUIRE( TypeCheck<KSArray<double>::value_type>::check(cmd5[0]) );
    }

    SECTION( "Bracket op (non-const) returns item by ref" )
    {
        // Also check KSArray<T>::value_type
        [[maybe_unused]] int & r1(mi1[0]);
        REQUIRE( TypeCheck<int>::check(mi1[0]) );
        [[maybe_unused]] KSArray<int>::value_type & r2(mi1[0]);
        REQUIRE( TypeCheck<KSArray<int>::value_type>::check(mi1[0]) );

        [[maybe_unused]] double & r3(md4[0]);
        REQUIRE( TypeCheck<double>::check(md4[0]) );
        [[maybe_unused]] KSArray<double>::value_type & r4(md4[0]);
        REQUIRE( TypeCheck<KSArray<double>::value_type>::check(md4[0]) );
    }

    SECTION( "size returns size_type by value" )
    {
        [[maybe_unused]] size_t && r1(cmi2.size());
        REQUIRE( TypeCheck<size_t>::check(cmi2.size()) );
        [[maybe_unused]] KSArray<int>::size_type && r2(cmi2.size());
        REQUIRE( TypeCheck<KSArray<int>::size_type>::check(cmi2.size()) );

        [[maybe_unused]] size_t && r3(cmd5.size());
        [[maybe_unused]] KSArray<int>::size_type && r4(cmd5.size());
        REQUIRE( TypeCheck<size_t>::check(cmd5.size()) );
        REQUIRE( TypeCheck<KSArray<int>::size_type>::check(cmd5.size()) );
    }

    SECTION( "begin (const) returns ptr-to-item by value" )
    {
        [[maybe_unused]] const int * && r1(cmi2.begin());
        REQUIRE( TypeCheck<const int *>::check(cmi2.begin()) );
        [[maybe_unused]] const KSArray<int>::value_type * && r2(cmi2.begin());
        REQUIRE( TypeCheck<const KSArray<int>::value_type *>::check(cmi2.begin()) );

        [[maybe_unused]] const double * && r3(cmd5.begin());
        REQUIRE( TypeCheck<const double *>::check(cmd5.begin()) );
        [[maybe_unused]] const KSArray<double>::value_type * && r4(cmd5.begin());
        REQUIRE( TypeCheck<const KSArray<double>::value_type *>::check(cmd5.begin()) );
    }

    SECTION( "begin (non-const) returns ptr-to-item by value" )
    {
        [[maybe_unused]] int * && r1(mi1.begin());
        REQUIRE( TypeCheck<int *>::check(mi1.begin()) );
        [[maybe_unused]] KSArray<int>::value_type * && r2(mi1.begin());
        REQUIRE( TypeCheck<KSArray<int>::value_type *>::check(mi1.begin()) );

        [[maybe_unused]] double * && r3(md4.begin());
        REQUIRE( TypeCheck<double *>::check(md4.begin()) );
        [[maybe_unused]] KSArray<double>::value_type * && r4(md4.begin());
        REQUIRE( TypeCheck<KSArray<double>::value_type *>::check(md4.begin()) );
    }

    SECTION( "end (const) returns ptr-to-item by value" )
    {
        [[maybe_unused]] const int * && r1(cmi2.end());
        REQUIRE( TypeCheck<const int *>::check(cmi2.end()) );
        [[maybe_unused]] const KSArray<int>::value_type * && r2(cmi2.end());
        REQUIRE( TypeCheck<const KSArray<int>::value_type *>::check(cmi2.end()) );

        [[maybe_unused]] const double * && r3(cmd5.end());
        REQUIRE( TypeCheck<const double *>::check(cmd5.end()) );
        [[maybe_unused]] const KSArray<double>::value_type * && r4(cmd5.end());
        REQUIRE( TypeCheck<const KSArray<double>::value_type *>::check(cmd5.end()) );
    }

    SECTION( "end (non-const) returns ptr-to-item by value" )
    {
        [[maybe_unused]] int * && r1(mi1.end());
        REQUIRE( TypeCheck<int *>::check(mi1.end()) );
        [[maybe_unused]] KSArray<int>::value_type * && r2(mi1.end());
        REQUIRE( TypeCheck<KSArray<int>::value_type *>::check(mi1.end()) );

        [[maybe_unused]] double * && r3(md4.end());
        REQUIRE( TypeCheck<double *>::check(md4.end()) );
        [[maybe_unused]] KSArray<double>::value_type * && r4(md4.end());
        REQUIRE( TypeCheck<KSArray<double>::value_type *>::check(md4.end()) );
    }

    SECTION( "operator== returns bool by value" )
    {
        [[maybe_unused]] bool && r1(cmi2 == cmi3);
        REQUIRE( TypeCheck<bool>::check(cmi2 == cmi3) );
    }

    SECTION( "operator!= returns bool by value" )
    {
        [[maybe_unused]] bool && r1(cmi2 != cmi3);
        REQUIRE( TypeCheck<bool>::check(cmi2 != cmi3) );
    }

    SECTION( "operator< returns bool by value" )
    {
        [[maybe_unused]] bool && r1(cmi2 < cmi3);
        REQUIRE( TypeCheck<bool>::check(cmi2 < cmi3) );
    }

    SECTION( "operator<= returns bool by value" )
    {
        [[maybe_unused]] bool && r1(cmi2 <= cmi3);
        REQUIRE( TypeCheck<bool>::check(cmi2 <= cmi3) );
    }

    SECTION( "operator> returns bool by value" )
    {
        [[maybe_unused]] bool && r1(cmi2 > cmi3);
        REQUIRE( TypeCheck<bool>::check(cmi2 > cmi3) );
    }

    SECTION( "operator>= returns bool by value" )
    {
        [[maybe_unused]] bool && r1(cmi2 >= cmi3);
        REQUIRE( TypeCheck<bool>::check(cmi2 >= cmi3) );
    }
}


TEST_CASE( "Functions take const arguments (passes if it compiles)",
           "[types]" )
{
    SECTION( "Taking const KSArray arguments" )
    {

        const KSArray<int> cmi1;
        const KSArray<int> cmi2;

        KSArray<int> mi3(cmi1);         // Copy ctor
        mi3 = cmi1;                     // Copy assn

        [[maybe_unused]] bool result1 = (cmi1 == cmi2);  // op==(KSArray,KSArray)
        [[maybe_unused]] bool result2 = (cmi1 != cmi2);  // op!=(KSArray,KSArray)
        [[maybe_unused]] bool result3 = (cmi1 <  cmi2);  // op<(KSArray,KSArray)
        [[maybe_unused]] bool result4 = (cmi1 <= cmi2);  // op<=(KSArray,KSArray)
        [[maybe_unused]] bool result5 = (cmi1 >  cmi2);  // op>(KSArray,KSArray)
        [[maybe_unused]] bool result6 = (cmi1 >= cmi2);  // op>=(KSArray,KSArray)

        REQUIRE( true );                // Section passes if it compiles
    }
}


TEST_CASE( "Comparisons allow min-functionality value types (passes if it compiles)",
           "[types]" )
{
    SECTION( "op== allows value types defining only op==, op!=" )
    {
        const KSArray<OnlyEq> cmo1(2);
        const KSArray<OnlyEq> cmo2(2);

        [[maybe_unused]] bool result = (cmo1 == cmo2);

        REQUIRE( true );                // Section passes if it compiles
    }

    SECTION( "op!= allows value types defining only op==, op!=" )
    {
        const KSArray<OnlyEq> cmo1(2);
        const KSArray<OnlyEq> cmo2(2);

        [[maybe_unused]] bool result = (cmo1 != cmo2);

        REQUIRE( true );                // Section passes if it compiles
    }

    SECTION( "op< allows value types defining only op<" )
    {
        const KSArray<Counter> cmc1(2);
        const KSArray<Counter> cmc2(2);

        [[maybe_unused]] bool result = (cmc1 < cmc2);

        REQUIRE( true );                // Section passes if it compiles
    }

    SECTION( "op<= allows value types defining only op<" )
    {
        const KSArray<Counter> cmc1(2);
        const KSArray<Counter> cmc2(2);

        [[maybe_unused]] bool result = (cmc1 <= cmc2);

        REQUIRE( true );                // Section passes if it compiles
    }

    SECTION( "op> allows value types defining only op<" )
    {
        const KSArray<Counter> cmc1(2);
        const KSArray<Counter> cmc2(2);

        [[maybe_unused]] bool result = (cmc1 > cmc2);

        REQUIRE( true );                // Section passes if it compiles
    }

    SECTION( "op>= allows value types defining only op<" )
    {
        const KSArray<Counter> cmc1(2);
        const KSArray<Counter> cmc2(2);

        [[maybe_unused]] bool result = (cmc1 > cmc2);

        REQUIRE( true );                // Section passes if it compiles
    }
}


TEST_CASE( "Checks for noexcept",
           "[types]" )
{
    KSArray<int> mi1;
    KSArray<int> mi2;

    SECTION( "Move ctor is noexcept" )
    {
        REQUIRE( noexcept(KSArray<int>(move(mi1))) );
    }

    SECTION( "Move assn is noexcept" )
    {
        REQUIRE( noexcept(mi2 = move(mi1)) );
    }

    SECTION( "Dctor is noexcept" )
    {
        REQUIRE( noexcept(mi1.~KSArray()) );
    }

    SECTION( "Copy ctor is NOT noexcept" )
    {
        REQUIRE_FALSE( noexcept(KSArray<int>(mi1)) );
    }

    SECTION( "Copy assn is NOT noexcept" )
    {
        REQUIRE_FALSE( noexcept(mi2 = mi1) );
    }

    SECTION( "Default ctor is NOT noexcept" )
    {
        REQUIRE_FALSE( noexcept(KSArray<int>()) );
    }

    SECTION( "Ctor from size is NOT noexcept" )
    {
        REQUIRE_FALSE( noexcept(KSArray<int>(size_t(100))) );
    }
}


TEST_CASE( "Size & ctor from size",
           "[objects]" )
{
    SECTION( "ctor from size (const) #1, check size" )
    {
        const KSArray<int> cmi(1);
        REQUIRE( cmi.size() == size_t(1) );
        REQUIRE( cmi.end()-cmi.begin() == ptrdiff_t(1) );
    }

    SECTION( "ctor from size (const) #2, check size" )
    {
        const KSArray<int> cmi(10);
        REQUIRE( cmi.size() == size_t(10) );
        REQUIRE( cmi.end()-cmi.begin() == ptrdiff_t(10) );
    }

    SECTION( "ctor from size (const) #3, check size" )
    {
        const KSArray<int> cmi(1000000);
        REQUIRE( cmi.size() == size_t(1000000) );
        REQUIRE( cmi.end()-cmi.begin() == ptrdiff_t(1000000) );
    }

    SECTION( "ctor from size (non-const) #1, check size" )
    {
        KSArray<int> mi(0);
        REQUIRE( mi.size() == size_t(0) );
        REQUIRE( mi.end()-mi.begin() == ptrdiff_t(0) );
    }

    SECTION( "ctor from size (non-const) #2, check size" )
    {
        KSArray<int> mi(20);
        REQUIRE( mi.size() == size_t(20) );
        REQUIRE( mi.end()-mi.begin() == ptrdiff_t(20) );
    }
}


TEST_CASE( "Size & ctor from size+value",
           "[objects]" )
{
    SECTION( "ctor from size+value (const) #1, check size & values" )
    {
        const KSArray<int> cmi(1, 42);
        const vector<int> data(1, 42);
		for(int i=0;i<cmi.size();i++){
			printf("%i %i\n",cmi[i],data[i]);
		}
        REQUIRE( cmi.size() == size_t(1) );
        REQUIRE( cmi.end()-cmi.begin() == ptrdiff_t(1) );
        REQUIRE( equal(cmi.begin(), cmi.end(), data.begin()) );
    }

    SECTION( "ctor from size+value (const) #2, check size & values" )
    {
        const KSArray<int> cmi(10, 37);
        const vector<int> data(10, 37);
        REQUIRE( cmi.size() == size_t(10) );
        REQUIRE( cmi.end()-cmi.begin() == ptrdiff_t(10) );
        REQUIRE( equal(cmi.begin(), cmi.end(), data.begin()) );
    }

    SECTION( "ctor from size+value (const) #3, check size & values" )
    {
        const KSArray<int> cmi(1000000, -63);
        const vector<int> data(1000000, -63);
        REQUIRE( cmi.size() == size_t(1000000) );
        REQUIRE( cmi.end()-cmi.begin() == ptrdiff_t(1000000) );
        REQUIRE( equal(cmi.begin(), cmi.end(), data.begin()) );
    }

    SECTION( "ctor from size+value (non-const), check size & values" )
    {
        KSArray<int> mi(20, 111);
        const vector<int> data(20, 111);
        REQUIRE( mi.size() == size_t(20) );
        REQUIRE( mi.end()-mi.begin() == ptrdiff_t(20) );
        REQUIRE( equal(mi.begin(), mi.end(), data.begin()) );
    }
}


TEST_CASE( "Default ctor",
           "[objects]" )
{
    SECTION( "Default ctor gives array of correct size" )
    {
        KSArray<int> cmi;
        REQUIRE( cmi.size() == DEFAULTSIZE );
        REQUIRE( cmi.end()-cmi.begin() == ptrdiff_t(DEFAULTSIZE) );
    }
}


TEST_CASE( "Bracket operator",
           "[operators]" )
{
    bool allgood;  // For results of checking multiple values

    using ST = KSArray<int>::size_type;
    const ST thesize = 100;
    KSArray<int> mi1(thesize);

    // Set all items
    for (auto i = ST(0); i != thesize; ++i)
    {
        mi1[i] = 15-int(i*i);
    }

    SECTION( "Items have values they were set to (use op[])" )
    {
        // Check values of all items
        allgood = true;
        for (auto i = ST(0); i != thesize; ++i)
        {
            if (mi1[i] != 15-int(i*i))
            {
                allgood = false;
                break;
            }
        }
        REQUIRE( allgood );  // All values in array are correct
    }

    SECTION( "Change one item; items have correct values (use op[])" )
    {
        // Change one item
        mi1[2] = 1234;

        // Check values of all items
        allgood = true;
        for (auto i = ST(0); i != thesize; ++i)
        {
            if (mi1[i] != (i == ST(2) ? 1234 : 15-int(i*i)))
            {
                allgood = false;
                break;
            }
        }
        REQUIRE( allgood );  // All values in array are correct (non-const)

        // Make const version and re-check
        const KSArray<int> & cmi2(mi1);
        allgood = true;
        for (auto i = ST(0); i != thesize; ++i)
        {
            if (cmi2[i] != (i == ST(2) ? 1234 : 15-int(i*i)))
            {
                allgood = false;
                break;
            }
        }
        REQUIRE( allgood );  // All values in array are correct (const)
    }
}


TEST_CASE( "Copy ctor",
           "[copy/move]" )
{
    bool allgood;  // For results of checking multiple values

    using ST = KSArray<int>::size_type;
    const ST thesize = 100;
    KSArray<int> mi1(thesize);

    // Set all items
    for (auto i = ST(0); i != thesize; ++i)
    {
        mi1[i] = 15-int(i*i);
    }

    // Make new copy -- COPY CTOR
    KSArray<int> mi2(mi1);

    SECTION( "Copy ctor - copy has correct size" )
    {
        REQUIRE( mi2.size() == thesize );
    }

    SECTION( "Copy ctor - copy has correct values" )
    {
        // Check values in copy
        allgood = true;
        for (auto i = ST(0); i != thesize; ++i)
        {
			printf("req: %i real: %i\n",15-int(i*i),mi2[i]);
            if (mi2[i] != 15-int(i*i))
            {
                allgood = false;
				
                break;
            }
        }
        REQUIRE( allgood );  // All values in copy are correct
    }

    SECTION( "Copy ctor - changing item in original does not affect copy" )
    {
        // Change one item in original
        mi1[2] = 1234;

        // Check values of all items in original
        allgood = true;
        for (auto i = ST(0); i != thesize; ++i)
        {
            if (mi1[i] != (i == ST(2) ? 1234 : 15-int(i*i)))
            {
                allgood = false;
                break;
            }
        }
        REQUIRE( allgood );  // All values in original are correct

        // Check values of all items in copy
        allgood = true;
        for (auto i = ST(0); i != thesize; ++i)
        {
            if (mi2[i] != 15-int(i*i))
            {
                allgood = false;
                break;
            }
        }
        REQUIRE( allgood );  // All values in original are correct
    }

    SECTION( "Copy ctor - changing item in copy does not affect original" )
    {
        // Change one item in copy
        mi2[3] = 4321;

        // Check values of all items in original
        allgood = true;
        for (auto i = ST(0); i != thesize; ++i)
        {
            if (mi1[i] != 15-int(i*i))
            {
                allgood = false;
                break;
            }
        }
        REQUIRE( allgood );  // All values in original are correct

        // Check values of all items in copy
        allgood = true;
        for (auto i = ST(0); i != thesize; ++i)
        {
            if (mi2[i] != (i == ST(3) ? 4321 : 15-int(i*i)))
            {
                allgood = false;
                break;
            }
        }
        REQUIRE( allgood );  // All values in original are correct
    }
}


TEST_CASE( "Copy assignment",
           "[copy/move]" )
{
    bool allgood;  // For results of checking multiple values

    using ST = KSArray<int>::size_type;
    const ST thesize = 100;
    KSArray<int> mi1(thesize);

    // Set all items
    for (auto i = ST(0); i != thesize; ++i)
    {
        mi1[i] = 15-int(i*i);
    }

    // Make new copy -- COPY ASSIGNMENT
    KSArray<int> mi2;
    mi2 = mi1;

    SECTION( "Copy assignment - copy has correct size" )
    {
        REQUIRE( mi2.size() == thesize );
    }

    SECTION( "Copy assignment - copy has correct values" )
    {
        // Check values in copy
        allgood = true;
        for (auto i = ST(0); i != thesize; ++i)
        {
            if (mi2[i] != 15-int(i*i))
            {
                allgood = false;
                break;
            }
        }
        REQUIRE( allgood );  // All values in copy are correct
    }

    SECTION( "Copy assignment - changing item in original does not affect copy" )
    {
        // Change one item in original
        mi1[2] = 1234;

        // Check values of all items in original
        allgood = true;
        for (auto i = ST(0); i != thesize; ++i)
        {
            if (mi1[i] != (i == ST(2) ? 1234 : 15-int(i*i)))
            {
                allgood = false;
                break;
            }
        }
        REQUIRE( allgood );  // All values in original are correct

        // Check values of all items in copy
        allgood = true;
        for (auto i = ST(0); i != thesize; ++i)
        {
            if (mi2[i] != 15-int(i*i))
            {
                allgood = false;
                break;
            }
        }
        REQUIRE( allgood );  // All values in original are correct
    }

    SECTION( "Copy assignment - changing item in copy does not affect original" )
    {
        // Change one item in copy
        mi2[3] = 4321;

        // Check values of all items in original
        allgood = true;
        for (auto i = ST(0); i != thesize; ++i)
        {
            if (mi1[i] != 15-int(i*i))
            {
                allgood = false;
                break;
            }
        }
        REQUIRE( allgood );  // All values in original are correct

        // Check values of all items in copy
        allgood = true;
        for (auto i = ST(0); i != thesize; ++i)
        {
            if (mi2[i] != (i == ST(3) ? 4321 : 15-int(i*i)))
            {
                allgood = false;
                break;
            }
        }
        REQUIRE( allgood );  // All values in original are correct
    }
}


TEST_CASE( "Move ctor",
           "[copy/move]" )
{
    bool allgood;  // For results of checking multiple values

    using ST = KSArray<int>::size_type;
    const ST thesize = 100;
    KSArray<int> mi1(thesize);

    // Set all items
    for (auto i = ST(0); i != thesize; ++i)
    {
        mi1[i] = 15-int(i*i);
    }

    // Make new copy -- MOVE CTOR
    KSArray<int> mi2(move(mi1));

    SECTION( "Move ctor - copy has correct size" )
    {
        REQUIRE( mi2.size() == thesize );
    }

    SECTION( "Move ctor - copy has correct values" )
    {
        // Check values in copy
        allgood = true;
        for (auto i = ST(0); i != thesize; ++i)
        {
            if (mi2[i] != 15-int(i*i))
            {
                allgood = false;
                break;
            }
        }
        REQUIRE( allgood );  // All values in copy are correct
    }

    SECTION( "Move ctor - altering item in copy acts correctly" )
    {
        // Change one item in copy
        mi2[3] = 4321;

        // Check values of all items in copy
        allgood = true;
        for (auto i = ST(0); i != thesize; ++i)
        {
            if (mi2[i] != (i == ST(3) ? 4321 : 15-int(i*i)))
            {
                allgood = false;
                break;
            }
        }
        REQUIRE( allgood );  // All values in original are correct
    }
}


TEST_CASE( "Move assignment",
           "[copy/move]" )
{
    bool allgood;  // For results of checking multiple values

    using ST = KSArray<int>::size_type;
    const ST thesize = 100;
    KSArray<int> mi1(thesize);

    // Set all items
    for (auto i = ST(0); i != thesize; ++i)
    {
        mi1[i] = 15-int(i*i);
    }

    // Make new copy -- MOVE ASSIGNMENT
    KSArray<int> mi2;
    mi2 = move(mi1);

    SECTION( "Move assignment - copy has correct size" )
    {
        REQUIRE( mi2.size() == thesize );
    }

    SECTION( "Move assignment - copy has correct values" )
    {
        // Check values in copy
        allgood = true;
        for (auto i = ST(0); i != thesize; ++i)
        {
            if (mi2[i] != 15-int(i*i))
            {
                allgood = false;
                break;
            }
        }
        REQUIRE( allgood );  // All values in copy are correct
    }

    SECTION( "Move assignment - altering item in copy acts correctly" )
    {
        // Change one item in copy
        mi2[3] = 4321;

        // Check values of all items in copy
        allgood = true;
        for (auto i = ST(0); i != thesize; ++i)
        {
            if (mi2[i] != (i == ST(3) ? 4321 : 15-int(i*i)))
            {
                allgood = false;
                break;
            }
        }
        REQUIRE( allgood );  // All values in original are correct
    }
}


TEST_CASE( "begin & end",
           "[iterators]" )
{
    using ST = KSArray<int>::size_type;
    bool allgood;     // For results of checking multiple values
    ST i;             // Loop counter
    int * it;         // Iterator
    const int * cit;  // Const-iterator

    const ST thesize = 100;
    KSArray<int> mi1(thesize);

    // Set all items
    for (auto i = ST(0); i != thesize; ++i)
    {
        mi1[i] = 15-int(i*i);
    }

    // Make const version (no copy)
    const KSArray<int> & cmi2(mi1);

    SECTION( "Difference of begin(), end() - non-const" )
    {
        REQUIRE( mi1.end() - mi1.begin() == ptrdiff_t(thesize) );

        {
        KSArray<int> m(0);
        REQUIRE(m.end() - m.begin() == ptrdiff_t(0) );
        }

        {
        KSArray<int> m(1);
        REQUIRE(m.end() - m.begin() == ptrdiff_t(1) );
        }

        {
        KSArray<int> m(10);
        REQUIRE(m.end() - m.begin() == ptrdiff_t(10) );
        }

        {
        KSArray<char> m(10);
        REQUIRE(m.end() - m.begin() == ptrdiff_t(10) );
        }
    }

    SECTION( "Using begin, end gives correct values - non-const" )
    {
        // Check values using begin, end
        allgood = true;
        for (it = mi1.begin(), i = 0; it != mi1.end(); ++it, ++i)
        {
            if (*it != 15-int(i*i))
            {
                allgood = false;
                break;
            }
        }
        REQUIRE( allgood );  // All values in copy are correct
    }

    SECTION( "Difference of begin(), end() - const" )
    {
        REQUIRE( cmi2.end() - cmi2.begin() == ptrdiff_t(thesize) );
    }

    SECTION( "Using begin, end gives correct values - const" )
    {
        // Check values using begin, end
        allgood = true;
        for (cit = cmi2.begin(), i = 0; cit != cmi2.end(); ++cit, ++i)
        {
            if (*cit != 15-int(i*i))
            {
                allgood = false;
                break;
            }
        }
        REQUIRE( allgood );  // All values in copy are correct
    }
}


TEST_CASE( "Equality & inequality operators",
           "[operators]" )
{
    using ST = KSArray<int>::size_type;
    const ST thesize = 100;
    KSArray<int> mi1(thesize);

    // Set all items
    for (auto i = ST(0); i != thesize; ++i)
    {
        mi1[i] = 15-int(i*i);
    }

    // Make copy
    KSArray<int> mi2(mi1);

    // Make almost-same version (different size)
    KSArray<int> mi3(thesize-ST(1));
    for (auto i = ST(0); i != thesize-ST(1); ++i)
    {
        mi3[i] = 15-int(i*i);
    }

    // Make almost-same version (different item)
    KSArray<int> mi4(mi1);
    mi4[thesize-ST(2)] = 1234;

    SECTION( "Object equal to self" )
    {
        REQUIRE( mi1 == mi1 );
        REQUIRE_FALSE( mi1 != mi1 );
    }

    SECTION( "Object equal to copy" )
    {
        REQUIRE( mi1 == mi2 );
        REQUIRE_FALSE( mi1 != mi2 );
    }

    SECTION( "Object unequal to almost-same (different size)" )
    {
        REQUIRE_FALSE( mi1 == mi3 );
        REQUIRE( mi1 != mi3 );
    }

    SECTION( "Object unequal to almost-same (different size) REVERSED" )
    {
        REQUIRE_FALSE( mi3 == mi1 );
        REQUIRE( mi3 != mi1 );
    }

    SECTION( "Object unequal to almost-same (different item)" )
    {
        REQUIRE_FALSE( mi1 == mi4 );
        REQUIRE( mi1 != mi4 );
    }

    SECTION( "Object unequal to almost-same (different item) REVERSED" )
    {
        REQUIRE_FALSE( mi4 == mi1 );
        REQUIRE( mi4 != mi1 );
    }
}


TEST_CASE( "Comparisons",
           "[operators]" )
{
    SECTION( "Check all comparisons for non-copies" )
    {
        // Make vector of 10 KSArray<int> objects, in ascending order
        using VST = vector<KSArray<int>>::size_type;
        auto NUM_ARRAYS = VST(10);
        int A = -2147483641;
        int B = 2147483641;
        vector<KSArray<int>> vv;

        {
        KSArray<int> mi(0);
        vv.push_back(mi);
        }

        {
        KSArray<int> mi(1);
        mi[0] = A;
        vv.push_back(mi);
        }

        {
        KSArray<int> mi(2);
        fill(mi.begin(), mi.end(), A);
        vv.push_back(mi);
        }

        {
        KSArray<int> mi(99);
        fill(mi.begin(), mi.end(), A);
        vv.push_back(mi);
        }

        {
        KSArray<int> mi(100);
        fill(mi.begin(), mi.end(), A);
        vv.push_back(mi);
        }

        {
        KSArray<int> mi(100);
        fill(mi.begin(), mi.end(), A);
        mi[90] = B;
        vv.push_back(mi);
        }

        {
        KSArray<int> mi(2);
        mi[0] = A;
        mi[1] = B;
        vv.push_back(mi);
        }

        {
        KSArray<int> mi(1);
        mi[0] = B;
        vv.push_back(mi);
        }

        {
        KSArray<int> mi(2);
        mi[0] = B;
        mi[1] = A;
        vv.push_back(mi);
        }

        {
        KSArray<int> mi(2);
        fill(mi.begin(), mi.end(), B);
        vv.push_back(mi);
        }

        assert (vv.size() == NUM_ARRAYS);

        for (auto i = VST(0); i != NUM_ARRAYS; ++i)
        {
            for (auto j = VST(0); j != NUM_ARRAYS; ++j)
            {
                REQUIRE( (vv[i] <  vv[j]) == (i <  j) );
                REQUIRE( (vv[i] <= vv[j]) == (i <= j) );
                REQUIRE( (vv[i] >  vv[j]) == (i >  j) );
                REQUIRE( (vv[i] >= vv[j]) == (i >= j) );
                REQUIRE( (vv[i] == vv[j]) == (i == j) );
                REQUIRE( (vv[i] != vv[j]) == (i != j) );
            }
        }
    }

    SECTION( "Check all order comparisons for copies" )
    {
        KSArray<int> mi1(100);
        fill(mi1.begin(), mi1.end(), 42);
        KSArray<int> mi2(mi1);

        REQUIRE_FALSE( mi1 < mi2 );
        REQUIRE( mi1 <= mi2 );
        REQUIRE_FALSE( mi1 > mi2 );
        REQUIRE( mi1 >= mi2 );
    }
}


TEST_CASE( "Same-object tests",
           "[other]" )
{
    SECTION( "Copy ctor creates object with copy of array" )
    {
        KSArray<int> mi1(1);
        int * addr1 = &(mi1[0]);
        KSArray<int> mi2(mi1);
        REQUIRE_FALSE( &(mi2[0]) == addr1 );
    }
    SECTION( "Copy ctor does not reallocate original array" )
    {
        KSArray<int> mi1(1);
        int * addr1 = &(mi1[0]);
        KSArray<int> mi2(mi1);
        REQUIRE( &(mi1[0]) == addr1 );
    }

    SECTION( "Move ctor creates object with original array" )
    {
        KSArray<int> mi_movable(1);
        int * addr1 = &(mi_movable[0]);
        KSArray<int> mi2(move(mi_movable));
        REQUIRE( &(mi2[0]) == addr1 );
    }

    SECTION( "Copy assignment returns *this" )
    {
        KSArray<int> mi1(1);
        KSArray<int> mi2;
        KSArray<int> & r(mi2 = mi1);
        REQUIRE( &r == &mi2 );
    }

    SECTION( "Copy assignment results in object with copy of array" )
    {
        KSArray<int> mi1(1);
        int * addr1 = &(mi1[0]);
        KSArray<int> mi2;
        mi2 = mi1;
        REQUIRE_FALSE( &(mi2[0]) == addr1 );
    }
    SECTION( "Copy assignment does not reallocate original array" )
    {
        KSArray<int> mi1(1);
        int * addr1 = &(mi1[0]);
        KSArray<int> mi2;
        mi2 = mi1;
        REQUIRE( &(mi1[0]) == addr1 );
    }

    SECTION( "Move assignment returns *this" )
    {
        KSArray<int> mi_movable(1);
        KSArray<int> mi2;
        KSArray<int> & r(mi2 = move(mi_movable));
        REQUIRE( &r == &mi2 );
    }

    SECTION( "Move assignment results in object with original array" )
    {
        KSArray<int> mi_movable(1);
        int * addr1 = &(mi_movable[0]);
        KSArray<int> mi2;
        mi2 = move(mi_movable);
        REQUIRE( &(mi2[0]) == addr1 );
    }

    SECTION ("size returns copy" )
    {
        KSArray<int> mi(1);
        KSArray<int>::size_type && rr1(mi.size());
        KSArray<int>::size_type && rr2(mi.size());
        REQUIRE_FALSE( &rr1 == &rr2 );
    }

    SECTION ( "Bracket op (const) returns original item" )
    {
        const KSArray<int> mi(1);
        const int & r1(mi[0]);
        const int & r2(mi[0]);
        REQUIRE( &r1 == &r2 );
    }

    SECTION ( "Bracket op (non-const) returns original item" )
    {
        KSArray<int> mi(1);
        int & r1(mi[0]);
        int & r2(mi[0]);
        REQUIRE( &r1 == &r2 );
    }

    SECTION ( "begin (const) returns pointer to original array" )
    {
        const KSArray<int> mi(1);
        const int * addr1(mi.begin());
        const int * addr2(mi.begin());
        REQUIRE( addr1 == addr2 );
    }

    SECTION ( "begin (non-const) returns pointer to original array" )
    {
        KSArray<int> mi(1);
        int * addr1(mi.begin());
        int * addr2(mi.begin());
        REQUIRE( addr1 == addr2 );
    }

    SECTION ( "end (const) returns pointer to end of original array" )
    {
        const KSArray<int> mi(1);
        const int * addr1(mi.end());
        const int * addr2(mi.end());
        REQUIRE( addr1 == addr2 );
    }

    SECTION ( "end (non-const) returns pointer to end of original array" )
    {
        KSArray<int> mi(1);
        int * addr1(mi.end());
        int * addr2(mi.end());
        REQUIRE( addr1 == addr2 );
    }
}


TEST_CASE( "Ctor/dctor/assignment count",
           "[other]" )
{
    size_t thesize = 100;

    SECTION( "Creation & destruction: ctor/dctor count" )
    {
        Counter::reset();
        { // Block, so we get dctor calls before function ends
            const KSArray<Counter> mc(thesize);

            // Count value-type default ctor calls due to array creation
            REQUIRE( Counter::getCtorCount() == thesize );

            Counter::reset();
        }
        // Count value-type dctor calls due to array destruction
        REQUIRE( Counter::getDctorCount() == thesize );
    }

    SECTION( "Copy construction: ctor/assignment count" )
    {
        KSArray<Counter> mc1(thesize);
        Counter::reset();

        const KSArray<Counter> mc2(mc1);  // Copy construction
        REQUIRE( Counter::getCtorCount() == thesize );
        REQUIRE( Counter::getAssnCount() == thesize );

        // Ensure compiler will not decide mc1 is movable
        Counter c;
        mc1[0] = c;
    }

    SECTION( "Copy assignment: ctor/assignment count" )
    {
        KSArray<Counter> mc1(thesize);
        KSArray<Counter> mc2;
        Counter::reset();

        mc2 = mc1;  // Copy assignment
        REQUIRE( Counter::getCtorCount() == thesize );
        REQUIRE( Counter::getAssnCount() == thesize );

        // Ensure compiler will not decide mc1 is movable
        Counter c;
        mc1[0] = c;
    }
}


TEST_CASE( "Ctor/dctor/assignment count - IMPROVED",
           "[other]" )
{
    const size_t thesize = 1000;   // Arbitrary size for our tests
    Counter val;                   // Value-type object to pass
    size_t c1, d1, a1;             // Ctor, dctor, assn counts #1
    size_t c2, d2, a2;             // Ctor, dctor, assn counts #2
    const size_t slop = 2;         // How far off counts may be

   Counter::reset();               // Restart all counts

    SECTION( "Default ctor: value-type ctor/dctor/assignment counts" )
    {
        size_t c1, d1, a1;  // No. of calls to value-type ops

        {  // Block, so we get dctor calls before function ends
            const KSArray<Counter> mc1;

            // Count value-type operations due to construction
            c1 = Counter::getCtorCount();
            d1 = Counter::getDctorCount();
            a1 = Counter::getAssnCount();
            REQUIRE( c1 >= DEFAULTSIZE );
            REQUIRE( c1 <= DEFAULTSIZE+slop );
            REQUIRE( d1 <= 0+slop );
            REQUIRE( a1 <= 0+slop );

            Counter::reset();
        }
        // Count value-type operations due to destruction
        c2 = Counter::getCtorCount();
        d2 = Counter::getDctorCount();
        a2 = Counter::getAssnCount();
        REQUIRE( c2 == 0 );
        REQUIRE( d2 == c1-d1 );
        REQUIRE( a2 == 0 );
    }

    SECTION( "Ctor from size: value-type ctor/dctor/assignment counts" )
    {
        {  // Block, so we get dctor calls before function ends
            const KSArray<Counter> mc1(thesize);

            // Count value-type operations due to construction
            c1 = Counter::getCtorCount();
            d1 = Counter::getDctorCount();
            a1 = Counter::getAssnCount();
            REQUIRE( c1 >= thesize );
            REQUIRE( c1 <= thesize+slop );
            REQUIRE( d1 <= 0+slop );
            REQUIRE( a1 <= 0+slop );

            Counter::reset();
        }
        // Count value-type operations due to destruction
        c2 = Counter::getCtorCount();
        d2 = Counter::getDctorCount();
        a2 = Counter::getAssnCount();
        REQUIRE( c2 == 0 );
        REQUIRE( d2 == c1-d1 );
        REQUIRE( a2 == 0 );
    }

    SECTION( "Copy ctor: value-type ctor/dctor/assignment counts" )
    {
        {  // Block, so we get dctor calls before function ends
            const KSArray<Counter> mc1(thesize);

            const KSArray<Counter> mc2(mc1);  // Copy ctor

            c1 = Counter::getCtorCount();
            d1 = Counter::getDctorCount();
            a1 = Counter::getAssnCount();
            REQUIRE( c1 >= thesize+thesize );
            REQUIRE( c1 <= thesize+thesize+slop );
            REQUIRE( d1 <= 0+0+slop );
            REQUIRE( a1 >= 0+thesize );
            REQUIRE( a1 <= 0+thesize+slop );
            // Values above: # from size ctor + # from copy ctor

            Counter::reset();
        }
        // Count value-type operations due to destruction
        c2 = Counter::getCtorCount();
        d2 = Counter::getDctorCount();
        a2 = Counter::getAssnCount();
        REQUIRE( c2 == 0 );
        REQUIRE( d2 == c1-d1 );
        REQUIRE( a2 == 0 );
    }

    SECTION( "Move ctor: value-type ctor/dctor/assignment counts" )
    {
        {  // Block, so we get dctor calls before function ends
            KSArray<Counter> mc1(thesize);
                // Non-const, so move(mc1) makes it movable.

            const KSArray<Counter> mc2(move(mc1));  // Move ctor

            c1 = Counter::getCtorCount();
            d1 = Counter::getDctorCount();
            a1 = Counter::getAssnCount();
            REQUIRE( c1 >= thesize+0 );
            REQUIRE( c1 <= thesize+0+slop );
            REQUIRE( d1 <= 0+0+slop );
            REQUIRE( a1 <= 0+0+slop );
            // Values above: # from size ctor + # from move ctor

            Counter::reset();
        }
        // Count value-type operations due to destruction
        c2 = Counter::getCtorCount();
        d2 = Counter::getDctorCount();
        a2 = Counter::getAssnCount();
        REQUIRE( c2 == 0 );
        REQUIRE( d2 == c1-d1 );
        REQUIRE( a2 == 0 );
    }

    SECTION( "Copy assignment: value-type ctor/dctor/assignment counts" )
    {
        {  // Block, so we get dctor calls before function ends
            const KSArray<Counter> mc1(thesize);
            KSArray<Counter> mc2;

            mc2 = mc1;  // Copy assn

            c1 = Counter::getCtorCount();
            d1 = Counter::getDctorCount();
            a1 = Counter::getAssnCount();
            REQUIRE( c1 >= (thesize+DEFAULTSIZE)+thesize );
            REQUIRE( c1 <= (thesize+DEFAULTSIZE)+thesize+slop );
            REQUIRE( d1 >= (0+0)+DEFAULTSIZE );
            REQUIRE( d1 <= (0+0)+DEFAULTSIZE+slop );
            REQUIRE( a1 >= (0+0)+thesize );
            REQUIRE( a1 <= (0+0)+thesize+slop );
            // Values above: (# from size ctor + # from default ctor)
            //                 + # from copy assn

            Counter::reset();
        }
        // Count value-type operations due to destruction
        c2 = Counter::getCtorCount();
        d2 = Counter::getDctorCount();
        a2 = Counter::getAssnCount();
        REQUIRE( c2 == 0 );
        REQUIRE( d2 == c1-d1 );
        REQUIRE( a2 == 0 );
    }

    SECTION( "Move assignment: value-type ctor/dctor/assignment counts" )
    {
        {  // Block, so we get dctor calls before function ends
            KSArray<Counter> mc1(thesize);
                // Non-const, so move(mc1) makes it movable.
            KSArray<Counter> mc2;

            mc2 = move(mc1);  // Move assn

            c1 = Counter::getCtorCount();
            d1 = Counter::getDctorCount();
            a1 = Counter::getAssnCount();
            REQUIRE( c1 >= (thesize+DEFAULTSIZE)+0 );
            REQUIRE( c1 <= (thesize+DEFAULTSIZE)+0+slop );
            REQUIRE( d1 <= (0+0)+0+slop );
            REQUIRE( a1 <= (0+0)+0+slop );
            // Values above: # from size ctor + # from move ctor

            Counter::reset();
        }
        // Count value-type operations due to destruction
        c2 = Counter::getCtorCount();
        d2 = Counter::getDctorCount();
        a2 = Counter::getAssnCount();
        REQUIRE( c2 == 0 );
        REQUIRE( d2 == c1-d1 );
        REQUIRE( a2 == 0 );
    }
}

