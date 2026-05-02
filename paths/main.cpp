#include <cassert>
#include <iostream>
#include "graph.h"
#include "dijkstra.h"
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
    Graph<int> graph(true);
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
		graph.add_edge(u, v, rand() % 10 + 1);
		connected[v] = true;
		nodes.push_back(v);
	}
	std::cout << "Graph created with 10 nodes and random edges." << std::endl;
	graph.display();
	Dijkstra<int, Graph<int>> dijkstra(graph);
	dijkstra.run(0);
	std::cout << "Distances from source 0:" << std::endl;
	for (const auto& pair : dijkstra.distance) {
		std::cout << "Node " << pair.first << ": " << pair.second << std::endl;
	}
	std::cout << "Shortest paths from source 0:" << std::endl;
	for (auto it = graph.node_begin(); it != graph.node_end(); ++it) {
		int node = *it;
		std::cout << "Node " << node << ": ";
		int current = node;
		while (current != dijkstra.parent[current]) {
			std::cout << current << " <- ";
			current = dijkstra.parent[current];
		}
		if (current == 0) {
			std::cout << current << std::endl; // źródło
		} else {
			std::cout << "No path" << std::endl; // brak ścieżki
		}
	}
	Graph<char> graph2(true);
	std::vector<char> all_nodes;
	for (char i = 'A'; i < 'A' + 10; i++) {
		all_nodes.push_back(i);
		graph2.add_node(i);
	}
	std::vector<bool> connected2(10, false);
	std::vector<char> nodes2;
	r = rand() % 10;
	char cr = all_nodes[r];
	connected2[r] = true;
	nodes2.push_back(cr);
	while(!all_connected(connected2)){
		char cu = nodes2[rand() % nodes2.size()];
		int v = rand() % 10;
		char cv = all_nodes[v];
		if (graph2.has_edge(cu, cv) || cu == cv) continue; // unikamy pętli i wielokrotnych krawędzi
		graph2.add_edge(cu, cv, rand() % 10 + 1);
		connected2[v] = true;
		nodes2.push_back(cv);
	}
	std::cout << "Graph created with 10 nodes and random edges." << std::endl;
	graph2.display();
	Dijkstra<char, Graph<char>> dijkstra2(graph2);
	dijkstra2.run('A');
	std::cout << "Distances from source A:" << std::endl;
	for (const auto& pair : dijkstra2.distance) {
		std::cout << "Node " << pair.first << ": " << pair.second << std::endl;
	}
	std::cout << "Shortest paths from source A:" << std::endl;
	for (auto it = graph2.node_begin(); it != graph2.node_end(); ++it) {
		char node = *it;
		std::cout << "Node " << node << ": ";
		char current = node;
		while (current != dijkstra2.parent[current]) {
			std::cout << current << " <- ";
			current = dijkstra2.parent[current];
		}
		if (current == 'A') {
			std::cout << current << std::endl; // źródło
		} else {
			std::cout << "No path" << std::endl; // brak ścieżki
		}
	}
}
