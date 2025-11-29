#include <cassert>
#include "myqueue.h"

int main(){
	MyQueue<int> list = MyQueue<int>();
	assert( list.empty() );
	assert( list.size() == 0);
	list.push(1);
	assert( !list.empty() );
	assert( list.front() == 1);
	assert( list.back() == 1);
	assert( list.size() == 1);
	list.push(4);
	assert( list.front() == 1);
	assert( list.back() == 4);
	assert( list.size() == 2);
	MyQueue<int> list2(list);
	assert( !list2.empty() );
	assert( list2.front() == 1);
	assert( list2.back() == 4);
	assert( list2.size() == 2);
	list.pop();
	assert( list.front() == 4);
	assert( list.size() == 1);
	list2 = std::move(list);
	assert( list.empty() );
	assert( list.size() == 0);
	assert( list.max_size() == 0);
	assert( list.full() );
	assert( list2.front() == 4);
	assert( list2.size() == 1);
	MyQueue<int> list3(std::move(list2));
	assert( list2.empty() );
	assert( list2.size() == 0 );
	assert( list2.max_size() == 0 );
	assert( list2.full() );
	assert( list3.front() == 4);
	assert( list3.size() == 1);
}
