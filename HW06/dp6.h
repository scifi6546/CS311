#ifndef DP6
#define DP6
#include "llnode2.h"

template<typename ValType>
void reverseList(unique_ptr<LLNode2<ValType>> & head){
	unique_ptr<ValType> prev = nullptr;

	unique_ptr<ValType> current = nullptr;
	unique_ptr<ValType> next = nullptr;
	while(0==0){
		if(prev!=nullptr){
			if(next->_next==nullptr){
				next->next=prev;
				return;

			}
			next=current->_next;
			current->_next=prev;	
			prev=current;

		}else{
			current=make_unique<head>;
			next=current->_next;
		}
		
	}
}
template<typename TA>
template<typename TB>
class BetterThanStdPair{
//otherwise known as I feel lucky today
	public:
	BetterThanStdPair(TA &A,TB &B):_a(A),_b(B){

	};
	private:
	TA _a;
	TB _b;
};
template<typename key>
template<typename data>
class LLMap{
	public:
		LLMap(){};
		~LLMAP();

		LLMap(LLMap &in)=delete;
		LLMap(const LLMap &in)=delete;

		LLMap(LLMap &&in)=delete;
		LLMap(const LLMap &&in)=delete;

		LLMap &operator=(LLMap &in)=delete;
		LLMap &operator=(const LLMap &in)=delete;

		LLMap& operator=(LLMap&& in)=delete;
		LLMap& operator=(const LLMap&& in)=delete;

		size_t size(){return 0;};
		

	private:
		unique_ptr<LLNode2<BetterThanStdPair<data,key>> _data;
};
#endif

