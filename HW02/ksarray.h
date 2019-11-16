/*Nicholas Alexeev
 * 2019-09-22
 * purpose: header for KSArray
 */
#ifndef KSARRAY
#define KSARRAY
#include <cstdint>
#include <stdio.h>
#include <cstddef>
#include <cstdlib>
#include <stdexcept>
#include <algorithm>
template<typename T>
//Preconditions:
//Valuetype has a ctor,and operator<
//Enough ram is avaliable to allocate data
//Post:KSArray is filled with data
class KSArray{
	public:

		typedef T value_type;
		typedef std::uint_fast64_t size_type;

	//preconditions:
	//enough ram is free to allocate 8 value_types
	//post: none
	KSArray():_size(8),_data(new value_type[8]){
	}
	//preconditions:enough ram is free to allocate 8 value_types
	//post: none
	KSArray(int size):_size(size),_data(new value_type[size]){
	}
	//pre: enough ram is free to allocate data
	//post: none
	KSArray(int size,T value):_size(size),_data(new value_type[size]){
		std::fill(begin(),end(),value);	
	}
	//pre: in is capable of being copied
	//post: data in this is a deep copy of the data in in
	KSArray(const KSArray &in):_size(in._size),_data(new value_type[in.size()]){
		std::copy(in.begin(),in.end(),begin());
	}
	//pre: none
	//post: data in array is gone forever
	~KSArray(){
		delete [] _data;
		_size=0;
	}
	
	//pre: in is a valid array
	//post: data in in is unusuable
	KSArray(KSArray && in)noexcept:_size(in._size),_data(in._data){
		in._data=nullptr;
		
	}
	//pre: in is valid
	//post: none
	KSArray& operator=(const KSArray &in){
		KSArray temp(in);
		_swap(temp);
		return *this;
	}
	//pre: in is valid
	//post: data in in is unuisuable by in
	KSArray& operator=(KSArray &&in)noexcept{
		_swap(in);
		return *this;
	}
	//preconditions
	//size<obj.size()
	//int is not the best choice for an index
	//because for small types an int may not be 
	//large enough to address all of avalible memory
	const KSArray::value_type& operator[](const int& index_in)const{
		size_type index = (size_type) index_in;
		if(index<_size&&index>=0){
			return _data[index];
		}else{

			throw std::out_of_range("Out of range");
		}
	}
	//pre:index_in is <size()
	T& operator[](const int &index_in){
	
		size_type index = (size_type) index_in;
		if(index<_size && index>=0){
			return _data[index];
		}else{
			throw std::out_of_range("Out of range");
		}
	
	}
	//pre: none
	const T* begin()const{
		return _data;
	};
	//pre none
	//post: the user does not walk of the end of the array
	T* begin(){

		return _data;
	}
	//pre none
	//post: the user does not walk of the end of the array
	T* end(){
		return _data+(_size);
	};
	//pre none
	//post: none
	const T* end() const{

		return _data+(_size);
	}
	//pre: none
	//post: none
	size_type size()const{
		return _size;	
	};
	private:
		void _swap(KSArray &in)noexcept{
			std::swap(_data,in._data);
			std::swap(_size,in._size);
		}
		size_type _size;
		T* _data;


};
//pre: operator== exists for value_type
template <typename T>
bool operator==(const KSArray<T> &lhs,const KSArray<T> &rhs){
	if(rhs.size() != lhs.size()){
		return false;
	}else{
		//iterates through both loops 
		//if any value is not the same
		//immediatly returns false
		for(int i=0;i<rhs.size();i++){
			if(!(rhs[i]==lhs[i])){
				return false;
			}
		}
		return true;
	}
};

//pre: operator== exists for value_type
template <typename T>
bool operator!=(const KSArray<T> &lhs,const KSArray<T> &rhs){
	return !operator==(lhs,rhs);
};
//pre: operator< exists for value_type
template <typename T>
bool operator<(const KSArray<T> &lhs,const KSArray<T> &rhs){
	return std::lexicographical_compare(lhs.begin(),lhs.end(),rhs.begin(),rhs.end());
};
//pre: operator< exists for value_type
template <typename T>
bool operator>(const KSArray<T> &lhs,const KSArray<T> &rhs){
	return std::lexicographical_compare(rhs.begin(),rhs.end(),lhs.begin(),lhs.end());
};

//pre: operator< exists for value_type
template <typename T>
bool operator>=(const KSArray<T> &lhs,const KSArray<T> &rhs){
	size_t index=0;

	while(true){
		if(index<lhs.size()&&index<rhs.size()){
			if(lhs[index]<rhs[index]){
				return false;
			}
			if(rhs[index]<lhs[index]){
				return true;
			}
			index++;
		}else{
			if(index>=lhs.size() && index>=rhs.size()){
				return true;
			}
			if(index>=lhs.size()){
				return false;
			}
			if(index>=rhs.size()){
				return true;
			}
		}
	}
};
//pre: operator< exists for value_type
template <typename T>
bool operator<=(const KSArray<T> &lhs,const KSArray<T> &rhs){
	size_t index=0;
	while(true){
		if(index<lhs.size()&&index<rhs.size()){
			if(rhs[index]<lhs[index]){
				return false;
			}
			if(lhs[index]<rhs[index]){
				return true;
			}
			index++;
		}else{
			if(index>=lhs.size() && index>=rhs.size()){
				return true;
			}
			if(index>=lhs.size()){
				return true;
			}
			if(index>=rhs.size()){
				
				return false;
			}
		}
	}
};
#endif
