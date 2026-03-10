#include <cassert>
#include <iostream>
#include "myset.h"

int main(){
	MySet<int> set(10);
	set.insert(5);
	set.insert(10);
	set.insert(15);
	set.display();
	assert(set.contains(5));
	assert(set.contains(10));
	assert(set.contains(15));
	assert(!set.contains(20));
	assert(set.find(10) != nullptr);
	assert(*set.find(10) == 10);
	assert(set.find(20) == nullptr);
	assert(set.size() == 3);
	set.insert(5); // duplikat, nie powinien być dodany
	assert(set.size() == 3);
	set.remove(10);
	assert(!set.contains(10));
	assert(set.size() == 2);
	set.clear();
	assert(set.empty());
	assert(set.size() == 0);
}

