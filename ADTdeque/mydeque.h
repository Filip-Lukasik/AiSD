// mydeque.h

#ifndef MYDEQUE_H
#define	MYDEQUE_H

#include <iostream>
#include <cassert>

template <typename T>
class MyDeque {
    T* tab;
    std::size_t msize; // największa możliwa liczba elementów plus jeden
    std::size_t head; // pierwszy do pobrania
    std::size_t tail; // pierwsza wolna pozycja
public:
    MyDeque(std::size_t s=10) : msize(s+1), head(0), tail(0) {
    	tab = new T[s+1];
    	assert( tab != nullptr );
    } // default constructor
    ~MyDeque() { delete [] tab; }
    MyDeque(const MyDeque& other){ // copy constructor
    	msize = other.msize;
	head = other.head;
	tail = other.tail;
	tab = new T[msize];
    	assert ( tab != nullptr);
    	for(std::size_t el = head ; el != tail ; el = (el + 1) % msize){
    		tab[el] = other.tab[el];
    	}
    }
    MyDeque(MyDeque&& other); // move constructor NIEOBOWIĄZKOWE
    // UWAGA Po przeniesieniu other.msize = 1, other.head = other.tail = 0.
    MyDeque& operator=(const MyDeque& other){ // copy assignment operator, return *this
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
    MyDeque& operator=(MyDeque&& other); // move assignment operator, return *this NIEOBOWIĄZKOWE
    // UWAGA Po przeniesieniu other.msize = 1, other.head = other.tail = 0.
    bool empty() const { return head == tail; }
    bool full() const { return (tail + 1) % msize == head; }
    std::size_t size() const { return (tail - head + msize) % msize; }
    std::size_t max_size() const { return msize-1; }
    void push_front(const T& item); // dodanie na początek O(1)
    void push_front(T&& item){ // dodanie na początek O(1) NIEOBOWIĄZKOWE
    	assert( !full() );
    	head = (head + msize - 1) % msize;
    	tab[head] = std::move(item);
    }
    void push_back(const T& item); // dodanie na koniec O(1)
    void push_back(T&& item){ // dodanie na koniec O(1) NIEOBOWIĄZKOWE
    	assert( !full() );
    	tab[tail] = std::move(item);
    	tail = (tail + 1) % msize; 
    }
    T& front() { return tab[head]; } // zwraca poczatek
    T& back() { return tab[(tail + msize - 1) % msize]; } // zwraca koniec
    void pop_front(){ // usuwa początek kolejki O(1)
    	assert( !empty() );
    	tab[head] = T();
    	head = (head + 1) % msize;
    }
    void pop_back(){ // usuwa koniec kolejki O(1)
    	assert( !empty() );
    	tail = (tail - 1 + msize) % msize;
    	tab[tail] = T();
    }
    void clear(){ // czyszczenie listy z elementów
    	for(std::size_t el = head ; el != tail ; el = (el + 1) % msize){
    		tab[el] = T();
    	}
    	head = tail = 0;
    }
    void display();
    void display_reversed(){
    	for(std::size_t el = (tail - 1 + msize) % msize ; el != (head - 1 + msize) % msize ; el = (el - 1 + msize) % msize){
    		std::cout << tab[el] << " ";
    	}
    	std::cout << std::endl;
    }
    // Operacje z indeksami. NIEOBOWIĄZKOWE
    T& operator[](std::size_t pos){ // podstawienie L[pos]=item, odczyt L[pos]
    	assert( pos < size() );
    	return tab[(head + pos) % msize];
    }
    const T& operator[](std::size_t pos) const; // dostęp do obiektu const
    void erase(std::size_t pos);
    int index(const T& item); // jaki index na liście (-1 gdy nie ma)
    void insert(std::size_t pos, const T& item); // inserts item before pos
    void insert(std::size_t pos, T&& item); // inserts item before pos
};
template <typename T>
void MyDeque<T>::push_front(const T& item) {
    assert(!full());
    head = (head + msize -1) % msize;
    tab[head] = item;
}
template <typename T>
void MyDeque<T>::push_back(const T& item) {
    assert(!full());
    tab[tail] = item;
    tail = (tail + 1) % msize;
}
template <typename T>
void MyDeque<T>::display() {
    for (std::size_t i = head; i != tail; i = (i+1) % msize) {
        std::cout << tab[i] << " ";
    }
    std::cout << std::endl;
}
#endif
