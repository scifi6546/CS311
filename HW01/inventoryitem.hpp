#ifndef
#define INVENTORY
//.hpp ending is also correct for c++

class InventoryItem{
	public:
		InventoryItem()_name:"UNNAMED",_number:0{};
		InventoryItem(std::string name, int number){};

		//figure out how to write move ctor
		//not by refrence because I do not trust users of this program
		//and name should be very short anyways so performance
		//should not be too much of a concern anyways
		const std::string getName(){}
		const int getNumber(){};
		void setName(const std::string & name){};
		
		void setNumber(int number){};
		const bool empty(){}
		const std::string toString(){};


	private:
		std::string _name;
		uint64_t _number;
}
#endif
