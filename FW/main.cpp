#include <cassert>
#include <iostream>
#include "graph.h"
#include "floydwarshall.h"
#include <cstdlib>
#include <ctime>

bool all_connected(std::vector<bool>& connected){
	for(bool b : connected)
		if(!b)
			return false;
	return true;
}

void print_path(const std::vector<std::vector<int>>& parent, int i, int j, const std::unordered_map<int, int>& node_index) {
	if (parent[node_index.at(i)][node_index.at(j)] == j) {
		std::cout << "no path to " << j;
	}
	else if (parent[node_index.at(i)][node_index.at(j)] == i) {
		std::cout << i << " -> " << j;
	} else {
		print_path(parent, i, parent[node_index.at(i)][node_index.at(j)], node_index);
		std::cout << " -> " << j;
	}
}

void print_path(const std::vector<std::vector<char>>& parent, char i, char j, const std::unordered_map<char, int>& node_index) {
	if (parent[node_index.at(i)][node_index.at(j)] == j) {
		std::cout << "no path to " << j;
	}
	else if (parent[node_index.at(i)][node_index.at(j)] == i) {
		std::cout << i << " -> " << j;
	} else {
		print_path(parent, i, parent[node_index.at(i)][node_index.at(j)], node_index);
		std::cout << " -> " << j;
	}	
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
	FloydWarshall<int, Graph<int>> floydwarshall(graph);
	floydwarshall.run();
	std::cout << "\nDistances :" << std::endl;
	int index = 0;
	for (auto it = floydwarshall.distance.begin(); it != floydwarshall.distance.end(); ++it) {
		int node = floydwarshall.index_node[index++];
		std::cout << "From Node " << node << ": ";
		int neighbor_index = 0;
		for(auto jt = it->begin(); jt != it->end(); ++jt) {
			int neighbor = floydwarshall.index_node[neighbor_index++];
			std::cout << "[" << neighbor << "] = " << *jt << "; ";
		}
		std::cout << std::endl;
	}
	std::cout << "\nParent :" << std::endl;
	index = 0;
	for (auto it = floydwarshall.parent.begin(); it != floydwarshall.parent.end(); ++it) {
		int node = floydwarshall.index_node[index++];
		std::cout << "From Node " << node << ": ";
		int neighbor_index = 0;
		for(auto jt = it->begin(); jt != it->end(); ++jt) {
			int neighbor = floydwarshall.index_node[neighbor_index++];
			if(neighbor == *jt && index != neighbor_index) {
				std::cout << "[" << neighbor << "] = No path; ";
			} else {
				std::cout << "[" << neighbor << "] = " << *jt << "; ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << "\nPaths :" << std::endl;
	for(auto it = graph.node_begin(); it != graph.node_end(); ++it) {
		int node = *it;
		std::cout << "From Node " << node << ": ";
		for(auto jt = graph.node_begin(); jt != graph.node_end(); ++jt) {
			int neighbor = *jt;
			if(neighbor == node) continue; // pomijamy ścieżki do samego siebie
			print_path(floydwarshall.parent, node, neighbor, floydwarshall.node_index);
			std::cout << "; ";
		}
		std::cout << std::endl;
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
	FloydWarshall<char, Graph<char>> floydwarshall2(graph2);
	floydwarshall2.run();
	std::cout << "\nDistances :" << std::endl;
	index = 0;
	for (auto it = floydwarshall2.distance.begin(); it != floydwarshall2.distance.end(); ++it) {
		char node = floydwarshall2.index_node[index++];
		std::cout << "From Node " << node << ": ";
		int neighbor_index = 0;
		for(auto jt = it->begin(); jt != it->end(); ++jt) {
			char neighbor = floydwarshall2.index_node[neighbor_index++];
			std::cout << "[" << neighbor << "] = " << *jt << "; ";
		}
		std::cout << std::endl;
	}
	std::cout << "\nParent :" << std::endl;
	index = 0;
	for (auto it = floydwarshall2.parent.begin(); it != floydwarshall2.parent.end(); ++it) {
		char node = floydwarshall2.index_node[index++];
		std::cout << "From Node " << node << ": ";
		int neighbor_index = 0;
		for(auto jt = it->begin(); jt != it->end(); ++jt) {
			char neighbor = floydwarshall2.index_node[neighbor_index++];
			if(neighbor == *jt && index != neighbor_index) {
				std::cout << "[" << neighbor << "] = No path; ";
			} else {
				std::cout << "[" << neighbor << "] = " << *jt << "; ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << "\nPaths :" << std::endl;
	for(auto it = graph2.node_begin(); it != graph2.node_end(); ++it) {
		char node = *it;
		std::cout << "From Node " << node << ": ";
		for(auto jt = graph2.node_begin(); jt != graph2.node_end(); ++jt) {
			char neighbor = *jt;
			if(neighbor == node) continue; // pomijamy ścieżki do samego siebie
			print_path(floydwarshall2.parent, node, neighbor, floydwarshall2.node_index);
			std::cout << "; ";
		}
		std::cout << std::endl;
	}
	return 0;
}