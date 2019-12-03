//Nicholas Alexeev
//16:59 Dec 3 2019
//Purpose: gets statists from file
//GPLv3.0
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

//pre: none
//post: statiscs are printed to screen
int main(){
	std::string fname;
	std::cout<<"choose file:\n";
	std::getline(std::cin,fname);
	std::ifstream ifs(fname, std::ifstream::in);
	std::map<std::string,std::vector<std::string>> dict;

	if(ifs.good()){
		
		std::string previous="";
		std::string current="";
		std::cout<<"opened "<<fname<<"\n";
		while(0==0){
			current="";
			ifs>>current;
			if(ifs.eof()){
				dict[current]=std::vector<std::string>();
				break;
			}
			if(previous!=""){
				bool in_vec=false;
				for(auto item:dict[previous]){
					if(current==item)
						in_vec=true;
				}
				if(!in_vec)
					dict[previous].push_back(current);
			}
			previous=current;
		}

	}else{
		std::cout<<"error invalid file\n";
		return 1;
	}
	for(auto i:dict){
		std::cout<<i.first<<": ";
		std::sort(i.second.begin(),i.second.end());
		for(auto j:i.second){
			std::cout<<j<<" ";
		}
		std::cout<<"\n";

	}
	return 0;
}
