// arraylist.h

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert>    // assert()

template <typename T>
class ArrayList {
    T* tab;
    std::size_t msize; // najwieksza mozliwa liczba elementow
    std::size_t last; // pierwsza wolna pozycja
public:
    ArrayList(std::size_t s=10) : msize(s), last(0) {
        assert( s > 0 );
        tab = new T[s];
        assert( tab != nullptr );
    } // default constructor
    ~ArrayList() { delete [] tab; } // destruktor

    ArrayList(const ArrayList& other){ // copy constructor
    	msize = other.msize;
    	last = other.last;
    	tab = new T[msize];
        assert( tab != nullptr );
    	for(std::size_t i=0;i<msize;i++){
    		tab[i] = other.tab[i];
    	}
    }// usage:   ArrayList<int> list2(list1);

    ArrayList(ArrayList&& other){ // move constructor NIEOBOWIAZKOWE
    	msize = other.msize;
    	tab = other.tab;
        assert( tab != nullptr );
    	last = other.last;
    	other.tab = nullptr;
    	other.msize = 0;
    	other.last =0;
    }
    // usage:   ArrayList<int> list2(std::move(list1));

    ArrayList& operator=(const ArrayList& other){ // copy assignment operator, return *this
    	if(this==&other){
    		return *this;
    	}
    	delete [] tab;
    	msize=other.msize;
    	last = other.last;
    	tab = new T[msize];
        assert( tab != nullptr );
    	for(std::size_t i=0;i<msize;i++){
    		tab[i] = other.tab[i];
    	}
    	return *this;
    }// usage:   list2 = list1;

    ArrayList& operator=(ArrayList&& other){ // move assignment operator, return *this
    	if(this==&other){
    		return *this;
    	}
    	delete [] tab;
    	msize = other.msize;
    	tab = other.tab;
        assert( tab != nullptr );
    	last = other.last;
    	other.tab = nullptr;
    	other.msize = 0;
    	other.last =0;
    	return *this;
    }
    // usage:   list2 = std::move(list1); NIEOBOWIAZKOWE

    bool empty() const { return last == 0; } // checks if the container has no elements
    bool full() const { return last == msize; } // checks if the container is full
    std::size_t size() const { return last; } // liczba elementow na liscie
    std::size_t max_size() const { return msize; } // najwieksza mozliwa liczba elementow
    void push_front(const T& item){ // dodanie na poczatek
    	assert(!full());
	for(std::size_t i = last;i>0;i--){
		tab[i] = tab[i-1];
	}
	tab[0] = item;
	last++;
    }
    void push_front(T&& item){ // dodanie na poczatek NIEOBOWIAZKOWE
    	assert(!full());
	for(std::size_t i = last;i>0;i--){
		tab[i] = tab[i-1];
	}
	tab[0] = item;
	item = T();
	last++;
    }
    void push_back(const T& item){ // dodanie na koniec
    	assert(!full());	
   	tab[last] = item;
       	last++;	
    }
    void push_back(T&& item){ // dodanie na koniec NIEOBOWIAZKOWE
    	assert(!full());
    	tab[last] = item;
	item = T();
	last++;
    }
    T& front(){assert(!empty());return tab[0];} // zwraca poczatek, nie usuwa, error dla pustej listy
    T& back(){assert(!empty());return tab[last-1];} // zwraca koniec, nie usuwa, error dla pustej listy
    void pop_front(){ // usuwa poczatek, error dla pustej listy
    	assert(!empty());
	for(std::size_t i = 1;i<last;i++){
		tab[i-1] = tab[i];
	}
	last--;
	tab[last] = T();
    }
    void pop_back(){ // usuwa koniec, error dla pustej listy
    	assert(!empty());
	last--;
	tab[last] = T();
    }
    void clear(){ // czyszczenie listy z elementow
    	while(!empty()){
		last--;
		tab[last] = T();
	}
    }
    void display(){ // lepiej zdefiniowac operator<<
	for(std::size_t i=0;i<size();i++){
		std::cout << tab[i] << " ";
	}
	std::cout << std::endl;
    }
    void reverse(){ // odwracanie kolejnosci
    	for(std::size_t i =0;i<size()/2;i++){
		std::swap(tab[i],tab[last-1-i]);
	}
    }
    void sort(){ // sortowanie listy
	if (size()>1){
		std::size_t s= size()/2;
		ArrayList<T> secondpart(s);
		for(std::size_t i=0;i<s;i++){
			secondpart.push_back(back());
			pop_back();
		}
		sort();
		secondpart.sort();
		merge(secondpart);
	}
    }
    void merge(ArrayList& other){ //  merges two sorted lists into one NIEOBOWIAZKOWE
	ArrayList<T> merged(size()+other.size());
	std::size_t mpos=0,otherpos=0;
	while((mpos<size())&&(otherpos<other.size())){
		if(tab[mpos]>other[otherpos]){
			merged.push_back(other[otherpos]);
			otherpos++;
		}
		else{
			merged.push_back(tab[mpos]);
			mpos++;
		}
	}	
	if(mpos==size()){
		while(otherpos!=other.size()){
			merged.push_back(other[otherpos]);
			otherpos++;	
		}
	}
	else{
		while(mpos!=size()){
			merged.push_back(tab[mpos]);
			mpos++;
		}
	}
	*this = std::move(merged);
    }
    // Operacje z indeksami. NIEOBOWIAZKOWE
    // https://en.cppreference.com/w/cpp/language/operators
    // Array subscript operator
    T& operator[](std::size_t pos){ // podstawienie L[pos]=item, odczyt L[pos]
    	assert(pos<last);
	return tab[pos];
    }
    const T& operator[](std::size_t pos) const{ // dostep do obiektu const
    	assert(pos<last);
	return tab[pos];
    }
    void erase(std::size_t pos){ // usuniecie elementu na pozycji pos
    	assert(pos<last);
	last--;
	for(;pos<last;pos++){
		tab[pos] = tab[pos+1];
	}
	tab[pos] =T();

    }
    int index(const T& item){ // jaki index na liscie (-1 gdy nie ma)
	for(std::size_t pos=0;pos<last;pos++){
		if(tab[pos]==item){
			return pos;
		}
	}
	return -1;
    }
    void insert(std::size_t pos, const T& item){ // inserts item before pos
    	assert(!full());
	assert(pos<=last);
	for(std::size_t i=last;i>pos;i--){
		tab[i] = tab[i-1];
	}
	tab[pos] = item;
	last++;
    }
    void insert(std::size_t pos, T&& item){ // inserts item before pos
    	assert(!full());
	assert(pos<=last);
	for(std::size_t i=last;i>pos;i--){
		tab[i] = tab[i-1];
	}
	tab[pos] = item;
	last++;
	item = T();
    }
    // Jezeli pos=0, to wstawiamy na poczatek.
    // Jezeli pos=size(), to wstawiamy na koniec.

    friend std::ostream& operator<<(std::ostream& os, const ArrayList& L) {
        for (std::size_t i=0; i < L.last; ++i) { // odwolanie L.last
            os << L.tab[i] << " ";   // odwolanie L.tab
        }
        return os;
    } // usage:   std::cout << L << std::endl;
};

#endif

// EOF
