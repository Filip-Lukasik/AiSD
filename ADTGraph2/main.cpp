#include <cassert>
#include <iostream>
#include "graph.h"

int main(){
    Graph g(5, true);
	g.add_edge(0, 1);
	g.add_edge(0, 2);
	g.add_edge(1, 2);
	g.add_edge(3, 4);
	g.display();
	assert(g.has_edge(0, 1) == true);
	assert(g.has_edge(1, 0) == false);
	assert(g.has_node(5) == false);
	assert(g.has_node(2) == true);
	assert(g.v() == 5);
	assert(g.e() == 4);
	assert(g.degree(0) == 2);
	assert(g.indegree(2) == 2);
	assert(g.outdegree(0) == 2);
	g.del_edge(0, 1);
	assert(g.e() == 3);
	g.clear();
	assert(g.e() == 0);
	g.del_node(2);
	assert(g.v() == 5);
	assert(g.degree(2) == 0);
	assert(g.has_node(2) == true);
	assert(g.has_edge(0, 2) == false);
	assert(g.has_edge(1, 2) == false);

	return 0;
}

