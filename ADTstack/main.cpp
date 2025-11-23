#include <cassert>
#include <iostream>
#include "add.h"

int main(){
	std::string result = add("1","1");
	assert( result.compare("2") == 0);
	result = add( "123456789" , "987654321" );
	assert( result.compare("1111111110") == 0);
	result = add( "123456789123456789" , "1" );
	assert( result.compare("123456789123456790") == 0);
	result = add( "1" ,"123456789123456789" );
	assert( result.compare("123456789123456790") == 0);
}
