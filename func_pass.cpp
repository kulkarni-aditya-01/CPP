#include <iostream>
using namespace std ;
void print(){
	cout << "This is the print function :) " << endl ;
}
void display(){
	cout << "This is a display function :) " << endl ;
}
void branch(){
	cout << "this is the branch function :) " << endl ;
}
void set(){
	cout << "this is the set function :) " << endl ;
}

int main(){
	print(); 
	display();
	branch() ;
	set() ;

	return 0 ;
}
//use a -opt -passes='inst-count' -disable-output filename.ll
//
