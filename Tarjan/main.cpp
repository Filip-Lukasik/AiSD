#include <cassert>
#include <iostream>
#include "graph.h"
#include "tarjan.h"
#include <cstdlib>
#include <ctime>

bool all_connected(std::vector<bool>& connected){
	for(bool b : connected)
		if(!b)
			return false;
	return true;
}

int main(){
	srand(time(nullptr));
    Graph g(10, true);
	std::vector<bool> connected(10, false);
	std::vector<int> nodes;
	int r = rand() % 10;
	connected[r] = true;
	nodes.push_back(r);
	while(!all_connected(connected)){
		int u = nodes[rand() % nodes.size()];
		int v = rand() % 10;
		if(connected[v]) continue;
		g.add_edge(u, v);
		connected[v] = true;
		nodes.push_back(v);
	}

	g.display();
	std::vector<int> topsort = topsort_dfs<int, Graph>(g);
	std::cout << "Topological Sort: ";
	for (int node : topsort) {
		std::cout << node << " ";
	}
	std::cout << std::endl;
	
	return 0;
}

