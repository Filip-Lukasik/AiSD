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
	Graph<int> closure_graph(true);
	std::cout << "\nDomknięcie przejściowe (Transitive Closure) :" << std::endl;
	for (int i = 0; i < graph.v(); i++) {
		for (int j = 0; j < graph.v(); j++) {
			if (floydwarshall.Transitive_closure[i][j]) {
				closure_graph.add_edge(floydwarshall.index_node[i], floydwarshall.index_node[j], 1);
			}
		}
	}
	closure_graph.display();
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
	Graph<char> closure_graph2(true);
	std::cout << "\nDomknięcie przejściowe (Transitive Closure) :" << std::endl;
	for (int i = 0; i < graph2.v(); i++) {
		for (int j = 0; j < graph2.v(); j++) {
			if (floydwarshall2.Transitive_closure[i][j]) {
				closure_graph2.add_edge(floydwarshall2.index_node[i], floydwarshall2.index_node[j], 1);
			}
		}
	}
	closure_graph2.display();
	return 0;
}