#include <cassert>
#include <iostream>
#include "binsearchtree.h"

int main(){
	BinarySearchTree<int> tree;
	BinarySearchTree<int> tree2;
	int size;
	tree.insert(5);
	tree.insert(1);
	tree.insert(2);
	tree.insert(3);
	tree.insert(4);
	tree.insert(7);
	tree.insert(8);
	tree.insert(0);
	tree.display();
	std::cout << "drzewo przed DSW" << std::endl << std::endl << std::endl;
	size = tree.tree_to_vine();
	assert( size == 8);
	tree.display();
	std::cout << "drzewo po tree vine" << std::endl << std::endl << std::endl;
	tree.vine_to_tree(size);
	tree.display();
	std::cout << "drzewo po vine to tree" << std::endl << std::endl << std::endl;
	for(int i=0;i<17;i++){
		tree2.insert(16-i);
	}
	tree2.display();
	std::cout << "drzewo przed DSW" << std::endl << std::endl << std::endl;
	tree2.DSW();
	tree2.display();
	std::cout << "drzewo po DSW" << std::endl << std::endl << std::endl;
}
