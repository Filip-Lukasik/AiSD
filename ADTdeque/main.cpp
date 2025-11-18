#include <cassert>
#include "mydeque.h"

int main(){
	MyDeque<int> list = MyDeque<int>();
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
	MyDeque<int> list2(list);
	assert( !list2.empty() );
	assert( list2.front() == 4);
	assert( list2.back() == 1);
	assert( list2.size() == 2);
	list.push_back(2);
	assert( list.back() == 2);
	assert( list[1] == 1);
	assert( list.size() == 3);
	assert( list2.back() == 1);
	assert( list2.size() == 2);
	list2 = list;
	list2.display();
	list2.display_reversed();
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
	MyDeque<int> list3(list);
	assert( list3.empty() );
	assert( list3.size() == 0);
}
