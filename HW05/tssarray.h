#ifndef TSSARRAY
#define TSSARRAY
#include <stdexcept>
#include <algorithm>
//Nicholas Alexeev
//purpose:implement tssarray
//25-08-2019
//licensed under the GPL v3
template <typename T>
class TSSArray{
	public:
		typedef T value_type;
		typedef unsigned int size_type;
		typedef T* iterator;
		typedef T* const_iterator;
		//basic garuntee
		//pre: value_type can be constructed 32 times
		//post: none
		TSSArray():_size(0),_alloc_size(_DEFAULT_SIZE),_data(new value_type[_DEFAULT_SIZE]){};
		TSSArray(size_type s_in):_size(s_in),_alloc_size(s_in),_data(new value_type[s_in]){};
		//strong guarentee
		//pre: in is a valid TSSArray
		//post: none
		TSSArray(TSSArray &in):_size(in.size()),_alloc_size(in.size()),_data(new value_type[in.size()]){
			std::copy(in.begin(),in.end,begin());
		}
		//strong guarentee
		//pre: in is a valid TSSArray
		//post: none
		TSSArray(const TSSArray &in):_size(in.size()),_alloc_size(in.size()),_data(new value_type[in.size()]){
			std::copy(in.begin(),in.end,begin());
		}

		//strong guarentee
		//pre: in is a valid TSSArray
		//post: none
		TSSArray(TSSArray &&in):_size(in.size(),_alloc_size(in.size()),_data(in.begin())noexcept{};
		//strong guarentee
		//pre: in is a valid TSSArray
		//post: none
		TSSArray(const TSSArray &&in):_size(in.size()),_alloc_size(in.size()),_data(in.begin())noexcept{};

		//strong guarentee
		//pre: in is a valid tssarray
		//post: none
		TSSArray operator=(TSSArray &in){
			TSSArray(in);
		}
		//strong guarentee
		//pre: in is a valid tssarray
		//post: none
		TSSArray operator=(const TSSArray &in){
			TSSArray(in);
		}
		//nothrow guarentee
		//pre: in is a valid tssarray
		//post: none
		TSSArray operator=(TSSAray &&in)noexcept{
			TSSArray(in);
		}
		//no throw guarentee
		//pre: in is a valid tssarray
		//post: none
		TSSArray operator=(const TSSAray &&in)noexcept{
			TSSArray(in);
		}
		//strong garuentee
		//pre: i<size()
		//post: none
		TSSArray& operator[](size_type i){
			if(i<size()){
				return _data[i];
			}
			throw std::out_of_range("out of range");
		}
		//strong garuentee
		//pre: i<size()
		//post: none
		const TSSArray& operator[](size_type i){
			if(i<size()){
				return _data[i];
			}
			throw std::out_of_range("out of range");
		}
		//no throw garuentee
		//pre: valid array
		//post: none
		size_type size()noexcept{
			return _size;
		}
		//no throw garuentee
		//pre: valid array
		//post: none
		bool empty()noexcept{
			return _size==0;
		}


		void resize(int size){
			if(size>_size){

				if(size<=_alloc_size){
					for(size_type i=size;i<_alloc_size;i++){
						_data[i]=value_type();
					}
				}else{
					value_type temp* = new value_type[size];
					std::copy(begin(),end(),temp);
					_size=size;
					_alloc_size=size;
				}
			}else{
				for(size_type i=size;i<_size){
					_data->~value_type();
				}
				_size=size;
			}
		}
		void insert(iterator &iterator,value_type& ins){

		}
		

		~TSSArray(){
			delete _data;
		}




	private:
		size_type _size;
		size_type _alloc_size;
		value_type [] _data;
		const size_type _DEFAULT_SIZE=0x20;

}
#endif
