// dp3.h  SKELETON
// Nicholas ALexeev with 
// contributions from Glenn G. Chappell
// 2019-09-24
//
// For CS 311 Fall 2019
// Header for Project 3 Functions

#ifndef FILE_DP3_H_INCLUDED
#define FILE_DP3_H_INCLUDED

#include <cstddef>     // For std::size_t
#include <functional>  // For std::function


// **************************************************************** // *
// Begin DO-NOT-CHANGE section                                      // *
// Do not alter the lines below                                     // *
// **************************************************************** // *
                                                                    // *
                                                                    // *
// struct LLNode                                                    // *
// Linked List node, with client-specified value type               // *
// Invariants:                                                      // *
//     Either _next is nullptr, or _next points to an LLNode,       // *
//      allocated with new, owned by *this.                         // *
// Requirements on Types:                                           // *
//     ValType must have a copy ctor and a (non-throwing) dctor.    // *
template <typename ValType>                                         // *
struct LLNode {                                                     // *
    ValType   _data;  // Data for this node                         // *
    LLNode *  _next;  // Ptr to next node, or nullptr if none       // *
                                                                    // *
    // The following simplify creation & destruction                // *
                                                                    // *
    // 1- & 2-param ctor                                            // *
    // _data is set to data (given). _next is set to next, if       // *
    // given, or nullptr if not.                                    // *
    // Pre:                                                         // *
    //     theNext, if passed, is either nullptr, or else it points // *
    //      to an LLNode allocated with new, with ownership         // *
    //      transferred to *this.                                   // *
    explicit LLNode(const ValType & data,                           // *
                    LLNode * next = nullptr)                        // *
        :_data(data),                                               // *
         _next(next)                                                // *
    {}                                                              // *
                                                                    // *
    // dctor                                                        // *
    // Does delete on _next.                                        // *
    ~LLNode()                                                       // *
    { delete _next; }                                               // *
                                                                    // *
    // No default ctor, copy, or move.                              // *
    LLNode() = delete;                                              // *
    LLNode(const LLNode & other) = delete;                          // *
    LLNode & operator=(const LLNode & other) = delete;              // *
    LLNode(LLNode && other) = delete;                               // *
    LLNode & operator=(LLNode && other) = delete;                   // *
                                                                    // *
};  // End struct LLNode                                            // *
                                                                    // *
                                                                    // *
// **************************************************************** // *
// End DO-NOT-CHANGE section                                        // *
// Do not alter the lines above                                     // *
// **************************************************************** // *

//pre: accessing _next will not lead to forbidden memory
template <typename ValueType>
ValueType lookup(const LLNode<ValueType> * head,
                 std::size_t index)
{
	if(head==nullptr){
		throw std::out_of_range("out of range");
	}
	const LLNode<ValueType> *current=head;
	for(std::size_t i=0;i<index;i++){
		if(current->_next!=nullptr){
			current=current->_next;
		}else{
			throw std::out_of_range("out of range");
		}
	}
	return (current->_data);
}


// Implementation in source file
void didItThrow(const std::function<void()> & ff,
                bool & threw);

//pre: item fditer is pointing to has < operator
//pre: FDIter has ++ and = copy ctor operator
template <typename FDIter>
bool checkSorted(FDIter first,
                 FDIter last)
{ 
	if(first==last){
		return true;
	}
	FDIter next = first;
	next++;	
	while(next!=last){
		if((*next)<(*first)){
			return false;
		}
		first++;
		next++;
	}
	
	return true;
}


// Implementation in source file
int gcd(int a,
        int b);


#endif  //#ifndef FILE_DP3_H_INCLUDED

