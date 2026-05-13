#ifndef FLOYDWARSHALL_H
#define FLOYDWARSHALL_H

#include <queue>
#include <limits>
#include <unordered_map>

// floydwarshall.hpp
template <typename T, typename G> // node type, graph type
class FloydWarshall {
    G& graph;
    // inne potrzebne elementy
public:
    std::unordered_map<int, T> index_node; // mapowanie indeksów na wierzchołki
    std::unordered_map<T, int> node_index; // mapowanie wierzchołków na indeksy
    std::vector<std::vector<bool>> Transitive_closure; // macierz osiągalności
    FloydWarshall(G& g) : graph(g) { 
        // inicjalizacja parent i distance
        Transitive_closure.resize(graph.v(), std::vector<bool>(graph.v(), false));
        int index = 0;
        for (auto it = graph.node_begin(); it != graph.node_end(); ++it) {
            index_node[index] = *it;
            node_index[*it] = index++;
        }
        for (auto it = graph.node_begin(); it != graph.node_end(); ++it) {
            T node = *it;
            Transitive_closure[node_index[node]][node_index[node]] = true; // osiągalność do samego siebie jest true
            for (auto adj_it = graph.adj_begin(node); adj_it != graph.adj_end(node); ++adj_it) {
                T neighbor = *adj_it;
                Transitive_closure[node_index[node]][node_index[neighbor]] = true; // osiągalność do sąsiada jest true
            }
        }
    }
    ~FloydWarshall() = default; // destruktor
    void run(){
        // implementacja algorytmu Floyda-Warshalla
        int n = graph.v();
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (!Transitive_closure[i][j] && Transitive_closure[i][k] && Transitive_closure[k][j]) {
                        Transitive_closure[i][j] = true; // jeśli i jest osiągalne z k, a k jest osiągalne z j, to i jest osiągalne z j
                    }
                }
            }
        }
    }
};

#endif // FLOYDWARSHALL_H