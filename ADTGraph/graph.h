#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "basegraph.h"
#include "iterator.h"

// graph.hpp
class Graph : public BaseGraph<int> { // wersja 7x
    bool directed;
    // Adjacency matrix to store graph edges.
    std::vector<std::vector<Edge<int> *> > adj_matrix;
public:
    class NodeIterator : public Iterator<int> { 
        Graph* graph;
        int index;
    public:        NodeIterator(Graph* g, int idx) : graph(g), index(idx) {
            while (index < graph->adj_matrix.size() && !graph->has_node(index)) {
                index++;
            }
    }
        int operator*() const override { return index; }
        NodeIterator& operator++() { // pre-inkrementacja
            do {
                index++;
            } while (index < graph->adj_matrix.size() && !graph->has_node(index));
            return *this;
        }
        NodeIterator operator++(int) { // post-inkrementacja
            NodeIterator temp = *this;
            ++(*this);
            return temp;
        }
        bool operator==(const NodeIterator& other) const {
            return graph == other.graph && index == other.index;
        }
        bool operator!=(const NodeIterator& other) const {
            return !(*this == other);
        }
     };
    NodeIterator node_begin() { return NodeIterator(this, 0); } // lub bez zera
    NodeIterator node_end() { return NodeIterator(this, v()); }
    class EdgeIterator : public Iterator<Edge<int>> { 
        Graph* graph;
        int row, col;
    public:        EdgeIterator(Graph* g, int r=0, int c=0) : graph(g), row(r), col(c) {
            while (row < graph->adj_matrix.size() && graph->adj_matrix[row][col] == nullptr) {
                col++;
                if (col >= graph->adj_matrix.size()) {
                    col = 0;
                    row++;
                }
            }
    }
        Edge<int> operator*() const override { return *(graph->adj_matrix[row][col]); }
        EdgeIterator& operator++() { // pre-inkrementacja
            do {
                col++;
                if (col >= graph->adj_matrix.size()) {
                    col = 0;
                    row++;
                }
            } while (row < graph->adj_matrix.size() && graph->adj_matrix[row][col] == nullptr);
            if (row >= graph->adj_matrix.size()) { // konwencja dla end()
                row = graph->adj_matrix.size();
                col = row;
            }
            return *this;
        }
        EdgeIterator operator++(int) { // post-inkrementacja
            EdgeIterator temp = *this;
            ++(*this);
            return temp;
        }
        bool operator==(const EdgeIterator& other) const {
            return graph == other.graph && row == other.row && col == other.col;
        }
        bool operator!=(const EdgeIterator& other) const {
            return !(*this == other);
        }
     };
    EdgeIterator edge_begin() { return EdgeIterator(this); }
    EdgeIterator edge_end() { return EdgeIterator(this, this->adj_matrix.size(), this->adj_matrix.size()); } // konwencja
    class AdjacentIterator : public Iterator<int> { 
        Graph* graph;
        int row, col;
    public:        AdjacentIterator(Graph* g, int r, int c=0) : graph(g), row(r), col(c) {
            while (col < graph->adj_matrix.size() && graph->adj_matrix[row][col] == nullptr) {
                col++;
            }
    }
        int operator*() const override { return col; }
        AdjacentIterator& operator++() { // pre-inkrementacja
            do {
                col++;
            } while (col < graph->adj_matrix.size() && graph->adj_matrix[row][col] == nullptr);
            return *this;
        }
        AdjacentIterator operator++(int) { // post-inkrementacja
            AdjacentIterator temp = *this;
            ++(*this);
            return temp;
        }
        bool operator==(const AdjacentIterator& other) const {
            return graph == other.graph && row == other.row && col == other.col;
        }
        bool operator!=(const AdjacentIterator& other) const {
            return !(*this == other);
        }
     };
    AdjacentIterator adj_begin(int r) { return AdjacentIterator(this, r); }
    AdjacentIterator adj_end(int r) { return AdjacentIterator(this, r, this->adj_matrix.size()); }
    Graph(int n, bool directed=false) : directed(directed) {
        adj_matrix = std::vector< std::vector<Edge<int> *> >(
            n, std::vector<Edge<int> *>(n, nullptr));
    }
    ~Graph() { clear(); } // trzeba zwolnić pamięć krawędzi
    bool is_directed() const override { return directed; }
    int v() const override {
        int count = 0;
        for (int i = 0; i < adj_matrix.size(); i++) {
            if(has_node(i)) count++;        // liczymy tylko wierzchołki, które mają krawędzie
        }   // ponieważ w tej implementacji wierzchołki usuniete nie są fizycznie usuwane z macierzy, a jedynie pozbawiane krawędzi
        return count;
    }
    int e() const override {
        if(directed) {
            int count = 0;
            for (const auto& row : adj_matrix) {
                for (const auto& edge : row) {
                    if (edge != nullptr) count++;
                }
            }
            return count;
        } else {    
            int count = 0;
            for (int i = 0; i < adj_matrix.size(); i++) {
                for (int j = i; j < adj_matrix.size(); j++) {
                    if (adj_matrix[i][j] != nullptr) count++;
                }
            }
            return count;
        }
    }
    int degree(int u) const override; // stopień wierzchołka
    int indegree(int u) const override;
    int outdegree(int u) const override;
    void add_node(int u) override;
    void del_node(int u) override;
    bool has_node(int u) const override;
    void add_edge(int u, int w, float weight=1.0); // dodanie krawędzi (u,w)
    void add_edge(Edge<int> edge) override;
    void del_edge(int u, int w); // usunięcie krawędzi (u,w)
    void del_edge(Edge<int> edge) override;
    bool has_edge(int u, int w) const override { // test istnienia krawędzi
        assert(has_node(u) && has_node(w));
        return adj_matrix[u][w] != nullptr;
    }
    bool has_edge(Edge<int> edge) const override {
        assert(has_node(edge.source) && has_node(edge.target));
        return adj_matrix[edge.source][edge.target] != nullptr;
    }
    float weight(int u, int w) const override; // waga krawędzi lub 0.0
    float weight(Edge<int> edge) const override;
    void clear() override; // usunięcie wszystkich krawędzi O(n^2)
    void display() const override;
};

int Graph::degree(int u) const {
    if(u >= adj_matrix.size()) return 0; // jeśli wierzchołek nie istnieje, stopień jest 0
    int deg = 0;
    if(directed) {
        deg = indegree(u) + outdegree(u);
    } else {
        for (const auto& edge : adj_matrix[u]) {
            if (edge != nullptr) deg++;
        }
    }
    return deg;
}
int Graph::indegree(int u) const {
    int indeg = 0;
    for (const auto& row : adj_matrix) {
        if (row[u] != nullptr) indeg++;
    }
    return indeg;
}
int Graph::outdegree(int u) const {
    int outdeg = 0;
    for (const auto& edge : adj_matrix[u]) {
        if (edge != nullptr) outdeg++;
    }
    return outdeg;
}
void Graph::add_node(int u) {
    if (u >= adj_matrix.size()) {
        int new_size = u + 1;
        adj_matrix.resize(new_size);
        for (auto& row : adj_matrix) {
            row.resize(new_size, nullptr);
        }
    }
}
void Graph::del_node(int u) {
    if (u < adj_matrix.size()) {
        for (int i = 0; i < adj_matrix.size(); i++) {
            if (adj_matrix[u][i] != nullptr) {
                delete adj_matrix[u][i];
                adj_matrix[u][i] = nullptr;
            }
            if (adj_matrix[i][u] != nullptr) {
                delete adj_matrix[i][u];
                adj_matrix[i][u] = nullptr;
            }
        }
    }
}
bool Graph::has_node(int u) const {
    if(u < adj_matrix.size() && degree(u) > 0) {
        return true;
    }
    return false;
}
void Graph::add_edge(int u, int w, float weight) {
    if (u >= adj_matrix.size() || w >= adj_matrix.size()) add_node(std::max(u, w));
    if (adj_matrix[u][w] == nullptr) {
        adj_matrix[u][w] = new Edge<int>(u, w, weight);
        if (!directed) {
            adj_matrix[w][u] = new Edge<int>(w, u, weight);
        }
    } else {
        adj_matrix[u][w]->weight = weight;
        if (!directed) {
            adj_matrix[w][u]->weight = weight;
        }
    }
}
void Graph::add_edge(Edge<int> edge) {
    add_edge(edge.source, edge.target, edge.weight);
}
void Graph::del_edge(int u, int w) {
    assert(has_node(u) && has_node(w));
    if (adj_matrix[u][w] != nullptr) {
        delete adj_matrix[u][w];
        adj_matrix[u][w] = nullptr;
        if (!directed) {
            delete adj_matrix[w][u];
            adj_matrix[w][u] = nullptr;
        }
    }
}
void Graph::del_edge(Edge<int> edge) {
    del_edge(edge.source, edge.target);
}
float Graph::weight(int u, int w) const {
    assert(has_node(u) && has_node(w));
    if (adj_matrix[u][w] != nullptr) {
        return adj_matrix[u][w]->weight;
    }
    return 0.0;
}
float Graph::weight(Edge<int> edge) const {
    return weight(edge.source, edge.target);
}
void Graph::clear() {
    for (auto& row : adj_matrix) {
        for (auto& edge : row) {
            if (edge != nullptr) {
                delete edge;
                edge = nullptr;
            }
        }
    }
}
void Graph::display() const {
    std::cout << (directed ? "Directed" : "Undirected") << " Graph:" << std::endl;
    for (int i = 0; i < adj_matrix.size(); i++) {
        for (int j = 0; j < adj_matrix.size(); j++) {
            if (adj_matrix[i][j] != nullptr) {
                std::cout << i << " -> " << j << " (weight: " << adj_matrix[i][j]->weight << ")" << std::endl;
            }
        }
    }
}

    

#endif
