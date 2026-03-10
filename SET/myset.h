#ifndef MYSET_H
#define MYSET_H

#include <iostream>
#include <cassert>
#include <list>

// Szablon dla prostego zbioru wykorzystującego metodę łańcuchową.

template<typename T>
class MySet {
    int BUCKET;    // liczba bukietów
    std::list<T> *table;
public:
    MySet(int b);  // konstruktor
    ~MySet() { clear(); delete [] table; }
    bool empty() const; // czy zbiór jest pusty?
    int size() const; // liczba elementów zbioru
    void insert(T key); // wstawienie klucza do zbioru
    T* find(const T& key); // czy klucz jest w zbiorze? zwraca &key lub nullptr
    bool contains(const T& key); // czy klucz jest w zbiorze?
    void remove(const T& key);
    int hash(const T& key) { return (int(key) % BUCKET); } // działa dla int, float
    void clear(); // czyścimy zbiór
    void display() const; // wypisuje { item1, item2, ..., itemk }
};
template<typename T>
void MySet<T>::remove(const T& key) {
    int index = hash(key);
    table[index].remove(key);
}
template<typename T>
bool MySet<T>::contains(const T& key) {
    int index = hash(key);
    for (const T& k : table[index]) {
        if (k == key) {
            return true;
        }
    }
    return false;
}
template<typename T>
T* MySet<T>::find(const T& key) {
    int index = hash(key);
    for (T& k : table[index]) {
        if (k == key) {
            return &k;
        }
    }
    return nullptr;
}
template<typename T>
int MySet<T>::size() const {
    int count = 0;
    for (int i = 0; i < BUCKET; i++){
        count += table[i].size();
    }
    return count;
}
template<typename T>
void MySet<T>::insert(T key) {
    if (!contains(key)) {
        table[hash(key)].push_back(key);
    }
}
template<typename T>
void MySet<T>::clear() {
    for (int i = 0; i < BUCKET; i++){
        table[i].clear();
    }
}
template<typename T>
bool MySet<T>::empty() const {
    for (int i = 0; i < BUCKET; i++){        
        if (!table[i].empty()){
            return false;
        }
    }
    return true;
}
template<typename T>
MySet<T>::MySet(int b) {
    BUCKET = b;
    table = new std::list<T>[BUCKET]; // tablica z pustymi listami
    assert( table != nullptr );
}
template<typename T>
void MySet<T>::display() const {
    for (int i = 0; i < BUCKET; i++)
        for (const T& k : table[i])
            std::cout << k << " ";
    std::cout << std::endl;
}

#endif
