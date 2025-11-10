// doublelist.h

#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert>    // assert()

template <typename T>
struct DoubleNode {
// the default access mode and default inheritance mode are public
    T value;
    DoubleNode *next, *prev;
    // konstruktor domyslny (niepotrzebny)
    DoubleNode() : value(T()), next(nullptr), prev(nullptr) {}
    DoubleNode(const T& item, DoubleNode *nptr=nullptr, DoubleNode *pptr=nullptr)
        : value(item), next(nptr), prev(pptr) {} // konstruktor
    ~DoubleNode() {} // destruktor
};


template <typename T>
class DoubleList {
    DoubleNode<T> *nil;
public:
    DoubleList(){
	    nil = new DoubleNode<T>();
	    nil->next = nil;
	    nil->prev = nil;
    }
    ~DoubleList(){ // tu trzeba wyczyscic wezly
		DoubleNode<T> *node = nil->next;
		while(node != nil){
			node = node->next;
			delete node->prev;
		}
		delete nil;
    }
    DoubleList(const DoubleList& other) : DoubleList() { // copy constructor
		DoubleNode<T> *node;
		for(DoubleNode<T> *current = other.nil->next ; current != other.nil ; current = current->next){
			node = new DoubleNode<T>(current->value , nil , nil->prev);
			nil->prev->next = node;
			nil->prev = node;
		}
    }
    // usage:   DoubleList<int> list2(list1);

    DoubleList(DoubleList&& other); // move constructor NIEOBOWIAZKOWE
    // usage:   DoubleList<int> list2(std::move(list1));

    DoubleList& operator=(const DoubleList& other){ // copy assignment operator, return *this
		if(this == &other){return *this;}
		this->clear();
		DoubleNode<T> *node;
		for(DoubleNode<T> *current = other.nil->next ; current != other.nil ; current = current->next){
			node = new DoubleNode<T>(current->value , nil , nil->prev);
			nil->prev->next = node;
			nil->prev = node;
		}
		return *this;
    }
    // usage:   list2 = list1;

    DoubleList& operator=(DoubleList&& other); // move assignment operator, return *this
    // usage:   list2 = std::move(list1); NIEOBOWIAZKOWE

    bool empty() const { return nil->next == nil; }
    std::size_t size() const{
		std::size_t size = 0;
		for(DoubleNode<T> *node = nil->next ; node != nil ; node = node->next){
			size++;
		}
		return size;
    } // O(n) bo trzeba policzyc
    void push_front(const T& item); // O(1)
    void push_front(T&& item); // O(1) NIEOBOWIAZKOWE
    void push_back(const T& item){
		DoubleNode<T> *node = new DoubleNode<T>(item , nil , nil->prev);
		nil->prev->next = node;
		nil->prev = node;
    } // O(1)
    void push_back(T&& item){
		DoubleNode<T> *node = new DoubleNode<T>(std::move(item) , nil , nil->prev);
		nil->prev->next = node;
		nil->prev = node;	
    } // O(1) NIEOBOWIAZKOWE
    T& front() const { return nil->next->value; } // zwraca poczatek, nie usuwa
    T& back() const { return nil->prev->value; } // zwraca koniec, nie usuwa
    void pop_front(); // usuwa poczatek O(1)
    void pop_back(){ // usuwa koniec O(1)
    	assert(!empty());
    	DoubleNode<T> *node = nil->prev;
    	node->next->prev = node->prev;
    	node->prev->next = node->next;
    	delete node;
    }
    void clear(){ // czyszczenie listy z elementow O(n)
		DoubleNode<T> *node = nil->next;
		while(node != nil){
			node = node->next;
			delete node->prev;
		}
		nil->next = nil;
		nil->prev = nil;
    }
    void display(){ // O(n)
    	DoubleNode<T> *node = nil->next;
    	while(node != nil){
    		std::cout << node->value;
    		node = node->next;
    	}
    	std::cout << std::endl;	
    }
    void display_reversed(){
    	DoubleNode<T> *node = nil->prev;
    	while(node != nil){
    		std::cout << node->value;
    		node = node->prev;
    	}
    	std::cout << std::endl;	
    } // O(n)

    // Operacje z indeksami. NIEOBOWIAZKOWE
    T& operator[](std::size_t pos); // podstawienie L[pos]=item, odczyt L[pos]
    const T& operator[](std::size_t pos) const; // dostep do obiektu const
    void erase(std::size_t pos);
    int index(const T& item); // jaki index na liscie (-1 gdy nie ma) O(n)
    void insert(std::size_t pos, const T& item); // inserts item before pos,
    void insert(std::size_t pos, T&& item); // inserts item before pos,
    // Jezeli pos=0, to wstawiamy na poczatek.
    // Jezeli pos=size(), to wstawiamy na koniec.
};

template <typename T>
void DoubleList<T>::push_front(const T& item){
	DoubleNode<T> *node = new DoubleNode<T>(item , nil->next , nil);
	node->next->prev = node;
	nil->next = node;
}

template <typename T>
void DoubleList<T>::push_front(T&& item){
	DoubleNode<T> *node = new DoubleNode<T>(std::move(item) , nil->next , nil);
	node->next->prev = node;
	nil->next = node;
}
template <typename T>
void DoubleList<T>::pop_front(){
    assert(!empty());
    DoubleNode<T> *node = nil->next; // zapamiętujemy
    node->next->prev = node->prev; // ogólny schemat usuwania
    node->prev->next = node->next;
    // Przywracanie usuniętego węzła [Knuth]:
    // node->next->prev = node;
    // node->prev->next = node;
    delete node;
}
#endif

// EOF
