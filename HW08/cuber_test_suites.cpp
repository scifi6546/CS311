//Nicholas Alexeev
//16:59 Dec 3 2019
//Purpose: tests cuber class
//GPLv3.0
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "cuber.h"

class Copy {
	public:
		Copy(){
			_d=2;
		}
		~Copy()=default;
		Copy operator*(const Copy& in){
			Copy a;
			a._d=_d*in._d;
		}
		Copy(const Copy&)=default;
		Copy(Copy&&)=delete;
		Copy operator=(const Copy&)=delete;
		Copy operator=(Copy&&)=delete;
		int get(){return _d;};
	private:
		int _d;
};
TEST_CASE("Testing required constructors"){
	Cuber cc;
	Copy c;
	//REQUIRE(cc(c).get()==8);
	INFO("Testing with object including only copy ctor and operator*");
}
TEST_CASE("Testing Aritmatic"){
	Cuber cc;
	REQUIRE(cc(5)==5*5*5);
	INFO("Failed with Input 5");
	REQUIRE(cc(8)==512);
	INFO("testing with input of 8");
	char small = 2;
	REQUIRE(cc(small)==8);
	INFO("Testing with char");
	char n=-1;
	REQUIRE(cc(n)==-1);
	INFO("Testing with -1");
	float ten=10.0f;
	REQUIRE(cc(n)-1000.0f<1.0f);
	INFO("Testing with 1.0f");
}
TEST_CASE("testing const"){
	const Copy c;
	const Cuber cc;
	//REQUIRE(cc(c).get()==8);
	INFO("Testing with object including only copy ctor and operator*");
	REQUIRE(cc(5)==5*5*5);
	INFO("Failed with Input 5");
	REQUIRE(cc(8)==512);
	INFO("testing with input of 8");
	const char small = 2;
	REQUIRE(cc(small)==8);
	INFO("Testing with char");
	const char n=-1;
	REQUIRE(cc(n)==-1);
	INFO("Testing with -1");
	const float ten=10.0f;
	REQUIRE(cc(n)-1000.0f<1.0f);
	INFO("Testing with 1.0f");

}
