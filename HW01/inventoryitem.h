/*Nicholas Alexeev
 * 2019-09-05
*/
#ifndef INVENTORY
#define INVENTORY
//.hpp ending is also correct for c++
#include <string>
class InventoryItem{
	public:
		InventoryItem():_name("UNNAMED"),_number(0){};
		//Preconditions:
		//Number is>=0
		InventoryItem(const std::string & name, int number){};
		//copy ctor
		InventoryItem(const InventoryItem &item)=default;
		InventoryItem(InventoryItem &&item)=default;

		InventoryItem& operator=(const InventoryItem& rhs){};
		//figure out how to write move ctor
		//not by refrence because I do not trust users of this program
		//and name should be very short anyways so performance
		//should not be too much of a concern anyways
		std::string getName()const{}
		//self explanatory
		int getNumber()const{};
		//preconditions: none
		void setName(const std::string & name){};
		//preconditions number >=0	
		void setNumber(int number){};
		bool empty()const{}
		std::string toString()const{};



		bool operator==(const InventoryItem &item)const{};

		bool operator!=(const InventoryItem &item)const{};

		//preincrement
		InventoryItem& operator++(){};
		//postincrement
		InventoryItem operator++(int){};

		//predecrement
		InventoryItem& operator--(){};
		//postdecrement
		InventoryItem operator--(int){};



	private:
		std::string _name;
		uint64_t _number;
};
std::ostream & operator<<(std::ostream &out,const InventoryItem & rhs){};
#endif
