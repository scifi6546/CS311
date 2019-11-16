/*Nicholas Alexeev
 * 2019-10-06
 * purpose: source code of counthar
 */
#include "counthar.h"
#include <vector>
struct Vec2{int x=0;int y=0;};
int countRec(std::vector<Vec2> &been,
		Vec2 dim,Vec2 hole, Vec2 pos, Vec2 finish,unsigned char n_rec){
	//check current pos to see if in been
	//if true return 0
	
	for(int i=0;i<been.size();i++){
		Vec2 temp = been[i];
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
		//check if all spots are used
		//creating board
		if(been.size()==(dim.x*dim.y-2))
			return 1;
		return 0;
	}
	
	//add pos to been
	std::vector<Vec2> been_new = been;
	been_new.push_back(pos);
	//recursivly call countRec for 4 directions
	return 
		countRec(been_new,dim,hole,{pos.x-1,pos.y},
				finish,n_rec+1)+
		countRec(been_new,dim,hole,{pos.x+1,pos.y},
				finish,n_rec+1)+
		countRec(been_new,dim,hole,{pos.x,pos.y-1},
				finish,n_rec+1)+
		countRec(been_new,dim,hole,{pos.x,pos.y+1},
				finish,n_rec+1);
}
int countHAR(int dim_x,int dim_y,
		int hole_x,int hole_y,
		int start_x, int start_y,
		int finish_x,int finish_y){
	std::vector<Vec2> been={};
	return countRec(been,{dim_x,dim_y},{hole_x,hole_y},
			{start_x,start_y},{finish_x,finish_y},0);
}
