#ifndef TSSARRAY
#define TSSARRAY
#include <stdexcept>
#include <algorithm>
#include <cstddef>
//Nicholas Alexeev
//purpose:implement tssarray
//25-08-2019
//tssarray.h
//licensed under the GPL v3

//class invariants
//_data is owned by this and allocated&&free'd by new and delete only
template <typename T>
class TSSArray{
	public:
		typedef T value_type;
		typedef std::size_t size_type;
		typedef T* iterator;
		typedef const T* const_iterator;
		//basic garuntee
		//pre: value_type can be constructed 32 times
		//post: none
		//Exception Neutral
		explicit TSSArray(size_type s_in=0):_size(s_in),
			_alloc_size(std::max(_size,size_type(_DEFAULT_SIZE))),_data(new value_type[_alloc_size]){};
		//strong guarentee
		//pre: in is a valid TSSArray
		//post: none
		//Exception Neutral
		TSSArray(const TSSArray &in){
			operator=(in);
		}

		//strong guarentee
		//pre: in is a valid TSSArray
		//post: none
		//Exception Neutral
		TSSArray(TSSArray &&in)noexcept{
			swap(in);
			in._size=0;
			in._alloc_size=0;
		};

		//strong guarentee
		//pre: in is a valid tssarray
		//post: none
		//Exception Neutral
		TSSArray& operator=(const TSSArray &in){
			value_type *temp = new value_type[in.size()];
			
			try{
				std::copy(in.begin(),in.end(),temp);
			}catch(...){
				delete[] temp;
				_size=0;
				_alloc_size=0;
				throw;
			}
			_alloc_size=in.size();
			_size=_alloc_size;
			std::swap(_data,temp);
			delete[] temp;
			return *this;
		}
		//nothrow guarentee
		//pre: in is a valid tssarray
		//post: none
		//Exception Neutral
		TSSArray& operator=(TSSArray &&in)noexcept{
			swap(in);
			in._size=0;
			in._alloc_size=0;
			return *this;
		}
		//strong garuentee
		//pre: i<size()
		//post: none
		//Exception Neutral
		value_type& operator[](size_type i){
			if(i<size()){
				return _data[i];
			}
			throw std::out_of_range("out of range");
		}
		//strong garuentee
		//pre: i<size()
		//post: none
		//Exception Neutral
		const value_type& operator[](size_type i)const{
			if(i<size()){
				return _data[i];
			}
			throw std::out_of_range("out of range");
		}
		//no throw garuentee
		//pre: valid array
		//post: none
		//Exception Neutral
		const size_type size()const noexcept{
			return _size;
		}
		//no throw garuentee
		//pre: valid array
		//post: none
		//Exception Neutral
		bool empty()const noexcept{
			return _size==0;
		}


		//basic gaurentee
		//pre: size is able to be allocated
		//post: data is allocated with a size >=size_in
		//Exception Neutral
		void resize(size_type size_in){
			//testing if new size is smaller
			if(size_in<=size()){
				_size=size_in;
			}else{
				//if need to resize
				if(size_in>_alloc_size){
					size_type t_size = std::max(5*_alloc_size/3,size_in);
					value_type *temp = new value_type[t_size];
					try{
						std::copy(begin(),end(),temp);
					}catch(...){
						delete[] temp;
						throw;
					}
					std::swap(temp,_data);
					delete[] temp;
					_alloc_size=t_size;
					_size=size_in;
				//if space is already allocated just need to run ctors
				}else{
					std::fill(_data+_size,_data+size_in,value_type());
					_size = size_in;
				}
				
			}
		}
		//basic garentee
		//pre: iter in range
		//Exception Neutral
		iterator insert(iterator iter,const value_type &ins){
			if(iter>end()|| iter<begin()){
				throw std::out_of_range("iterator out of range");
			}
			size_type index=iter-begin();
			resize(size()+1);
			_data[_size-1]=ins;
			std::rotate(begin() + index, end()-1, end());	

			return index+begin();
		}
		//basic garentee
		//pre: iter in range
		//Exception Neutral
		iterator erase(iterator elm){
			if(elm>=begin()&&elm<end()){
				size_type index = elm-begin();
				std::rotate(elm,elm + 1, end());
				resize(size()-1);
				return index+begin();
			}
			throw std::out_of_range("iterator out of range");
		}
		//nothrow guarentee
		//pre: data is valid
		//post: none
		//exception neutral
		iterator begin()noexcept{
			return _data;
		}
		//nothrow guarentee
		//pre: data is valid
		//post: none
		//exception neutral
		const_iterator begin()const noexcept{
			return _data;
		}
		//nothrow guarentee
		//pre: data is valid
		//post: none
		//exception neutral
		iterator end()noexcept{
			return _data+_size;
		}
		//nothrow guarentee
		//pre: data is valid
		//post: none
		//exception neutral
		const_iterator end()const noexcept{
			return _data+_size;
		}
		// gaurentee
		//pre: data is valid
		//exception neutral
		void push_back(const value_type& in){
			insert(end(),in);

		}
		//basic gaurentee
		//pre: data is valid
		//exception neutral
		void pop_back(){
			if(_size>=1){
				end()->~value_type();
				_size--;
			}
		}
		//basic gaurentee
		//pre: data is valid
		//exception neutral
		void swap(TSSArray &in)noexcept{
			if(&in==this)
				return;
			std::swap(_data,in._data);
			std::swap(_size,in._size);
			std::swap(_alloc_size,in._alloc_size);
		}

		

		~TSSArray(){
				delete[] _data;

		}





	private:
		size_type _size=0;
		size_type _alloc_size=0;
		value_type * _data=nullptr;
		enum def_size:size_type{_DEFAULT_SIZE=0x20};

};
#endif
