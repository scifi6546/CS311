#include "counthar.h"
#include <vector>
struct Vec2{int x=0;int y=0;};
int countRec(std::vector<Vec2> *been,
		Vec2 dim,Vec2 hole, Vec2 pos, Vec2 finish){
	//check current pos to see if in been
	//if true return 0
	
	for(int i=0;i<been->size();i++){
		Vec2 temp = been->operator[](i);
		if(temp.x==pos.x && temp.y==pos.y)
			return 0;
	}
	
	//check current pos to see if inside of dim
	//if false return 0
	
	if(pos.x<0 || pos.y<0 || pos.x>=dim.x ||
			pos.y>=dim.y){
		return 0;
	}
	//check if at hole
	if(pos.x==hole.x&&pos.y==hole.y){
		return 0;
	}
	
	//check current pos to see if at finish
	//if true return 1
	
	if(pos.x==finish.x && pos.y==finish.y){
		return 1;
	}
	
	//add pos to been
	been->push_back(pos);
	//recursivly call countRec for 4 directions
	return 
		countRec(been,dim,hole,{pos.x-1,pos.y},finish)+
		countRec(been,dim,hole,{pos.x+1,pos.y},finish)+
		countRec(been,dim,hole,{pos.x,pos.y-1},finish)+
		countRec(been,dim,hole,{pos.x,pos.y+1},finish);
}
int countHAR(int dim_x,int dim_y,
		int hole_x,int hole_y,
		int start_x, int start_y,
		int finish_x,int finish_y){
	std::vector<Vec2> been={};
	return countRec(&been,{dim_x,dim_y},{hole_x,hole_y},
			{start_x,start_y},{finish_x,finish_y});
	//todo check if every tile is visited.
}
