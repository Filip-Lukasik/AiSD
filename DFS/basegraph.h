#ifndef BASEGRAPH_H
#define BASEGRAPH_H

#include "edge.h"

// basegraph.hpp
template <typename T>
class BaseGraph { // abstract class
public:
    BaseGraph() {}
    ~BaseGraph() {}
    virtual bool is_directed() const = 0;
    virtual int v() const = 0; // liczba wierzcholkow
    virtual int e() const = 0; // liczba krawedzi
    virtual int degree(T u) const = 0; // problem z const dla operator[]
    virtual int indegree(T u) const = 0; // stopień wejściowy
    virtual int outdegree(T u) const = 0; // stopień wyjściowy
    virtual void add_node(T u) = 0;
    virtual void del_node(T u) = 0;
    virtual bool has_node(T u) const = 0;
    virtual void add_edge(T u, T w, float weight=1.0) = 0;
    virtual void add_edge(Edge<T> edge) = 0;
    virtual void del_edge(T u, T w) = 0;
    virtual void del_edge(Edge<T> edge) = 0;
    virtual bool has_edge(T u, T w) const = 0;
    virtual bool has_edge(Edge<T> edge) const = 0;
    virtual float weight(T u, T w) const = 0;
    virtual float weight(Edge<T> edge) const = 0;
    virtual void clear() = 0;
    virtual void display() const = 0;
};

#endif
