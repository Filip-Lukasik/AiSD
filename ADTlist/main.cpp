#include"arraylist.h"
#include<cassert>

int main(){
	ArrayList<int> ls1(10);
	assert(ls1.empty());
	assert(ls1.max_size()==10);
	ls1.push_back(1);
	assert(ls1.front()==1);
	assert(ls1.size()==1);
	ls1.push_front(3);
	assert(ls1.back()==1);
	assert(ls1.front()==3);
	assert(ls1.size()==2);
	assert(ls1[0]==3);
	ls1.pop_front();
	assert(ls1.front()==1);
	assert(ls1.size()==1);
	ls1.push_back(2);
	ls1.push_back(2);
	ls1.push_back(2);
	assert(ls1.size()==4);
	ls1.pop_back();
	assert(ls1.size()==3);
	ArrayList<int> ls2(ls1);
	assert(ls2.max_size()==10);
	assert(ls2.front()==1);
	assert(ls2[1]==2);
	assert(ls2.back()==2);
	ArrayList<int>ls3 = ls1;
	assert(ls3.max_size()==10);
	assert(ls3.front()==1);
	assert(ls3[1]==2);
	assert(ls3.back()==2);
	ls3.clear();
	assert(ls3.empty());
	ls3 = std::move(ls2);
	assert(ls3.max_size()==10);
	assert(ls3.front()==1);
	assert(ls3[1]==2);
	assert(ls3.back()==2);
	assert(ls2.empty());
	ArrayList<int> ls4(std::move(ls3));
	assert(ls3.empty());
	assert(ls4.max_size()==10);
	assert(ls4.front()==1);
	assert(ls4.back()==2);
	assert(ls4.size()==3);
	ls1.clear();
	ls4.reverse();
	assert(ls4.front()==2);
	assert(ls4.back()==1);
	ls4.insert(1,5);
	assert(ls4.size()==4);
	assert(ls4[1]==5);
	assert(ls4.index(5)==1);
	assert(ls4.index(0)==-1);
	for(int i=0;i<10;i++){
	ls1.push_front(i);
	}
	assert(ls1.full());
	ls1.display();
	ls1.sort();
	assert(ls1.front()==0);
	assert(ls1.back()==9);
	ls1.display();	
	return 0;
}
