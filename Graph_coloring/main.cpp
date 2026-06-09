#include <cassert>
#include <iostream>
#include "graph.h"
#include "graphnodecoloring.h"
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
    Graph<int> graph(false);
	for (int i = 0; i < 10; i++) {
		graph.add_node(i);
	}
	std::vector<bool> connected(10, false);
	std::vector<int> nodes;
	int r = rand() % 10;
	connected[r] = true;
	nodes.push_back(r);
	while(!all_connected(connected)){
		int u = nodes[rand() % nodes.size()];
		int v = rand() % 10;
		if (graph.has_edge(u, v) || u == v) continue; // unikamy pętli i wielokrotnych krawędzi
		graph.add_edge(u, v);
		connected[v] = true;
		nodes.push_back(v);
	}
	std::cout << "Graph created with 10 nodes and random edges." << std::endl;
	graph.display();
	GraphNodeColoring<int, Graph<int>> coloring(graph);
	coloring.run();
	std::cout << "Node colors:" << std::endl;
	for (const auto& pair : coloring.nodeColors) {
		std::cout << "Node " << pair.first << ": Color " << pair.second << std::endl;
	}
	Graph<char> graph2(false);
	for (char c = 'A'; c <= 'J'; c++) {
		graph2.add_node(c);
	}
	std::vector<bool> connected2(10, false);
	std::vector<char> nodes2;
	char r2 = 'A' + rand() % 10;
	connected2[r2 - 'A'] = true;
	nodes2.push_back(r2);
	while(!all_connected(connected2)){
		char u = nodes2[rand() % nodes2.size()];
		char v = 'A' + rand() % 10;
		if (graph2.has_edge(u, v) || u == v) continue; // unikamy pętli i wielokrotnych krawędzi
		graph2.add_edge(u, v);
		connected2[v - 'A'] = true;
		nodes2.push_back(v);
	}
	std::cout << "Graph created with 10 nodes and random edges." << std::endl;
	graph2.display();
	GraphNodeColoring<char, Graph<char>> coloring2(graph2);
	coloring2.run();
	std::cout << "Node colors:" << std::endl;
	for (const auto& pair : coloring2.nodeColors) {
		std::cout << "Node " << pair.first << ": Color " << pair.second << std::endl;
	}
	return 0;
}