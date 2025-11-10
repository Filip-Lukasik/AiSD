#include <cassert>
#include "doublelist.h"

int main(){
	DoubleList<int> list = DoubleList<int>();
	assert( list.empty() );
	assert( list.size() == 0);
	list.push_front(1);
	assert( !list.empty() );
	assert( list.front() == 1);
	assert( list.back() == 1);
	assert( list.size() == 1);
	list.push_front(4);
	assert( list.front() == 4);
	assert( list.back() == 1);
	assert( list.size() == 2);
	DoubleList<int> list2(list);
	assert( !list2.empty() );
	assert( list2.front() == 4);
	assert( list2.back() == 1);
	assert( list2.size() == 2);
	list.push_back(2);
	assert( list.back() == 2);
	assert( list.size() == 3);
	assert( list2.back() == 1);
	assert( list2.size() == 2);
	list2 = list;
	assert( list2.back() == 2);
	assert( list2.size() == 3);
	list.pop_front();
	assert( list.front() == 1);
	assert( list.size() == 2);
	list.pop_back();
	assert( list.back() == 1);
	assert( list.size() == 1);
	list2.clear();
	assert( list2.empty() );
	assert( list2.size() == 0);
	list = list2;
	assert( list.empty() );
	assert( list.size() == 0);
	DoubleList<int> list3(list);
	assert( list3.empty() );
	assert( list3.size() == 0);
}
