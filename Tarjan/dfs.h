#ifndef DFS_H
#define DFS_H
// dfs.hpp
#include <unordered_map>
#include <vector>
// dfs.hpp
template<typename T, typename G> // node type, graph type
class DFS {
    G& graph;
    std::unordered_map<T, bool> visited;
public:
    std::vector<T> preorder;
    std::vector<T> postorder;
    std::unordered_map<T, T> parent; // drzewo DFS
    DFS(G& g) : graph(g) {
        for (auto n_it = graph.node_begin();
            n_it != graph.node_end();
            ++n_it) {
            visited[*n_it] = false;
            parent[*n_it] = *n_it; // konwencja, brak rodzica
        }
    }
    ~DFS() = default; // destruktor
    void run(T u) { // badamy jedną składową spójną
        visit(u);
    }
    void run() {
        for (auto n_it = graph.node_begin();
            n_it != graph.node_end();
            ++n_it) {
            if (!visited[*n_it])
                visit(*n_it);
        }
    }
    void visit(T u){
        visited[u] = true;
        preorder.push_back(u);
        for (auto v_it = graph.neighbor_begin(u);
            v_it != graph.neighbor_end(u);
            ++v_it) {
            if (!visited[*v_it]) {
                parent[*v_it] = u;
                visit(*v_it);
            }
        }
        postorder.push_back(u);
    }
};
// Usage:
// auto algorithm = DFS<int,Graph>(graph); // macierz sąsiedztwa
// auto algorithm = DFS<char,Graph<char>>(graph); // lista sąsiedztwa
// algorithm.run(start_node);
// for (auto& node : algorithm.preorder) { ... }
// for (auto& node : algorithm.postorder) { ... }


#endif
