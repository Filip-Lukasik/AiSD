#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <queue>
#include <limits>
#include <unordered_map>

// dijkstra.hpp
template <typename T, typename G> // node type, graph type
class Dijkstra {
    G& graph;
    // inne potrzebne elementy
public:
    std::unordered_map<T, T> parent;     // drzewo najkrótszych ścieżek
    std::unordered_map<T, float> distance; // odległość od źródła
    Dijkstra(G& g) : graph(g) { 
        // inicjalizacja parent i distance
        for (auto it = graph.node_begin(); it != graph.node_end(); ++it) {
            T node = *it;
            parent[node] = node; // na początku każdy wierzchołek jest swoim rodzicem
            distance[node] = std::numeric_limits<float>::infinity(); // odległość nieskończona
        }
    }
    ~Dijkstra() = default; // destruktor
    void run(T u){
        // implementacja algorytmu Dijkstry
        distance[u] = 0; // odległość do źródła jest 0
        // kolejka priorytetowa do wyboru wierzchołka o najmniejszej odległości
        std::priority_queue<std::pair<float, T>, std::vector<std::pair<float, T>>, std::greater<std::pair<float, T>>> pq;
        pq.push({0, u});
        while (!pq.empty()) {
            std::pair<float, T> current = pq.top();
            float dist = current.first;
            T node = current.second;
            pq.pop();
            if (dist > distance[node]) continue; // jeśli odległość jest większa niż aktualna, pomijamy
            for (auto it = graph.adj_begin(node); it != graph.adj_end(node); ++it) {
                T neighbor = *it;
                float weight = graph.weight(node, neighbor);
                if (distance[node] + weight < distance[neighbor]) {
                    distance[neighbor] = distance[node] + weight;
                    parent[neighbor] = node;
                    pq.push({distance[neighbor], neighbor});
                }
            }
        }
    }
};
// Usage:
// auto algorithm = Dijkstra<int,Graph>(G); // macierz sąsiedztwa
// auto algorithm = Dijkstra<char,Graph<char>>(G); // lista sąsiedztwa
// algorithm.run(source);
// for (auto& pair : algorithm.distance)
//     std::cout << pair.first << " distance : " << pair.second << std::endl;
#endif // DIJKSTRA_H