#ifndef KSARRAY
#define KSARRAY
#include <cstdint>
#include <stdio.h>
#include <cstddef>
#include <cstdlib>
#include <stdexcept>
#include <algorithm>
template<typename T>
class KSArray{
	public:

		typedef T value_type;
		typedef std::uint_fast64_t size_type;

	KSArray():_size{8}{
		_makeObjs(_size);
		
	}
	//assumes that size_in can be sucessfully allocated
	KSArray(int size_in):_size{static_cast<size_type>(size_in)}{
		_makeObjs(_size);
	}

	KSArray(int size,T value){
		_makeObjsValue(size,value);	
	}

	KSArray(const KSArray &in){
		operator=(in);
	}
	~KSArray(){
		_freeData();
	}
	
	KSArray(KSArray && in)noexcept{
		_data = in._data;
		_size = in._size;
		in._data=nullptr;
	}
	KSArray& operator=(const KSArray &in){

		printf("copy ctor called\n");
		//ugly I know this iterates through each element in 
		//the target array and copies the item over
		_alloc(in.size());
		T* foo = _data;
		for(size_type i=0;i<_size;i++){
			foo=new T(in[i]);
			foo++;
		}
		std::copy(in.begin(),in.end(),begin());
		return *this;
	}
	KSArray& operator=(KSArray &&in)noexcept{

		printf("move called\n");
		_data = in._data;
		_size = in._size;
		in._data=nullptr;
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
		//return const_cast<const T*>(_data);	
	};
	T* begin(){

		return _data;
	}
	T* end(){
		return _data+(_size);
		//return const_cast<const T*>(_data);	
	};
	const T* end() const{

		return const_cast<T*>(_data+(_size));
	}
	size_t size()const{
		return _size;	
	};
	bool operator==(const KSArray &rhs)const{
		if(rhs.size() != _size){
			return false;
		}else{
			//iterates through both loops 
			//if any value is not the same
			//immediatly returns false
			for(size_type i=0;i<size();i++){
				T foo = rhs[i];
				T bar = _data[i];
				if(foo!=bar){
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
					printf("rhs[index]<_data[index] eval as true\n");
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
		//pointer to data
		T* _data=nullptr;
		//checks if the object owns the data (eg a move ctor was not
		//used on the object)
		//length of array
		size_type _size=0;

		//this constructs objects with default value
		//assumes allocated size is able to be allocated
		void _makeObjs(size_type size)noexcept{
			_size=size;
			_data = (T*) malloc(_size*sizeof(T));
			T* temp_data = _data;
			for(size_type i=0;i<_size;i++){
				temp_data=new T();
				temp_data++;
			}
		}
		//this constructs objects with value of type
		//assumes allocated size is able to be allocated
		void _makeObjsValue(size_type size,T value)noexcept{

			_size=size;
			_data = (T*) malloc(_size*sizeof(T));
			T* temp_data = _data;
			for(size_type i=0;i<size;i++){
				temp_data[0]=value;
				temp_data++;
			}
		}
		//allocates size for array
		//data is zero initilized
		//Pre: none that I know of
		void _alloc(size_type length){
			//if(_data==nullptr){
				_size=length;
				_data = (T*)calloc(_size,sizeof(T));
			//if data is not nullptr destroy all data;
			//}else{
				/*
				for(size_type i=0;i<_size;i++){
					//calling deconstructor on all objs for 
					//saftey sake
					delete &_data[i];
				}*/
				//free(_data);
				//_alloc(length);
			//}
		}
		void _freeData(){
			if(_data!=nullptr){
				for(size_type i=0;i<_size;i++){
					_data[i].~T();
				}
				free(_data);
				_data=nullptr;
				_size=0;
				return;
			}
			return;

		}

};
#endif
