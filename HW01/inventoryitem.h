/*Nicholas Alexeev
 * 2019-09-05
*/
#ifndef INVENTORY
#define INVENTORY
//.hpp ending is also correct for c++
#include <string>
#include <cassert>
class InventoryItem{
	public:
		InventoryItem():_name("UNNAMED"),_number(0){};
		//Preconditions:
		//Number is>=0
		InventoryItem(const std::string & name, int number):_name(name),_number(number){};
		//copy ctor
		InventoryItem(const InventoryItem &item)=default;
		InventoryItem(InventoryItem &&item)=default;

		InventoryItem& operator=(const InventoryItem& rhs)=default;
		InventoryItem& operator=(InventoryItem&& rhs)=default;
		//figure out how to write move ctor
		//not by refrence because I do not trust users of this program
		//and name should be very short anyways so performance
		//should not be too much of a concern anyways
		std::string getName()const{
			return _name;	
		}
		//self explanatory
		int getNumber()const{
			return _number;	
		};
		//preconditions: none
		void setName(const std::string & name){
			_name=name;	
		};
		//preconditions number >=0	
		void setNumber(int number){
		
			assert(number>=0);
			_number=number;

		};
		//number is unsigned so it can never be less than zero
		bool empty()const{
			return _number==0;	
		}
		//returns string in form "{name} ({number})"
		std::string toString()const{
			std::string out="";
			out+=_name;
			out+=" (";
			out+=std::to_string(_number);
			out+=")";
			return out;
		};



		bool operator==(const InventoryItem &item)const{
			return item.getName()==getName()&&item.getNumber()==getNumber();	
		};

		bool operator!=(const InventoryItem &item)const{
			return !operator==(item);	
		};

		//preincrement
		//preconditions: _number is lower than max for uint64_t -1
		InventoryItem& operator++(){
				_number++;
				return *this;
		};
		//postincrement
		InventoryItem operator++(int){
			InventoryItem temp = *this;
			++*this;
			return temp;
		};

		//predecrement
		InventoryItem& operator--(){
			if(_number>0){
				_number--;
			}
			return *this;
		};
		//postdecrement
		InventoryItem operator--(int){
			InventoryItem temp = *this;
			--*this;
			return temp;
		};


	private:
		std::string _name;
		uint64_t _number;
};
std::ostream & operator<<(std::ostream &out,const InventoryItem & rhs){
	return out<<rhs.toString();
};
#endif
