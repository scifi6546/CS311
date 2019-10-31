#ifndef TSSARRAY
#define TSSARRAY
#include <stdexcept>
#include <algorithm>
#include <cstddef>
//Nicholas Alexeev
//purpose:implement tssarray
//25-08-2019
//licensed under the GPL v3
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
		explicit TSSArray(size_type s_in=0):_size(s_in),
			_alloc_size(std::max(_size,size_type(_DEFAULT_SIZE))),_data(new value_type[_alloc_size]){};
		//strong guarentee
		//pre: in is a valid TSSArray
		//post: none
		TSSArray(TSSArray &in){
			_size=in.size();
			_alloc_size=_size;
			_data = new value_type[in.size()];
			try{
				std::copy(in.begin(),in.end(),_data);
			}catch(...){
				delete [] _data;
				throw;
			}
		}
		//strong guarentee
		//pre: in is a valid TSSArray
		//post: none
		TSSArray(const TSSArray &in){
			if(this==&in){
				return;
			}
			_size=in.size();
			_alloc_size=_size;
			_data = new value_type[in.size()];
			try{
				std::copy(in.begin(),in.end(),_data);
			}catch(...){
				delete [] _data;
				throw;
			}
		}

		//strong guarentee
		//pre: in is a valid TSSArray
		//post: none
		TSSArray(TSSArray &&in)noexcept{
			swap(in);
		};

		//strong guarentee
		//pre: in is a valid tssarray
		//post: none
		TSSArray& operator=(TSSArray &in){
			if(this==&in){
				return *this;
			}
			_data= new value_type[in.size()];
			try{
				std::copy(in.begin(),in.end(),begin());
			}catch(...){
				delete [] _data;
				throw;
			}
			_alloc_size=in.size();
			_size=_alloc_size;
			return *this;
		}
		//strong guarentee
		//pre: in is a valid tssarray
		//post: none
		TSSArray& operator=(const TSSArray &in){
			_data= new value_type[in.size()];
			
			try{
				std::copy(in.begin(),in.end(),begin());
			}catch(...){
				delete [] _data;
				throw;
			}
			_alloc_size=in.size();
			_size=_alloc_size;
			return *this;
		}
		//nothrow guarentee
		//pre: in is a valid tssarray
		//post: none
		TSSArray& operator=(TSSArray &&in)noexcept{
			swap(in);
			return *this;
			/*
			if(this==&in)
				return *this;
			_data=in._data;
			_alloc_size=in._alloc_size;
			_size=in._size;
			in._size=0;
			in._alloc_size=0;
			in._data=nullptr;
			return *this;*/
		}
		//nothrow guarentee
		//pre: in is a valid tssarray
		//post: none
		/*
		TSSArray& operator=(const TSSArray &&in)noexcept{
			_data=in._data;
			_alloc_size=in._alloc_size;
			_size=in._size;
			in._size=0;
			in._alloc_size=0;
			in._data=nullptr;
			return *this;
		}*/
		//strong garuentee
		//pre: i<size()
		//post: none
		value_type& operator[](size_type i){
			if(i<size()){
				return _data[i];
			}
			throw std::out_of_range("out of range");
		}
		//strong garuentee
		//pre: i<size()
		//post: none
		const value_type& operator[](size_type i)const{
			if(i<size()){
				return _data[i];
			}
			throw std::out_of_range("out of range");
		}
		//no throw garuentee
		//pre: valid array
		//post: none
		const size_type size()const noexcept{
			return _size;
		}
		//no throw garuentee
		//pre: valid array
		//post: none
		bool empty()const noexcept{
			return _size==0;
		}


		//weak gaurentee
		//pre: size is able to be allocated
		void resize(size_type size_in){
			//testing if new size is smaller
			if(size_in<size()){
				for(value_type* i=_data+size_in;i<_data+_size;i++){
					i->~value_type();
				}
				_size=size_in;
			}else{
				//if need to resize
				if(size_in>_alloc_size){

					value_type *temp = new value_type[size_in];
					std::copy(begin(),end(),temp);
					_data= temp;
					_alloc_size=size_in;
					_size=size_in;
				//if space is already allocated just need to run ctors
				}else{
					for(value_type* i=_data+_size;i<_data+size_in;i++){
						i = new value_type();
					}
					_size = size_in;
				}
				
			}
		}
		//weak garuentee
		//pre: iter in range
		iterator insert(iterator iter,const value_type &ins){
			if(iter>end()|| iter<begin()){
				throw std::out_of_range("iterator out of range");
			}
			size_type index=iter-begin();
			resize(size()+1);
			std::rotate(begin() + index, end()-1, end());	
			//std::copy(begin()+index,end(),begin()+index+1);
			_data[index]=ins;

			return index+begin();
		}
		//weak garentee
		//pre: iter in range
		iterator erase(iterator elm){
			if(elm>=begin()&&elm<end()){
				elm->~value_type();
				std::copy(elm+1,end(),elm);
				_size--;
				return elm;
			}
			throw std::out_of_range("iterator out of range");
		}
		//weak garentee
		//pre: data is valid
		iterator begin()noexcept{
			return _data;
		}
		//weak garentee
		//pre: data is valid
		const_iterator begin()const noexcept{
			return _data;
		}
		//weak garentee
		//pre: data is valid
		iterator end()noexcept{
			return _data+_size;
		}
		//weak garentee
		//pre: data is valid
		const_iterator end()const noexcept{
			return _data+_size;
		}
		//weak gaurentee
		//pre: data is valid
		void push_back(const value_type& in){
			if(_size>=_alloc_size){
				resize(size()+1);
				_data[_size-1]=in;
			}else{
				_data[_size]=in;
				_size++;
			}

		}
		void pop_back(){
			if(_size>=1){
				end()->~value_type();
				_size--;
			}
		}
		void swap(TSSArray &in)noexcept{
			if(&in==this)
				return;
			T* temp = in._data;
			size_type t_alloc = in._alloc_size;
			size_type t_size = in._size;


			in._data=_data;
			in._alloc_size=_alloc_size;
			in._size=_size;


			_data=temp;
			_alloc_size=t_alloc;
			_size=t_size;
		}

		

		~TSSArray(){
			if(_data!=nullptr)
				delete[] _data;

		}





	private:
		size_type _size=0;
		size_type _alloc_size=0;
		value_type * _data=nullptr;
		enum def_size:size_type{_DEFAULT_SIZE=0x20};

};
#endif
