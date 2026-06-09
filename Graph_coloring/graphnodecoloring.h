#ifndef GRAPHNODECOLORING_H
#define GRAPHNODECOLORING_H

#include <queue>
#include <limits>
#include <unordered_map>
#include <unordered_set>

// graphnodecoloring.hpp
template <typename T, typename G> // node type, graph type
class GraphNodeColoring {
    G& graph;
    std::vector<T> order; // kolejność węzłów do kolorowania
    std::vector<int> degree; // stopień węzłów, może być używany do ustalenia kolejności kolorowania
    // inne potrzebne elementy
public:
    std::unordered_map<T, int> nodeColors; // mapa kolorów dla każdego węzła
    GraphNodeColoring(G& g) : graph(g) {
        order.reserve(graph.v());
        degree.reserve(graph.v());
        for (int i = 0; i < graph.v(); i++) {
            degree.push_back(0); // inicjalizacja stopni węzłów
            order.push_back(T()); // inicjalizacja kolejności węzłów, będzie nadpisywana później
        }
        // inicjalizacja kolorów węzłów, ustawienie na -1 (niepokolorowany)
        for (auto it = graph.node_begin(); it != graph.node_end(); ++it) {
            nodeColors[*it] = -1; // -1 oznacza, że węzeł nie jest pokolorowany
            degree[graph.degree(*it)]++; // wykorzystujemy stopień węzła do ustalenia kolejności kolorowania
        }
        auto it = degree.begin();
        ++it;
        for (auto it_prev = degree.begin(); it != degree.end(); ++it, ++it_prev) {
            *it += *it_prev; // kumulacja stopni węzłów
        }
        for (auto it = graph.node_begin(); it != graph.node_end(); ++it) {
            int d = graph.degree(*it);
            order[degree[d]-1] = *it; // umieszczamy węzeł w kolejności kolorowania
            degree[d]--; // zmniejszamy licznik dla tego stopnia
        }
    }
    ~GraphNodeColoring() = default; // destruktor
    void run(){
        // implementacja algorytmu kolorowania węzłów, np. algorytm zachłanny
        for (auto it = order.rbegin(); it != order.rend(); ++it) {
            T node = *it;
            std::unordered_set<int> usedColors; // zbiór kolorów użytych przez sąsiadów
            for (auto adj_it = graph.adj_begin(node); adj_it != graph.adj_end(node); ++adj_it) {
                T neighbor = *adj_it;
                if (nodeColors[neighbor] != -1) {
                    usedColors.insert(nodeColors[neighbor]);
                }
            }
            // znajdź najmniejszy kolor, który nie jest używany przez sąsiadów
            int color = 0;
            while (usedColors.count(color)) {
                color++;
            }
            nodeColors[node] = color; // przypisz kolor do węzła
        }
    }
};

#endif // GRAPHNODECOLORING_H