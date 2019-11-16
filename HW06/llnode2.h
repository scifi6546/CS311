// llnode2.h
// Glenn G. Chappell
// 2019-11-01
//
// For CS 311 Fall 2019
// Singly Linked List Node + Associated Functionality
// Used in Project 6, Exercises A, B
// Based on list2.cpp
// There is no associated source file.

#ifndef FILE_LLNODE2_H_INCLUDED
#define FILE_LLNODE2_H_INCLUDED

#include <iostream>
using std::cout;
using std::endl;
using std::ostream;
#include <cstddef>
using std::size_t;
#include <memory>
using std::unique_ptr;
using std::make_unique;
#include <utility>
using std::move;


// struct LLNode2
// Linked List node, with client-specified value type
// Invariants:
//     Either _next is empty or _next points to an LLNode2 (and thus
//      _next points to an empty-ptr-terminated Linked List of LLNode2).
// Requirements on Types:
//     ValType must have a copy ctor and a (non-throwing) dctor.
template <typename ValType>
struct LLNode2 {
    ValType             _data;  // Data for this node
    unique_ptr<LLNode2> _next;  // Ptr to next node, or empty if none

    // The following simplify creation & destruction

    // 1- & 2-param ctor
    // _data is set to data (given). _next is set to next, if given, or
    // nullptr if not.
    // Strong guarantee
    // Exception neutral
    explicit LLNode2(const ValType & data,
                     unique_ptr<LLNode2> & next = nullptr)
        :_data(data),
         _next(move(next))
    {}

    ~LLNode2() = default;

    // No default ctor, copy, or move.
    LLNode2() = delete;
    LLNode2(const LLNode2 & other) = delete;
    LLNode2 & operator=(const LLNode2 & other) = delete;
    LLNode2(LLNode2 && other) = delete;
    LLNode2 & operator=(LLNode2 && other) = delete;
};


// size
// Given unique_ptr to Linked List, return its size (number of nodes).
// Pre:
//     head is ptr to empty-ptr-terminated Linked List, or is empty.
// Requirements on Types:
//     ValType must have a copy ctor and a (non-throwing) dctor.
// NOTE: The above are the requirements for LLNode2<ValType>; no member
// functions of ValType are actually used here.
// Strong Guarantee
// Exception Neutral
template <typename ValType>
size_t size(const unique_ptr<LLNode2<ValType>> & head)
{
    auto p = head.get();  // Iterates through list
    size_t counter = 0;   // Number of nodes so far
    while (p != nullptr)
    {
        ++counter;
        p = p->_next.get();
    }
    return counter;
}


// is_empty
// Given unique_ptr to Linked List, returns true if the list is empty,
// false otherwise.
// Requirements on Types:
//     ValType must have a copy ctor and a (non-throwing) dctor.
// No Throw Guarantee
// Exception Neutral
template <typename ValType>
bool is_empty(const unique_ptr<LLNode2<ValType>> & head)
{
    return !head;
}


// push_front
// Given unique_ptr to Linked List, and a ValType item, push the item
// onto the front of the list. head becomes a pointer to the new list.
// Pre:
//     head points to empty-ptr-terminated Linked List, or is empty.
// Requirements on Types:
//     ValType must have a copy ctor and a (non-throwing) dctor.
// NOTE: The above are the requirements for LLNode2<ValType>; no member
// functions of ValType are actually used here.
// Strong guarantee
// Exception neutral
template <typename ValType>
void push_front(unique_ptr<LLNode2<ValType>> & head,
                const ValType & item)
{
    head = make_unique<LLNode2<ValType>>(item, head);
}


// print_list
// Given unique_ptr to Linked List, prints it to given output stream --
// or cout, if none is given -- a blank separating items, with a single
// trailing newline.
// Pre:
//     head points to empty-terminated Linked List, or is empty.
// Requirements on Types:
//     ValType must have a copy ctor and a (non-throwing) dctor.
//     ValType must have operator<< (stream insertion).
// Basic Guarantee
// Exception neutral
template <typename ValType>
void print_list(const unique_ptr<LLNode2<ValType>> & head,
                ostream & outstr = cout)
{
    auto p = head.get();
    while (p != nullptr)
    {
        outstr << p ->_data;
        p = p->_next.get();
        if (p != nullptr)
            cout << " ";
    }
    outstr << endl;
}


// pop_front
// Given unique_ptr to Linked List, removes first item from list, if
// list is nonempty. If list is empty, does nothing.
// Pre:
//     head points to empty-ptr-terminated Linked List, or is an empty
//      unique_ptr.
// Requirements on Types:
//     ValType must have a copy ctor and a (non-throwing) dctor.
// Strong Guarantee
// Exception Neutral
template <typename ValType>
void pop_front(unique_ptr<LLNode2<ValType>> & head)
{
    if (head)
        head = move(head->_next);
}


#endif //#ifndef FILE_LLNODE2_H_INCLUDED

