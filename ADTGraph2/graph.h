#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "basegraph.h"

// graph.hpp
class Graph : public BaseGraph<int> { // wersja 5b
    bool directed; // czy graf jest skierowany
    std::vector< std::vector<int> > adj_list; // lista sąsiedztwa
public:
    // Powstaje wektor z 'n' pustymi wektorami.
    Graph(int n, bool directed=false) : directed(directed) {
        adj_list = std::vector< std::vector<int> >(n);
    }
    ~Graph() { clear(); }
    bool is_directed() const override { return directed; } // czy graf jest skierowany O(1)
    int v() const override { return adj_list.size(); } // liczba wierzchołków grafu O(1)
    int e() const override { // liczba krawędzi grafu O(n)
        int counter = 0;
        for (auto& vec : adj_list)
            counter += vec.size();
        return (directed ? counter : counter / 2);
    }
    int degree(int u) const override { return adj_list[u].size(); }
    int indegree(int u) const override; // liczba krawędzi wchodzących do u
    int outdegree(int u) const override { return adj_list[u].size(); } // liczba krawędzi wychodzących z u
    void add_node(int u) override { assert((0 <= u) && (u < v())); } // tylko test zakresu
    void del_node(int u) override; // usuwanie krawedzi incydentnych
    bool has_node(int u) const override { return (0 <= u) && (u < v()); } // tylko test zakresu
    void add_edge(int u, int w, float weight=1.0) override; // wstawienie krawędzi (u,w)
    void add_edge(Edge<int> edge) override {
        add_edge(edge.source, edge.target, edge.weight);
    }
    void del_edge(int u, int w) override; // usunięcie krawędzi (u,w)
    void del_edge(Edge<int> edge) override {
        del_edge(edge.source, edge.target);
    }
    bool has_edge(int u, int w) const override; // test istnienia krawędzi (u,w)
    bool has_edge(Edge<int> edge) const override {
        return has_edge(edge.source, edge.target);
    }
    float weight(int u, int v) const override;
    float weight(Edge<int> edge) const override {
        return weight(edge.source, edge.target);
    }
    void clear() override { // usunięcie wszystkich krawędzi (wierzchołki zostają)
        // Zostawiamy adj_list z pustymi listami sąsiedztwa.
        for (auto& vec : adj_list)
            vec.clear();
    }
    void display() const override; // wypisywanie 'directed' i adj_list
};
int Graph::indegree(int u) const{
    int counter = 0;
    for (auto& vec : adj_list)
        for (int w : vec)
            if (w == u)
                counter++;
    return counter;
}
void Graph::del_node(int u) {
    adj_list[u].clear(); 
    for (auto& vec : adj_list) { 
        for(int i = 0; i < vec.size(); ++i) {
            if (vec[i] == u) {
                vec.erase(vec.begin() + i);
                break;
            }
        }
    }
}
void Graph::add_edge(int u, int w, float weight) {
    assert((0 <= u) && (u < v()) && (0 <= w) && (w < v()));
    adj_list[u].push_back(w);
    if (!directed)
        adj_list[w].push_back(u);
}
void Graph::del_edge(int u, int w) {
    assert((0 <= u) && (u < v()) && (0 <= w) && (w < v()));
    for(int i = 0; i < adj_list[u].size(); ++i) {
        if (adj_list[u][i] == w) {
            adj_list[u].erase(adj_list[u].begin() + i);
            break;
        }
    }
    if (!directed){
        for(int i = 0; i < adj_list[w].size(); ++i) {
            if (adj_list[w][i] == u) {
                adj_list[w].erase(adj_list[w].begin() + i);
                break;
            }
        }
    }
}
bool Graph::has_edge(int u, int w) const {
    assert((0 <= u) && (u < v()) && (0 <= w) && (w < v()));
    for (int neighbor : adj_list[u]) {
        if (neighbor == w)
            return true;
    }
    return false;
}
float Graph::weight(int u, int v) const {
    assert((0 <= u) && (u < this->v()) && (0 <= v) && (v < this->v()));
    for (int neighbor : adj_list[u])        
        if (neighbor == v)
            return 1.0; 
    return 0.0; 
}
void Graph::display() const {
    std::cout << (directed ? "Skierowany" : "Nieskierowany") << " Graf z " << v() << " wierzchołkami i " << e() << " krawędziami:\n";
    for (size_t i = 0; i < adj_list.size(); ++i) {
        std::cout << "wierzchołek " << i << ": ";
        for (int neighbor : adj_list[i]) {
            std::cout << neighbor << " ";
        }
        std::cout << "\n";
    }
}

#endif
