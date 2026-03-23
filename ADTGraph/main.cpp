#include <cassert>
#include <iostream>
#include "graph.h"

int main(){
    Graph g(5, true); // directed graph with 5 nodes
	g.add_edge(0, 1, 2.5);
	g.add_edge(0, 2, 1.0);
	g.add_edge(1, 3, 3.0);
	g.add_edge(2, 3, 1.5);
	g.add_edge(3, 4, 2.0);

	assert(g.has_node(0));
	assert(g.has_node(4));
	assert(!g.has_node(5));
	assert(g.has_edge(0, 1));
	assert(g.has_edge(1, 3));
	assert(!g.has_edge(1, 0));
	assert(g.weight(0, 1) == 2.5);
	assert(g.v() == 5);
	assert(g.e() == 5);
	assert(g.degree(0) == 2);
	assert(g.indegree(3) == 2);
	assert(g.outdegree(0) == 2);
	g.del_edge(0, 1);
	assert(!g.has_edge(0, 1));
	assert(g.e() == 4);
	assert(g.degree(0) == 1);
	assert(g.v() == 5);
	assert(g.outdegree(0) == 1);
	g.add_edge(0, 1, 2.5);
	g.del_node(3);
	assert(!g.has_node(3));
	int v = g.v();
	g.add_node(5); // dodajemy wierzchołek 5, który nie jest połączony z żadnym innym
	assert(!g.has_node(5)); // ponieważ wierzchołek 5 nie ma żadnych krawędzi, nie jest uważany za istniejący w grafie
	assert(g.v() == v); // liczba wierzchołków nie powinna się zmienić, ponieważ wierzchołek 5 nie jest uważany za istniejący
	g.add_edge(5, 0, 1.0); // teraz wierzchołek 5 jest połączony z wierzchołkiem 0
	assert(g.has_node(5)); // teraz wierzchołek 5 jest uważany za istniejący w grafie, ponieważ ma krawędź do wierzchołka 0
	assert(g.v() == v + 1); // liczba wierzchołków powinna wzrosnąć o 1
	
	for (auto it = g.edge_begin(); it != g.edge_end(); ++it) {
		Edge<int> edge = *it;
		assert(g.has_edge(edge.source, edge.target));
	}
	for (auto it = g.node_begin(); it != g.node_end(); ++it) {
		int u = *it;
		for (auto it2 = g.adj_begin(u); it2 != g.adj_end(u); ++it2) {
			int v = *it2;
			assert(g.has_edge(u, v));
		}
	}
}

