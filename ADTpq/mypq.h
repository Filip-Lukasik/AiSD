#ifndef MYPQ_H
#define MYPQ_H

#include <vector>
#include <algorithm>   // make_heap, push_heap, pop_heap

template <typename T, typename Compare = std::less<T>>
class MyPriorityQueue {
    std::vector<T> lst; // działa domyślny konstruktor dla std::vector
    Compare cmp;
public:
    MyPriorityQueue(std::size_t s=10, const Compare& c = Compare()) : cmp(c) { lst.reserve(s); } // default constructor
    MyPriorityQueue(const Compare& c) : cmp(c) { lst.reserve(10); } // constructor with custom comparator
    ~MyPriorityQueue() { lst.clear(); }
    MyPriorityQueue(const MyPriorityQueue& other) : lst(other.lst), cmp(other.cmp) { } // copy constructor
    MyPriorityQueue(MyPriorityQueue&& other) : lst(std::move(other.lst)), cmp(std::move(other.cmp)) { } // move constructor
    MyPriorityQueue& operator=(const MyPriorityQueue& other) { // copy assignment operator, return *this
        if (this != &other) {
            lst = other.lst;
            cmp = other.cmp;
        }
        return *this;
    }
    MyPriorityQueue& operator=(MyPriorityQueue&& other) { // move assignment operator, return *this
        if (this != &other) {
            lst = std::move(other.lst);
            cmp = std::move(other.cmp);
        }
        return *this;
    }
    bool empty() const { return lst.empty(); }
    std::size_t size() const { return lst.size(); } // liczba elementów w kolejce
    void push(const T& item) { // dodanie do kolejki
        lst.push_back(item);
        std::push_heap(lst.begin(), lst.end(), cmp);
    }
    void push(T&& item) { // dodanie do kolejki
        lst.push_back(std::move(item));
        std::push_heap(lst.begin(), lst.end(), cmp);
    }
    T& top() { return lst.front(); } // zwraca element, nie usuwa go z kolejki
    void pop() { // usuwa element z kolejki
        std::pop_heap(lst.begin(), lst.end(), cmp);
        lst.pop_back();
    }
    void clear() { lst.clear(); } // czyszczenie listy z elementów
    void display(); // nie oczekujemy jakiegoś uporządkowania elementów
};
template <typename T, typename Compare>
void MyPriorityQueue<T, Compare>::display() {
    for (const auto& item : lst) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

#endif
