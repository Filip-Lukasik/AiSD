#include <cassert>
#include <iostream>
#include "graph.h"
#include "connected.h"
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
    Graph g(10, false);
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
	for (auto n_it = g.node_begin();
		n_it != g.node_end();
		++n_it) {
		if(g.degree(*n_it) > 1) {
			for (auto m_it = g.neighbor_begin(*n_it);
				m_it != g.neighbor_end(*n_it);
				++m_it) {
				int v = (*m_it);
				if(g.degree(v) > 1) {
					g.del_edge(*n_it, v);
					break;
				}
				
			}
		}
	}

	g.display();
	auto algorithm = ConnectedComponents<int,Graph>(g);
	algorithm.run();
	for (int i = 0; i < algorithm.ncc; i++) {
		std::cout << "Component " << i << ": ";
		for (auto pair : algorithm.component) {
			if(pair.second == i) {
				std::cout << pair.first << " ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << "Total components: " << algorithm.ncc << std::endl;
	
	return 0;
}

