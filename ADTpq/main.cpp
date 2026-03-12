#include <cassert>
#include <iostream>
#include "mypq.h"

int main(){
    MyPriorityQueue<int> pq;
	assert(pq.empty());
    pq.push(5);
    pq.push(10);
    pq.push(15);
	assert(pq.size() == 3);
    pq.display();
	assert(pq.top() == 15);
	pq.pop();
	assert(pq.size() == 2);
	assert(pq.top() == 10);
	MyPriorityQueue<int> pq2 = pq;
	assert(pq2.size() == 2);
	assert(pq2.top() == 10);
	MyPriorityQueue<int> pq3 = std::move(pq);
	assert(pq3.size() == 2);
	assert(pq3.top() == 10);
	MyPriorityQueue<int> pq4;
	pq4 = pq2;
	assert(pq4.size() == 2);
	assert(pq4.top() == 10);
	MyPriorityQueue<int> pq5;
	pq5 = std::move(pq2);
	assert(pq5.size() == 2);
	assert(pq5.top() == 10);
	pq.clear();
	assert(pq.empty());
	auto cmp = [](std::pair<int, std::string> a, std::pair<int, std::string> b) {
		return a.first > b.first;
	};
	MyPriorityQueue<std::pair<int, std::string>, decltype(cmp)> pq6(cmp);
	pq6.push({3, "trzy"});
	pq6.push({1, "raz"});
	pq6.push({2, "dwa"});
	while (!pq6.empty())
	{
		auto top = pq6.top();
		std::cout << top.first << ": " << top.second << std::endl;
		pq6.pop();
	}
	
}

