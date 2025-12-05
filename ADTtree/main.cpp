#include <cassert>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "randbintree.h"

int main(){
	RandomBinaryTree<int> tree;
	std::srand(std::time(nullptr));
	assert( tree.iter_calc_height() == tree.rec_calc_height() );
	assert( tree.iter_calc_height() == 0 );
	tree.insert(5);
	assert( tree.iter_calc_height() == tree.rec_calc_height() );
	assert( tree.iter_calc_height() == 1 );
	tree.insert(1);
	assert( tree.iter_calc_height() == tree.rec_calc_height() );
	assert( tree.iter_calc_height() == 2 );
	tree.insert(2);
	assert( tree.iter_calc_height() == tree.rec_calc_height() );
	tree.insert(3);
	assert( tree.iter_calc_height() == tree.rec_calc_height() );
	tree.insert(4);
	assert( tree.iter_calc_height() == tree.rec_calc_height() );
	tree.insert(7);
	assert( tree.iter_calc_height() == tree.rec_calc_height() );
	tree.insert(8);
	assert( tree.iter_calc_height() == tree.rec_calc_height() );
	tree.insert(0);
	assert( tree.iter_calc_height() == tree.rec_calc_height() );
	tree.display();
	std::cout << "Height(iter) = "<< tree.iter_calc_height() << std::endl;
	std::cout << "Height(rec) = "<< tree.rec_calc_height() << std::endl;
}
