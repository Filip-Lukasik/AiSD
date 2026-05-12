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
    std::vector<std::vector<float>> distance; // macierz odległości
    std::vector<std::vector<T>> parent; // macierz poprzedników
    FloydWarshall(G& g) : graph(g) { 
        // inicjalizacja parent i distance
        distance.resize(graph.v(), std::vector<float>(graph.v(), std::numeric_limits<float>::infinity()));
        parent.resize(graph.v(), std::vector<T>(graph.v(), T()));
        int index = 0;
        for (auto it = graph.node_begin(); it != graph.node_end(); ++it) {
            index_node[index] = *it;
            node_index[*it] = index++;
        }
        for (auto it = graph.node_begin(); it != graph.node_end(); ++it) {
            T node = *it;
            distance[node_index[node]][node_index[node]] = 0; // odległość do samego siebie jest 0
            for(int j = 0; j < graph.v(); j++) {
                parent[node_index[node]][j] = index_node[j]; // na początku poprzednik to węzeł docelowy
            }
            for (auto adj_it = graph.adj_begin(node); adj_it != graph.adj_end(node); ++adj_it) {
                T neighbor = *adj_it;
                distance[node_index[node]][node_index[neighbor]] = graph.weight(node, neighbor); // odległość do sąsiada
                parent[node_index[node]][node_index[neighbor]] = node; // poprzednik to węzeł źródłowy
            }
        }
    }
    ~FloydWarshall() = default; // destruktor
    int run(){
        // implementacja algorytmu Floyda-Warshalla
        int n = graph.v();
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (distance[i][k] == std::numeric_limits<float>::infinity() || distance[k][j] == std::numeric_limits<float>::infinity()) {
                        continue; // pomijamy przypadki, gdzie nie ma ścieżki
                    }
                    if (distance[i][j] > distance[i][k] + distance[k][j]) {
                        distance[i][j] = distance[i][k] + distance[k][j];
                        parent[i][j] = parent[k][j]; // aktualizacja poprzednika
                    }
                }
            }
        }
        // Sprawdzenie, czy istnieje ujemny cykl
        for (int i = 0; i < n; i++) {
            if (distance[i][i] < 0) {
                return -1; // wykryto ujemny cykl
            }
        }
        return 0;
    }
};

#endif // FLOYDWARSHALL_H