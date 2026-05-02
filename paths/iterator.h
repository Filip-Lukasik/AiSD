// iterator.hpp

template <typename T>
class Iterator { // abstract class
public:
    Iterator() = default;
    ~Iterator() = default;
    // Sa problemy w dziedziczeniu tych funkcji.
    //virtual Iterator& operator=(const Iterator& other) = 0; // tego się nie robi
    //virtual Iterator& operator++() = 0;
    //virtual Iterator operator++(int) = 0;
    //virtual bool operator==(const Iterator& other) = 0;
    //virtual bool operator!=(const Iterator& other) = 0;
    virtual T operator*() const = 0; // działa
};