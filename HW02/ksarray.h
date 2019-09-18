#ifndef KSARRAY
#define KSARRAY
#include <cstdint>
#include <cstddef>
#include <cstdlib>
#include <stdexcept>
template<typename T>
class KSArray{
	public:
	KSArray()noexcept:_size{8}{
		_makeObjs(_size);
		
	}
	//assumes that size_in can be sucessfully allocated
	KSArray(int size_in)noexcept:_size{static_cast<size_type>(size_in)}{
		_makeObjs(_size);
	}

	KSArray(int size,T value)noexcept{
		_makeObjsValue(size,value);	
	}

	KSArray(const KSArray &in)noexcept{
		operator=(in);

	}
	~KSArray(){
		if(_data!=NULL){
			free(_data);
			_data=NULL;
		}
		return;
	}
	
	KSArray(KSArray && in)noexcept{
		_data = in.begin();
	}
	KSArray operator=(const KSArray &in){

		//ugly I know this iterates through each element in 
		//the target array and copies the item over
		_alloc(in.size());
		//getting a pointer to the zeroth element
		T* temp_ptr = _data;
		for(int i=0;i<in.size();i++){
			temp_ptr = new T(in[i]);
			temp_ptr++;
		}
		return *this;
	}
	KSArray operator=(KSArray &&in)noexcept{

		_data = in._data;
		return *this;
	}
	//preconditions
	//size<obj.size()
	//int is not the best choice for an index
	//because for small types an int may not be 
	//large enough to address all of avalible memory
	T operator[](const int& index)const{
		if(index<_size){
			return _data[index];
		}
	}
	T& operator[](const int& index){
	
		if(index<_size){
			return _data[index];
		}else{
			throw std::out_of_range("Out of range");
		}
	
	}
	T* begin()const{
		return _data;
		//return const_cast<const T*>(_data);	
	};
	T* end()const{
		return _data+_size;
		//return const_cast<const T*>(_data);	
	};
	size_t size()const{
		return _size;	
	};
	bool operator==(const KSArray &rhs)const{
		if(rhs.size()!=size()){
			return false;
		}else{
			//iterates through both loops 
			//if any value is not the same
			//immediatly returns false
			for(int i=0;i<size();i++){
				if(operator[](i)!=rhs[i]){
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
	
		if(rhs.size()!=size()){
			return false;
		}else{
			//iterates through both loops 
			//if any value is not the same
			//immediatly returns false
			for(int i=0;i<size();i++){
				if(!(operator[](i)<rhs[i])){
					return false;
				}
			}
			return true;
		}
	};
		
	bool operator>(const KSArray &rhs)const{
		if(rhs.size()!=size()){
			return false;
		}else{
			for(int i=0;i<size();i++){
				if(operator[](i)<rhs[i]){
					return false;
				}
			}
			return true;
		}
	};
	bool operator>=(const KSArray &rhs)const{
	
		if(rhs.size()!=size()){
			return false;
		}else{
			for(int i=0;i<size();i++){
				if(operator[](i)<rhs[i]){
					return false;
				}
			}
			return true;
		}
	};
	bool operator<=(const KSArray &rhs)const{
	
		if(rhs.size()!=size()){
			return false;
		}else{
			for(int i=0;i<size();i++){
				if(!(operator[](i)<rhs[i])){
					return false;
				}
			}
			return true;
		}
	};
	typedef T value_type;
	typedef std::uint_fast64_t size_type;
	private:
		//pointer to data
		T* _data=NULL;
		size_type _size=0;

		//this constructs objects with default value
		//assumes allocated size is able to be allocated
		void _makeObjs(size_type size){
			_size=size;
			_data = (T*) malloc(_size*sizeof(T));
			T* temp_data = _data;
			for(size_type i=0;i<size;i++){
				temp_data=new T();
				temp_data++;
			}
		}
		//this constructs objects with value of type
		//assumes allocated size is able to be allocated
		void _makeObjsValue(size_type size,T value){

			_size=size;
			_data = (T*) malloc(_size*sizeof(T));
			T* temp_data = _data;
			for(size_type i=0;i<size;i++){
				temp_data=new T(value);
				temp_data++;
			}
		}
		void _alloc(size_type length){
			if(_data==NULL){
				_size=length;
				_data = (T*)calloc(_size,sizeof(T));
			}else{
				throw std::bad_alloc();
			}
		}

};
#endif
