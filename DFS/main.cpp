#include <cassert>
#include <iostream>
#include "graph.h"
#include "dfs.h"
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
		g.add_edge(u, v);
		connected[v] = true;
		nodes.push_back(v);
	}

	g.display();

	auto dfs_algorithm = DFS<int, Graph>(g);
	dfs_algorithm.run();
	std::cout << "Preorder: ";
	std::cout << std::endl;
	for (auto& node : dfs_algorithm.preorder) {
		std::cout << node << " ";
	}
	std::cout << std::endl;
	std::cout << "Postorder: ";
	std::cout << std::endl;
	for (auto& node : dfs_algorithm.postorder) {
		std::cout << node << " ";
	}
	std::cout << std::endl;
	std::cout << "DFS Tree (Parent Map): " << std::endl;
	for (auto& pair : dfs_algorithm.parent) {
		std::cout << "Node: " << pair.first << ", Parent: " << pair.second << std::endl;
	}
	return 0;
}

