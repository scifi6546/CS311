// treesort.h  SKELETON
// Glenn G. Chappell
// 2019-11-10
//
// For CS 311 Fall 2019
// Header for function template treesort
// There is no associated source file.

#ifndef FILE_TREESORT_H_INCLUDED
#define FILE_TREESORT_H_INCLUDED

#include <iterator>
// For std::iterator_traits
#include <algorithm>
// For std::stable_sort, std::move
#include <vector>
// For std::vector
#include <iterator>
// For std::distance


// treesort
// Sort a given range using Treesort.
// Pre:
//     ???
// Requirements on Types:
//     ???
// Exception safety guarantee:
//     ???
template <typename T>
struct Node{
	T* data=nullptr;
	Node<T>* left=nullptr;
	Node<T>* right=nullptr; 
};
template <typename T>
void insert(T* data, Node<T> &root){
	if(root.data==nullptr){
		root.data=data;
	}else if(*data<*root.data){
		insert(data,*root.left);
	}else{
		insert(data,*root.right);
	}
}
template<typename FDIter>
void treesort(FDIter first, FDIter last)
{
    // ValType is the type that FDIter points to
    using ValType = typename std::iterator_traits<FDIter>::value_type;
    FDIter item=first;
	struct Node<ValType> &root;
    while(item!=last){
		ValType* to_ins = &(*item);
		insert(to_ins,root);	
	}
	
    // THE FOLLOWING IS DUMMY CODE. IT WILL PASS ALL TESTS, BUT IT DOES
    // NOT MEET THE REQUIREMENTS OF THE PROJECT.
    /*
    std::vector<ValType> buff(std::distance(first, last));
    std::move(first, last, buff.begin());
    std::stable_sort(buff.begin(), buff.end());
    std::move(buff.begin(), buff.end(), first);
    */
}


#endif //#ifndef FILE_TREESORT_H_INCLUDED

