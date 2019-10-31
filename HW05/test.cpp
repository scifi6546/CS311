int main(){
	char* foo = new char[-1];
	delete[] foo;
}
