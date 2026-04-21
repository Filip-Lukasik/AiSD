#ifndef TARJAN_H
#define TARJAN_H

#include "dfs.h"
#include <algorithm> // for std::reverse

template<typename T, typename G> // node type, graph type
std::vector<T> topsort_dfs(G& graph) {
    DFS<T, G> dfs_algorithm(graph);
    dfs_algorithm.run();
    std::vector<T> topsort = dfs_algorithm.postorder;
    std::reverse(topsort.begin(), topsort.end());
    return topsort;
}

#endif // TARJAN_H