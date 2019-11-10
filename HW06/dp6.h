//Nicholas Alexeev
//purpose: define reverseList and LLMap
//10-10-2018
//licsened under gpl-v3
#ifndef DP6
#define DP6
#include <algorithm> 
#include "llnode2.h"
//precondition: head is a valid uniqe_ptr to LLNode2
//noexcept guarantee
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
//Basic Pair template
//writtem because std::pair has a wierd api
template<typename A,typename B>
struct Pair{
	public:
		Pair(const A& a,const B& b):_a(a),_b(b){};
		A _a;
		B _b;
};
//class invariants:_data has Pair, the key has operator== and the datatype has operator= 
template<typename KeyType,typename DataType>
class LLMap{
	public:
		//pre: none
		//post: none as this does nothing
		//noexcept guarantee
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

		//pre: none
		//post: returns size
		//noexcept guarantee
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
		//pre: none
		//post: returns true if empty
		//noexcept guarantee
		bool empty()const{
			return _data==nullptr;	
		};
		//pre: none
		//post: returns ptr to data
		//noexcept guarantee
		DataType* find(const KeyType &key_in){
			auto current_data = _data.get();
			while(0==0){
				if(current_data==nullptr){
					return nullptr;
				}
				else if(current_data->_data._a==key_in){
					return &current_data->_data._b;
				}else{
					current_data=current_data->_next.get();
				}
			}

		}
		//pre: none
		//post: returns ptr to data
		//noexcept guarantee
		const DataType* find(const KeyType &key_in)const{
			auto current_data = _data.get();
			while(0==0){
				if(current_data==nullptr){
					return nullptr;
				}
				else if(current_data->_data._a==key_in){
					return &current_data->_data._b;
				}else{
					current_data=current_data->_next.get();
				}

			}
		}
// Pre:
//     head points to empty-ptr-terminated Linked List, or is empty.
// Requirements on Types:
//     ValType must have a copy ctor and a (non-throwing) dctor.
// NOTE: The above are the requirements for LLNode2<ValType>; no member
// functions of ValType are actually used here.
// Strong guarantee
// Exception neutral
		void insert(const KeyType &key,const DataType &data){
			DataType* found = find(key);
			if(found==nullptr){
				push_front(_data,Pair<KeyType,DataType>(key,data));
			}else{
				*found=data;
			}
		}
		//noexcept guarantee
		//pre: key has operator==
		//post: data with key is no longer present
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
		//strong guarantee
		//exception neutral
		//pre: fn has operator()
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
