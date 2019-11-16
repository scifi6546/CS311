// inventoryitem_test_suites.cpp
// Glenn G. Chappell
// 2019-09-02
//
// For CS 311 Fall 2019
// Tests for class InventoryItem: test suites
// For Project 1, Exercise A
// Uses the "Catch" unit-testing framework, version 2
// Requires inventoryitem_test_main.cpp, catch.hpp, inventoryitem.h,
//  inventoryitem.cpp

// Includes for code to be tested
#include "inventoryitem.h" // For class InventoryItem
#include "inventoryitem.h" // Double inclusion test

#define CATCH_CONFIG_FAST_COMPILE
                           // Disable some features for faster compile
#include "catch.hpp"       // For the "Catch" unit-testing framework

// Additional includes for this test program
#include <string>
using std::string;
#include <ostream>
using std::ostream;
#include <sstream>
using std::ostringstream;
#include <cstddef>
using std::size_t;
#include <utility>
using std::move;


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


// *********************************************************************
// Test Cases
// *********************************************************************


TEST_CASE( "Function return types are correct",
           "[types]" )
{
    InventoryItem t1;
    InventoryItem t2;

    SECTION( "Copy assn returns InventoryItem by ref" )
    {
        [[maybe_unused]] InventoryItem & r(t1 = t2);  // By-reference check
        REQUIRE( TypeCheck<InventoryItem>::check(t1 = t2) );
    }

    SECTION( "Move assn returns InventoryItem by ref" )
    {
        InventoryItem t_movable;
        [[maybe_unused]] InventoryItem & r(t1 = move(t_movable));  // By-reference check
        REQUIRE( TypeCheck<InventoryItem>::check(t1 = move(t_movable)) );
    }

    SECTION( "InventoryItem::getName returns string by value" )
    {
        [[maybe_unused]] string && rr(t1.getName());  // by-value check
        REQUIRE( TypeCheck<string>::check(t1.getName()) );
    }

    SECTION( "InventoryItem::getNumber returns int by value" )
    {
        [[maybe_unused]] int && rr(t1.getNumber());  // by-value check
        REQUIRE( TypeCheck<int>::check(t1.getNumber()) );
    }

    SECTION( "InventoryItem::empty returns bool by value" )
    {
        [[maybe_unused]] bool && rr(t1.empty());  // by-value check
        REQUIRE( TypeCheck<bool>::check(t1.empty()) );
    }

    SECTION( "InventoryItem::toString returns string by value" )
    {
        [[maybe_unused]] string && rr(t1.toString());  // by-value check
        REQUIRE( TypeCheck<string>::check(t1.toString()) );
    }

    SECTION( "InventoryItem::operator++ [pre] returns InventoryItem by ref" )
    {
        [[maybe_unused]] InventoryItem & r(++t1);  // By-reference check
        REQUIRE( TypeCheck<InventoryItem>::check(++t1) );
    }

    SECTION( "InventoryItem::operator++ [post] returns InventoryItem by value" )
    {
        [[maybe_unused]] InventoryItem && rr(t1++);  // by-value check
        REQUIRE( TypeCheck<InventoryItem>::check(t1++) );
    }

    SECTION( "InventoryItem::operator-- [pre] returns InventoryItem by ref" )
    {
        [[maybe_unused]] InventoryItem & r(--t1);  // By-reference check
        REQUIRE( TypeCheck<InventoryItem>::check(--t1) );
    }

    SECTION( "InventoryItem::operator-- [post] returns InventoryItem by value" )
    {
        [[maybe_unused]] InventoryItem && rr(t1--);  // by-value check
        REQUIRE( TypeCheck<InventoryItem>::check(t1--) );
    }

    SECTION( "operator==(InventoryItem,InventoryItem) returns bool by value" )
    {
        [[maybe_unused]] bool && rr(t1 == t2);  // by-value check
        REQUIRE( TypeCheck<bool>::check(t1 == t2) );
    }

    SECTION( "operator!=(InventoryItem,InventoryItem) returns bool by value" )
    {
        [[maybe_unused]] bool && rr(t1 != t2);  // by-value check
        REQUIRE( TypeCheck<bool>::check(t1 != t2) );
    }

    SECTION( "operator<<(ostream,InventoryItem) returns ostream by ref" )
    {
        ostringstream ostr;
        [[maybe_unused]] ostream & r(ostr << t1);  // By-reference check
        REQUIRE( TypeCheck<ostream>::check(ostr << t1) );
    }
}


TEST_CASE( "Functions are const-correct (passes if it compiles)",
           "[types]" )
{
    SECTION( "Calling functions on a const InventoryItem object" )
    {
        const InventoryItem tc1;

        [[maybe_unused]] string s1 = tc1.getName();   // InventoryItem::getName
        [[maybe_unused]] int w = tc1.getNumber();  // InventoryItem::getNumber
        [[maybe_unused]] bool b = tc1.empty();        // InventoryItem::empty
        [[maybe_unused]] string s2 = tc1.toString();  // InventoryItem::toString

        REQUIRE( 0 == 0 );           // Section passes if it compiles
    }

    SECTION( "Taking const InventoryItem arguments" )
    {
        const InventoryItem tc1;
        const InventoryItem tc2;

        InventoryItem t3 = tc1;      // Copy ctor
        t3 = tc1;                    // Copy assn

        [[maybe_unused]] bool b1 = (tc1 == tc2);      // op==(InventoryItem,InventoryItem)
        [[maybe_unused]] bool b2 = (tc1 != tc2);      // op!=(InventoryItem,InventoryItem)
        ostringstream ostr;
        ostr << tc1;                 // op<<(ostring,InventoryItem)

        REQUIRE( 0 == 0 );           // Section passes if it compiles
    }

    SECTION( "Taking const string arguments" )
    {
        const string s;

        InventoryItem t(s, 0);       // Data ctor
        t.setName(s);                // InventoryItem::setName

        REQUIRE( 0 == 0 );           // Section passes if it compiles
    }
}


TEST_CASE( "Default-constructed InventoryItem object: blank name, 0 inventory",
           "[objs]" )
{
    InventoryItem t1;

    REQUIRE( t1.getName() == "UNNAMED" );
    REQUIRE( t1.getNumber() == 0 );
    REQUIRE( t1.empty() );

    SECTION( "Set name" )
    {
        t1.setName("abc");

        REQUIRE( t1.getName() == "abc" );
        REQUIRE( t1.getNumber() == 0 );
        REQUIRE( t1.empty() );
    }

    SECTION( "Set inventory" )
    {
        t1.setNumber(20);

        REQUIRE( t1.getName() == "UNNAMED" );
        REQUIRE( t1.getNumber() == 20 );
        REQUIRE( !t1.empty() );
    }

    SECTION( "Set name, inventory" )
    {
        t1.setName("def");
        t1.setNumber(30);

        REQUIRE( t1.getName() == "def" );
        REQUIRE( t1.getNumber() == 30 );
        REQUIRE( !t1.empty() );
    }

    SECTION( "Set inventory, name" )
    {
        t1.setNumber(40);
        t1.setName("ghi");

        REQUIRE( t1.getName() == "ghi" );
        REQUIRE( t1.getNumber() == 40 );
        REQUIRE( !t1.empty() );
    }
}


TEST_CASE( "Data-constructed InventoryItem object",
           "[objs]" )
{
    InventoryItem t1("xyz", 100);

    REQUIRE( t1.getName() == "xyz" );
    REQUIRE( t1.getNumber() == 100 );
    REQUIRE( !t1.empty() );

    SECTION( "Set name" )
    {
        t1.setName("abc");

        REQUIRE( t1.getName() == "abc" );
        REQUIRE( t1.getNumber() == 100 );
        REQUIRE( !t1.empty() );
    }

    SECTION( "Set inventory" )
    {
        t1.setNumber(20);

        REQUIRE( t1.getName() == "xyz" );
        REQUIRE( t1.getNumber() == 20 );
        REQUIRE( !t1.empty() );
    }

    SECTION( "Set name, inventory" )
    {
        t1.setName("def");
        t1.setNumber(30);

        REQUIRE( t1.getName() == "def" );
        REQUIRE( t1.getNumber() == 30 );
        REQUIRE( !t1.empty() );
    }

    SECTION( "Set inventory, name" )
    {
        t1.setNumber(40);
        t1.setName("ghi");

        REQUIRE( t1.getName() == "ghi" );
        REQUIRE( t1.getNumber() == 40 );
        REQUIRE( !t1.empty() );
    }
}


TEST_CASE( "Copied InventoryItem objects",
           "[objs]" )
{
    SECTION( "Copy-constructed InventoryItem object" )
    {
        InventoryItem t1("xyz", 100);
        InventoryItem t2 = t1;

        REQUIRE( t1.getName() == "xyz" );
        REQUIRE( t1.getNumber() == 100 );
        REQUIRE( !t1.empty() );
        REQUIRE( t2.getName() == "xyz" );
        REQUIRE( t2.getNumber() == 100 );
        REQUIRE( !t2.empty() );

        t2.setName("abc");
        t2.setNumber(10);

        REQUIRE( t1.getName() == "xyz" );
        REQUIRE( t1.getNumber() == 100 );
        REQUIRE( !t1.empty() );
        REQUIRE( t2.getName() == "abc" );
        REQUIRE( t2.getNumber() == 10 );
        REQUIRE( !t2.empty() );

        t1.setName("def");
        t1.setNumber(20);

        REQUIRE( t1.getName() == "def" );
        REQUIRE( t1.getNumber() == 20 );
        REQUIRE( !t1.empty() );
        REQUIRE( t2.getName() == "abc" );
        REQUIRE( t2.getNumber() == 10 );
        REQUIRE( !t2.empty() );
    }

    SECTION( "Copy-assigned InventoryItem object" )
    {
        InventoryItem t1("xyz", 100);
        InventoryItem t2;
        t2 = t1;

        REQUIRE( t1.getName() == "xyz" );
        REQUIRE( t1.getNumber() == 100 );
        REQUIRE( !t1.empty() );
        REQUIRE( t2.getName() == "xyz" );
        REQUIRE( t2.getNumber() == 100 );
        REQUIRE( !t2.empty() );

        t2.setName("abc");
        t2.setNumber(10);

        REQUIRE( t1.getName() == "xyz" );
        REQUIRE( t1.getNumber() == 100 );
        REQUIRE( !t1.empty() );
        REQUIRE( t2.getName() == "abc" );
        REQUIRE( t2.getNumber() == 10 );
        REQUIRE( !t2.empty() );

        t1.setName("def");
        t1.setNumber(20);

        REQUIRE( t1.getName() == "def" );
        REQUIRE( t1.getNumber() == 20 );
        REQUIRE( !t1.empty() );
        REQUIRE( t2.getName() == "abc" );
        REQUIRE( t2.getNumber() == 10 );
        REQUIRE( !t2.empty() );
    }
}


TEST_CASE( "String conversions",
           "[strings]" )
{
    InventoryItem t1;
    InventoryItem t2("xyz", 100);
    InventoryItem t3("", 0);

    SECTION( "InventoryItem::toString" )
    {
        REQUIRE( t1.toString() == "UNNAMED (0)" );
        REQUIRE( t2.toString() == "xyz (100)" );
        REQUIRE( t3.toString() == " (0)" );
    }

    SECTION( "operator<<(ostream,InventoryItem)" )
    {
        ostringstream ostr1;
        ostr1 << t1;
        REQUIRE( ostr1.str() == "UNNAMED (0)" );
        ostringstream ostr2;
        ostr2 << t2;
        REQUIRE( ostr2.str() == "xyz (100)" );
        ostringstream ostr3;
        ostr3 << t3;
        REQUIRE( ostr3.str() == " (0)" );
    }
}


TEST_CASE( "Increment & decrement",
           "[operators]" )
{
    InventoryItem t1;
    InventoryItem t2("xyz", 10);

    SECTION( "Increment ordinary object" )
    {
        InventoryItem t3 = (++t2);
        REQUIRE( t2.getName() == "xyz" );
        REQUIRE( t2.getNumber() == 11 );
        REQUIRE( !t2.empty() );
        REQUIRE( t3.getName() == "xyz" );
        REQUIRE( t3.getNumber() == 11 );
        REQUIRE( !t3.empty() );

        InventoryItem t4 = (t2++);
        REQUIRE( t2.getName() == "xyz" );
        REQUIRE( t2.getNumber() == 12);
        REQUIRE( !t2.empty() );
        REQUIRE( t4.getName() == "xyz" );
        REQUIRE( t4.getNumber() == 11 );
        REQUIRE( !t4.empty() );

        ++(++t2);
        REQUIRE( t2.getName() == "xyz" );
        REQUIRE( t2.getNumber() == 14 );
        REQUIRE( !t2.empty() );
    }

    SECTION( "Increment object with zero inventory" )
    {
        ++t1;
        REQUIRE( t1.getName() == "UNNAMED" );
        REQUIRE( t1.getNumber() == 1 );
        REQUIRE( !t1.empty() );

        t1++;
        REQUIRE( t1.getName() == "UNNAMED" );
        REQUIRE( t1.getNumber() == 2 );
        REQUIRE( !t1.empty() );
    }

    SECTION( "Decrement ordinary object" )
    {
        InventoryItem t3 = (--t2);
        REQUIRE( t2.getName() == "xyz" );
        REQUIRE( t2.getNumber() == 9 );
        REQUIRE( !t2.empty() );
        REQUIRE( t3.getName() == "xyz" );
        REQUIRE( t3.getNumber() == 9 );
        REQUIRE( !t3.empty() );

        InventoryItem t4 = (t2--);
        REQUIRE( t2.getName() == "xyz" );
        REQUIRE( t2.getNumber() == 8 );
        REQUIRE( !t2.empty() );
        REQUIRE( t4.getName() == "xyz" );
        REQUIRE( t4.getNumber() == 9 );
        REQUIRE( !t4.empty() );

        --(--t2);
        REQUIRE( t2.getName() == "xyz" );
        REQUIRE( t2.getNumber() == 6 );
        REQUIRE( !t2.empty() );
    }

    SECTION( "Decrement object with zero inventory" )
    {
        --t1;
        REQUIRE( t1.getName() == "UNNAMED" );
        REQUIRE( t1.getNumber() == 0 );
        REQUIRE( t1.empty() );

        t1--;
        REQUIRE( t1.getName() == "UNNAMED" );
        REQUIRE( t1.getNumber() == 0 );
        REQUIRE( t1.empty() );
    }
}


TEST_CASE( "Equality & inequality",
           "[operators]" )
{
    InventoryItem t1("abc", 10);  // Base value
    InventoryItem t2("abc", 10);  // Same
    InventoryItem t3("def", 10);  // Different name
    InventoryItem t4("abc", 20);  // Different inventory
    InventoryItem t5("def", 20);  // Different name & inventory

    SECTION( "Equality" )
    {
        REQUIRE( t1 == t1 );
        REQUIRE( t1 == t2 );
        REQUIRE( t2 == t1 );
        REQUIRE( !(t1 == t3) );
        REQUIRE( !(t3 == t1) );
        REQUIRE( !(t1 == t4) );
        REQUIRE( !(t4 == t1) );
        REQUIRE( !(t1 == t5) );
        REQUIRE( !(t5 == t1) );
    }

    SECTION( "Inequality" )
    {
        REQUIRE( !(t1 != t1) );
        REQUIRE( !(t1 != t2) );
        REQUIRE( !(t2 != t1) );
        REQUIRE( t1 != t3 );
        REQUIRE( t3 != t1 );
        REQUIRE( t1 != t4 );
        REQUIRE( t4 != t1 );
        REQUIRE( t1 != t5 );
        REQUIRE( t5 != t1 );
    }
}


TEST_CASE( "Large values",
           "[other]" )
{
    const size_t bigname_len = 1000001;
    string bigname(bigname_len, 'x');  // We make this into a long string

    int biginventory = 2147483641;     // Almost greatest 32-bit signed value

    ostringstream ostr;
    ostr << bigname << " (" << biginventory << ")";
    string bigstringform = ostr.str();
                        // String form of InventoryItem(bigname, biginventory)

    SECTION( "Construction from large values" )
    {
        InventoryItem t1(bigname, biginventory);

        REQUIRE( t1.getName() == bigname );
        REQUIRE( t1.getNumber() == biginventory );
        REQUIRE( !t1.empty() );

        // Check size & prefix first, to avoid enormous error messages
        REQUIRE( t1.toString().size() == bigstringform.size() );
        REQUIRE( t1.toString().substr(0,20) == bigstringform.substr(0,20) );
        REQUIRE( t1.toString() == bigstringform );
    }

    SECTION( "Set functions, passing large values" )
    {
        InventoryItem t1;
        t1.setName(bigname);
        t1.setNumber(biginventory);

        REQUIRE( t1.getName() == bigname );
        REQUIRE( t1.getNumber() == biginventory );
        REQUIRE( !t1.empty() );

        // Check size & prefix first, to avoid enormous error messages
        REQUIRE( t1.toString().size() == bigstringform.size() );
        REQUIRE( t1.toString().substr(0,20) == bigstringform.substr(0,20) );
        REQUIRE( t1.toString() == bigstringform );
    }
}


TEST_CASE( "Same-object tests",
           "[other]" )
{
    SECTION("Copy assignment returns *this")
    {
        InventoryItem t1;
        InventoryItem t2;
        InventoryItem & r(t1 = t2);
        REQUIRE( &r == &t1 );
    }

    SECTION("Move assignment returns *this")
    {
        InventoryItem t1;
        InventoryItem t_movable;
        InventoryItem & r(t1 = move(t_movable));
        REQUIRE( &r == &t1 );
    }

    SECTION("pre-increment returns *this")
    {
        InventoryItem t1;
        InventoryItem & r(++t1);
        REQUIRE( &r == &t1 );
    }

    SECTION("pre-decrement returns *this")
    {
        InventoryItem t1;
        InventoryItem & r(--t1);
        REQUIRE( &r == &t1 );
    }

    SECTION("post-increment returns copy")
    {
        InventoryItem t1;
        InventoryItem && rr1(t1++);
        InventoryItem && rr2(t1++);
        REQUIRE( &rr1 != &t1 );
        REQUIRE( &rr1 != &rr2 );
    }

    SECTION("post-decrement returns copy")
    {
        InventoryItem t1;
        InventoryItem && rr1(t1--);
        InventoryItem && rr2(t1--);
        REQUIRE( &rr1 != &t1 );
        REQUIRE( &rr1 != &rr2 );
    }

    SECTION("getName returns copy")
    {
        InventoryItem t1;
        string && rr1(t1.getName());
        string && rr2(t1.getName());
        REQUIRE( &rr1 != &rr2 );
    }

    SECTION("getNumber returns copy")
    {
        InventoryItem t1;
        int && rr1(t1.getNumber());
        int && rr2(t1.getNumber());
        REQUIRE( &rr1 != &rr2 );
    }

    SECTION("empty returns copy")
    {
        InventoryItem t1;
        bool && rr1(t1.empty());
        bool && rr2(t1.empty());
        REQUIRE( &rr1 != &rr2 );
    }

    SECTION("operator<< returns original stream")
    {
        ostringstream ostr;
        InventoryItem t1;
        ostream & r(ostr << t1);
        REQUIRE( &r == &ostr );
    }
}

