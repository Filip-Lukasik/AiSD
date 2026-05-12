#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "iterator.h"
#include "edge.h"
#include "basegraph.h"
#include <unordered_map>

// graph.hpp
template <typename T>
class Graph : public BaseGraph<T> { // wersja5c
    bool directed;
    //std::unordered_map<T, std::list<Edge<T> *> > adj_list; // lista sąsiedztwa
    std::unordered_map<T, std::vector<Edge<T> *> > adj_list; // lista sąsiedztwa
    // Korzystanie z iteratorów w grafie.
    // w grafie używamy std::map lub std::unordered_map
public:
    class NodeIterator : public Iterator<T> { 
        Graph* graph;
        typename std::unordered_map<T, std::vector<Edge<T> *> >::iterator map_it;
    public:
        NodeIterator(Graph* graph, typename std::unordered_map<T, std::vector<Edge<T> *> >::iterator map_it) : graph(graph), map_it(map_it) {}
        T operator*() const { return map_it->first; }
        NodeIterator& operator++() { ++map_it; return *this; }
        bool operator!=(const NodeIterator& other) const { return map_it != other.map_it; }
    };
    NodeIterator node_begin() {
        return NodeIterator(this, this->adj_list.begin());
    }
    NodeIterator node_end() {
        return NodeIterator(this, this->adj_list.end());
    }
    class EdgeIterator : public Iterator<Edge<T>> {
        Graph* graph;
        typename std::unordered_map<T, std::vector<Edge<T> *> >::iterator map_it;
        typename std::vector<Edge<T> *>::iterator edge_it;
    public:
        EdgeIterator(Graph* graph, typename std::unordered_map<T, std::vector<Edge<T> *> >::iterator map_it, typename std::vector<Edge<T> *>::iterator edge_it) : graph(graph), map_it(map_it), edge_it(edge_it) {}
        EdgeIterator(Graph* graph) : graph(graph), map_it(graph->adj_list.begin()) {
            if (map_it != graph->adj_list.end()) {
                edge_it = map_it->second.begin();
                while (map_it != graph->adj_list.end() && edge_it == map_it->second.end()) {
                    ++map_it;
                    if (map_it != graph->adj_list.end()) {
                        edge_it = map_it->second.begin();
                    }
                }
            }
        }
        Edge<T> operator*() const { return *(edge_it); }
        EdgeIterator& operator++() {
            if (graph->directed) {
                ++edge_it;
                while (map_it != graph->adj_list.end() && edge_it == map_it->second.end()) {
                    ++map_it;
                    if (map_it != graph->adj_list.end()) {
                        edge_it = map_it->second.begin();
                    }
                }
                return *this;
            } else {
                ++edge_it;
                while(edge_it != map_it->second.end() && (*edge_it)->target < map_it->first) { // pomijamy krawędzie już odwiedzone
                    ++edge_it;
                }
                while (map_it != graph->adj_list.end() && edge_it == map_it->second.end()) {
                    ++map_it;
                    if (map_it != graph->adj_list.end()) {
                        edge_it = map_it->second.begin();
                    }
                }
                return *this;
            }
        }
        bool operator!=(const EdgeIterator& other) const {return map_it != other.map_it || (map_it != graph->adj_list.end() && edge_it != map_it->second.end()); }
    };
    EdgeIterator edge_begin() {
        return EdgeIterator(this);
    }
    EdgeIterator edge_end() {
        return EdgeIterator(this, this->adj_list.end(),
            this->adj_list.begin()->second.end()); // konwencja
    }
    class AdjacentIterator : public Iterator<T> {
        Graph* graph;
        typename std::unordered_map<T, std::vector<Edge<T> *> >::iterator map_it;
        typename std::vector<Edge<T> *>::iterator edge_it;
    public:    
        AdjacentIterator(Graph* graph, typename std::unordered_map<T, std::vector<Edge<T> *> >::iterator map_it, typename std::vector<Edge<T> *>::iterator edge_it) : graph(graph), map_it(map_it), edge_it(edge_it) {}
        T operator*() const { return (*edge_it)->target; }
        AdjacentIterator& operator++() {
            ++edge_it;
            return *this;
        }
        bool operator!=(const AdjacentIterator& other) const { return edge_it != other.edge_it; }
    }; 
    AdjacentIterator adj_begin(T u) {
        auto pair_it = this->adj_list.find(u);
        return AdjacentIterator(this, pair_it, pair_it->second.begin());
    }
    AdjacentIterator adj_end(T u) {
        auto pair_it = this->adj_list.find(u);
        return AdjacentIterator(this, pair_it, pair_it->second.end());
    }
    Graph(bool directed=false) : directed(directed) {}
    ~Graph() { clear(); } // trzeba zwolnić pamięć krawędzi
    bool is_directed() const override { return directed; }
    int v() const override { return adj_list.size(); } // liczba wierzchołków
    int e() const override { // liczba krawędzi
        int counter = 0;
        for (auto& pair : adj_list)
            counter += pair.second.size();
        return (directed ? counter : counter / 2);
    }
    int degree(T u) override {
        assert( !directed );
        return adj_list[u].size();
    }
    int indegree(T u) const override { // liczba krawędzi wchodzących do u
        int counter = 0;
        for (auto& pair : adj_list) {
            for (auto& edge : pair.second) {
                if (edge->target == u) {
                    counter++;
                }
            }
        }
        return counter;
    }
    int outdegree(T u) override { return adj_list[u].size(); } // liczba krawędzi wychodzących z u
    void add_node(T u) override { adj_list[u]; } // dodaj izolowany wierzchołek
    void del_node(T u) override {
        // usunięcie wierzchołka u i wszystkich krawędzi z nim związanych
        auto it = adj_list.find(u);
        if (it != adj_list.end()) {
            // zwolnienie pamięci krawędzi wychodzących z u
            for (auto& edge : it->second) {
                delete edge;
            }
            adj_list.erase(it);
        }
        // usunięcie krawędzi wchodzących do u
        for (auto& pair : adj_list) {
            auto& edges = pair.second;
            for (auto it = edges.begin(); it != edges.end();) {
                if ((*it)->target == u) {
                    delete *it; // zwolnienie pamięci krawędzi
                    it = edges.erase(it); // usunięcie krawędzi z listy sąsiedztwa
                } else {
                    ++it;
                }
            }
        }
    }
    bool has_node(T u) const override { return adj_list.find(u) != adj_list.end(); } // test istnienia wierzchołka
    void add_edge(T u, T w, float weight=1.0) override {
        // wstawienie krawędzi (u,w) z wagą
        if (!has_node(u)) {
            add_node(u);
        }
        if (!has_node(w)) {
            add_node(w);
        }
        Edge<T>* edge = new Edge<T>(u, w, weight);
        adj_list[u].push_back(edge);
        if (!directed) {
            Edge<T>* reverse_edge = new Edge<T>(w, u, weight);
            adj_list[w].push_back(reverse_edge);
        }
    } // wstawienie krawędzi (u,w) z wagą
    void add_edge(Edge<T> edge) override {
        add_edge(edge.source, edge.target, edge.weight);
    }
    void del_edge(T u, T w) override{
        // usunięcie krawędzi (u,w)
        auto it = adj_list.find(u);
        if (it != adj_list.end()) {
            auto& edges = it->second;
            for (auto edge_it = edges.begin(); edge_it != edges.end(); ++edge_it) {
                if ((*edge_it)->target == w) {
                    delete *edge_it; // zwolnienie pamięci krawędzi
                    edges.erase(edge_it); // usunięcie krawędzi z listy sąsiedztwa
                    break;
                }
            }
        }
        if (!directed) {
            auto it = adj_list.find(w);
            if (it != adj_list.end()) {
                auto& edges = it->second;
                for (auto edge_it = edges.begin(); edge_it != edges.end(); ++edge_it) {
                    if ((*edge_it)->target == u) {
                        delete *edge_it; // zwolnienie pamięci krawędzi
                        edges.erase(edge_it); // usunięcie krawędzi z listy sąsiedztwa
                        break;
                    }
                }
            }
        }
    } // usunięcie krawędzi (u,w)
    void del_edge(Edge<T> edge) override {
        del_edge(edge.source, edge.target);
    }
    bool has_edge(T u, T w) const override { // test istnienia krawędzi
        auto it = adj_list.find(u);
        if (it != adj_list.end()) {
            for (const auto& edge : it->second) {
                if (edge->target == w) {
                    return true;
                }
            }
        }
        return false;
    } // test istnienia krawędzi
    bool has_edge(Edge<T> edge) const override {
        return has_edge(edge.source, edge.target);
    }
    float weight(T u, T w) const override {
        auto it = adj_list.find(u);
        if (it != adj_list.end()) {
            for (const auto& edge : it->second) {
                if (edge->target == w) {
                    return edge->weight;
                }
            }
        }
        return 0.0; // brak krawędzi
    } // waga krawędzi lub 0.0
    float weight(Edge<T> edge) const override {
        return weight(edge.source, edge.target);
    }
    void clear() override { // trzeba zwolnić pamięć krawędzi
        for (auto& pair : adj_list) {
            for (auto& edge : pair.second) {
                delete edge;
            }
        }
        adj_list.clear();
    }
    void display() const override {
        for (const auto& pair : adj_list) {
            std::cout << pair.first << ": ";
            for (const auto& edge : pair.second) {
                std::cout << "(" << edge->target << ", weight: " << edge->weight << ") ";
            }
            std::cout << std::endl;
        }
    }
};


    

#endif
