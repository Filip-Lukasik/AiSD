#ifndef EDGE_H
#define EDGE_H

#include <iostream>

// edge.hpp
template<typename T>
class Edge {
public:
    T source;
    T target;
    float weight;
    Edge(T s, T t, float w=1.0) : source(s), target(t), weight(w) {}
    ~Edge() {}                // destruktor
    Edge(const Edge& edge) : source(edge.source), target(edge.target),
        weight(edge.weight) {}  // copy-constructor
    // Operator negacji bitowej, ale tu pasuje.
    Edge operator~() const { return Edge(target, source, weight); }
    Edge& operator=(const Edge& other) { // return *this;
        if (this != &other) {
            source = other.source;
            target = other.target;
            weight = other.weight;
        }
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& os, const Edge& edge) {
        os << "(" << edge.source << "->" << edge.target
           << ", w=" << edge.weight << ")";
        return os;
    }
    bool operator==(const Edge& edge) const {
        return source == edge.source && target == edge.target
            && weight == edge.weight;
    }
    bool operator!=(const Edge& edge) const {
        return !(*this == edge);
    }
};

#endif
