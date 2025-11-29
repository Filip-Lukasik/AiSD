// myqueue.h

#ifndef MYQUEUE_H
#define	MYQUEUE_H

#include <iostream>
#include <cassert>

template <typename T>
class MyQueue {
    T* tab;
    std::size_t msize; // największa możliwa liczba elementów plus jeden
    std::size_t head; // pierwszy do pobrania
    std::size_t tail; // pierwsza wolna pozycja
public:
    MyQueue(std::size_t s=10) : msize(s+1), head(0), tail(0) {
    	tab = new T[s+1];
    	assert( tab != nullptr );
    } // default constructor
    ~MyQueue() { delete [] tab; }
    MyQueue(const MyQueue& other){ // copy constructor
    	msize = other.msize;
	head = other.head;
	tail = other.tail;
	tab = new T[msize];
    	assert ( tab != nullptr);
    	for(std::size_t el = head ; el != tail ; el = (el + 1) % msize){
    		tab[el] = other.tab[el];
    	}
    }
    MyQueue(MyQueue&& other){ // move constructor
    	msize = other.msize;
	head = other.head;
	tail = other.tail;
	tab = other.tab;
	other.tail = other.head = 0;
	other.msize = 1;
	other.tab = nullptr;
    }
    // UWAGA Po przeniesieniu other.msize = 1, other.head = other.tail = 0.
    MyQueue& operator=(const MyQueue& other){ // copy assignment operator, return *this
    	if(this == &other){ return *this; }
    	delete [] tab;
    	msize = other.msize;
    	head = other.head;
    	tail = other.tail;
    	tab = new T[msize];
    	assert ( tab != nullptr);
    	for(std::size_t el = head ; el != tail ; el = (el + 1) % msize){
    		tab[el] = other.tab[el];
    	}
    	return *this;
    }
    MyQueue& operator=(MyQueue&& other){ // move assignment operator, return *this
    	if(this == &other){ return *this; }
    	delete [] tab;
	msize = other.msize;
    	head = other.head;
	tail = other.tail;
	tab = other.tab;
	other.tail = other.head = 0;
	other.msize = 1;
	other.tab = nullptr;
    	return *this;
    }
    // UWAGA Po przeniesieniu other.msize = 1, other.head = other.tail = 0.
    bool empty() const { return head == tail; }
    bool full() const { return (tail + 1) % msize == head; }
    std::size_t size() const { return (tail - head + msize) % msize; }
    std::size_t max_size() const { return msize-1; }
    void push(const T& item){ // dodanie na koniec
    	assert(!full());
    	tab[tail] = item;
    	tail = (tail + 1) % msize;
    }
    void push(T&& item){ // dodanie na koniec
    	assert( !full() );
    	tab[tail] = std::move(item);
    	tail = (tail + 1) % msize; 
    }
    T& front() { return tab[head]; } // zwraca poczatek
    T& back() { return tab[(tail + msize - 1) % msize]; } // zwraca koniec
    void pop(){ // usuwa początek
    	assert( !empty() );
    	tab[head] = T();
    	head = (head + 1) % msize;
    }
    void clear(){ // czyszczenie listy z elementów
    	for(std::size_t el = head ; el != tail ; el = (el + 1) % msize){
    		tab[el] = T();
    	}
    	head = tail = 0;
    }
    void display(){
    	for (std::size_t i = head; i != tail; i = (i+1) % msize) {
        	std::cout << tab[i] << " ";
    	}
    	std::cout << std::endl;
    	}
};
#endif
