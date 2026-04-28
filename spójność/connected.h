#ifndef CONNECTED_H
#define CONNECTED_H

#include "unordered_map"
// connected.hpp
template<typename T, typename G> // node type, graph type
class ConnectedComponents {
    G& graph;
    std::unordered_map<T, bool> visited;
public:
    std::unordered_map<T, int> component; // a table for component numbers
    int ncc; // the number of connected components
    ConnectedComponents(G& g) : graph(g), ncc(0) {
        assert( !graph.is_directed() );
        for (auto n_it = graph.node_begin();
            n_it != graph.node_end();
            ++n_it) {
            visited[*n_it] = false;
        }
    }
    ~ConnectedComponents() = default; // destruktor
    void run(){
        for (auto n_it = graph.node_begin();
            n_it != graph.node_end();
            ++n_it) {
            if (!visited[*n_it]) {
                visit(*n_it);
                ncc++;
            }
        }
    }
    void visit(T u){
        visited[u] = true;
        component[u] = ncc;
        for (auto e_it = graph.neighbor_begin(u);
            e_it != graph.neighbor_end(u);
            ++e_it) {
            T v = (*e_it);
            if (!visited[v]) {
                visit(v);
            }
        }
    }
};
// Usage:
// auto algorithm = ConnectedComponents<int,Graph>(G); // macierz sąsiedztwa
// auto algorithm = ConnectedComponents<char,Graph<char>>(G); // lista sąsiedztwa
// algorithm.run();
// for (auto pair : algorithm.component)
//     std::cout << pair.first << " component " << pair.second << std::endl;
// std::cout << "total components " << algorithm.ncc << std::endl;

#endif