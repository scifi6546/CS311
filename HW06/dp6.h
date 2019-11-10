#ifndef DP6
#define DP6
#include <algorithm> 
#include "llnode2.h"
template<typename ValType>
void reverseList(unique_ptr<LLNode2<ValType>> & head){
	unique_ptr<LLNode2<ValType>> new_head=nullptr;
	unique_ptr<LLNode2<ValType>> next=nullptr;
	while(head){
		next = std::move(head->_next);
		head->_next = std::move(new_head);
		new_head=std::move(head);
		head=std::move(next);
	}

	head = std::move(new_head);

};
template<typename A,typename B>
class Pair{
	public:
		Pair(const A& a,const B& b):_a(a),_b(b){};
		A _a;
		B _b;
};
template<typename KeyType,typename DataType>
class LLMap{
	public:
		LLMap(){
		}

		LLMap(LLMap&)=delete;
		LLMap(const LLMap&)=delete;
		LLMap(LLMap&&)=delete;
		LLMap(const LLMap&&)=delete;

		LLMap& operator=(LLMap&) = delete;
		LLMap& operator=(const LLMap&)=delete;
		LLMap& operator=(LLMap&&)=delete;
		LLMap& operator=(const LLMap&&)=delete;

		const size_t size()const{
			auto current_data=_data.get();
			if(current_data==nullptr){
				return 0;
			}else{
				size_t size_out = 1;
				while(0==0){
					if(current_data->_next!=nullptr){
						size_out++;
						current_data=current_data->_next.get();
					}else
						return size_out;
				}
			}
		}
		bool empty()const{
			return _data==nullptr;	
		};
		DataType* find(const KeyType &key_in){
			auto current_data = _data.get();
			while(0==0){
				if(current_data==nullptr){
					return nullptr;
				}
				if(current_data->_data._a==key_in){
					return &current_data->_data._b;
				}
				if(current_data->_next!=nullptr){
					current_data=current_data->_next.get();
				}else{
					return nullptr;
				}
			}

		}
		const DataType* find(const KeyType &key_in)const{
			auto current_data = _data.get();
			while(0==0){
				if(current_data==nullptr){
					return nullptr;
				}
				else if(current_data->_data._a==key_in){
					return &current_data->_data._b;
				}
			}
		}
		void insert(const KeyType &key,const DataType &data){
			DataType* found = find(key);
			if(found==nullptr){
				push_front(_data,Pair<KeyType,DataType>(key,data));
			}else{
				*found=data;
			}
		}
		void erase(const KeyType &key_in){
			auto current_data = _data.get();
			while(0==0){
				if(current_data->_data._a==key_in){
					_data = std::move(current_data->_next);	
					return;
				}else{
					if(current_data->_next!=nullptr){
						if(current_data->_next->_data._a==key_in)
							current_data->_next=std::move(current_data->_next->_next);
						else
							current_data=current_data->_next.get();
					}else{
						return;
					}
				}
			}
		}
		template <typename fn>
		void traverse(fn lambda){
			auto current_data = _data.get();
			while(0==0){
				if(current_data==nullptr){
					return;
				}
				lambda(current_data->_data._a,current_data->_data._b);
				if(current_data->_next!=nullptr){
					current_data=current_data->_next.get();
				}else{
					return;
				}
			}


		}

	private:
		unique_ptr<LLNode2<Pair<KeyType,DataType>>> _data;

};
#endif
