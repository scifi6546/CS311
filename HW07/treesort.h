// treesort.h  SKELETON
// Nicholas Alexeev with contributions from Glenn G. Chappell
// 2019-11-17
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
#include <memory>


// Binary Tree node
// Sort a given range using Treesort.
// Invariants
// Data is valid, left and right node point to valid memory
template <typename T>
class Node{
	public:
		//pre data_in is valid
		//exception neutral
		Node(T&& data_in):data(std::move(data_in)){};
		//exception neutral
		Node(Node<T>* n):data(std::move(n->data)),left(std::move(n->left)),right(std::move(n->right)){};
	T data;
	std::unique_ptr<Node<T>> left=nullptr;
	std::unique_ptr<Node<T>> right=nullptr;
};
//Inserts into binary tree node
//takes ownership of data
//pre: root is valid and modifies root
//post root has new data in it
template <typename T>
void insert(T&& data, Node<T> *root){
	if(data < root->data){
		if(root->left.get()==nullptr){
			root->left=std::make_unique<Node<T>>(new Node<T>(std::move(data)));
			return;
		}
		insert(std::move(data),root->left.get());
	}else{
		if(root->right.get()==nullptr){
			root->right=std::make_unique<Node<T>>(new Node<T>(std::move(data)));
			return;
		}
		insert(std::move(data),root->right.get());
	}
}
//Writes binary tree to iterator
//pre: root is valid data
//post: root has no data in it
template<typename Iter,typename T>
Iter return_list(Iter iter,Node<T> *root){
	if(root->left!=nullptr){
		iter = return_list(iter,root->left.get());
	}
	
	*iter = std::move(root->data);
	iter++;
	if(root->right!=nullptr){
		iter = return_list(iter,root->right.get());
	}
	return iter;
}
// treesort
// Sort a given range using Treesort.
// Pre:
//     Iteraters are Valid
// Requirements on Types:
//     Types have move ctor, operator<
// Exception safety guarantee:
//     Exception Neutral
template<typename FDIter>
void treesort(FDIter first, FDIter last)
{
    using ValType = typename std::iterator_traits<FDIter>::value_type;
    if(first==last)
	    return;
    auto item = first;
    //auto item=std::move_iterator(first);

    struct Node<ValType> *root = new Node<ValType>(std::move(*first));
    item++;

    while(item!=last){
	    auto temp = std::move_iterator(item);
		insert(*temp,root);	
		temp->~ValType();
		item++;
    }
	
    return_list<FDIter,ValType>(first,root);
    delete root;
}


#endif //#ifndef FILE_TREESORT_H_INCLUDED

