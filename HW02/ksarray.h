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
//Post:
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
	~KSArray(){
		delete [] _data;
		_size=0;
	}
	
	KSArray(KSArray && in)noexcept:_size(in._size),_data(in._data){
		in._data=nullptr;
		
	}
	KSArray& operator=(const KSArray &in){
		KSArray temp(in);
		_swap(temp);
		return *this;
	}
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
	T& operator[](const int &index_in){
	
		size_type index = (size_type) index_in;
		if(index<_size && index>=0){
			return _data[index];
		}else{
			throw std::out_of_range("Out of range");
		}
	
	}
	const T* begin()const{
		return _data;
	};
	T* begin(){

		return _data;
	}
	T* end(){
		return _data+(_size);
	};
	const T* end() const{

		return _data+(_size);
	}
	size_t size()const{
		return _size;	
	};
	//preconditions: operator== exists for rhs
	bool operator==(const KSArray &rhs)const{
		if(rhs.size() != _size){
			return false;
		}else{
			//iterates through both loops 
			//if any value is not the same
			//immediatly returns false
			for(size_type i=0;i<size();i++){
				if(!(rhs[i]==_data[i])){
					return false;
				}
			}
			return true;
		}
	};
	bool operator!=(const KSArray &rhs)const{
		return !operator==(rhs);	
	};
	bool operator<(const KSArray &rhs)const{
		return std::lexicographical_compare(begin(),end(),rhs.begin(),rhs.end());
	};
		
	bool operator>(const KSArray &rhs)const{
		return std::lexicographical_compare(rhs.begin(),rhs.end(),begin(),end());
	};
	bool operator>=(const KSArray &rhs)const{
		size_type index=0;

		while(true){
			if(index<_size&&index<rhs.size()){
				if(_data[index]<rhs[index]){
					return false;
				}
				if(rhs[index]<_data[index]){
					return true;
				}
				index++;
			}else{
				if(index>=_size && index>=rhs.size()){
					return true;
				}
				if(index>=_size){
					return false;
				}
				if(index>=rhs.size()){
					return true;
				}
			}
		}
	};
	bool operator<=(const KSArray &rhs)const{
		
		size_type index=0;
		while(true){
			if(index<_size&&index<rhs.size()){
				if(rhs[index]<_data[index]){
					return false;
				}
				if(_data[index]<rhs[index]){
					return true;
				}
				index++;
			}else{
				if(index>=_size && index>=rhs.size()){
					return true;
				}
				if(index>=_size){
					return true;
				}
				if(index>=rhs.size()){
					
					return false;
				}
			}
		}
	};
	private:
		void _swap(KSArray &in)noexcept{
			std::swap(_data,in._data);
			std::swap(_size,in._size);
		}
		size_type _size;
		T* _data;


};
#endif
