#include <cassert>
#include <iostream>
#include "blackredtree.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

std::vector<int> generate_unique_random_numbers(int n, int min, int max) {
	std::vector<int> numbers;
	for (int i = min; i <= max; ++i) {
		numbers.push_back(i);
	}
	std::random_shuffle(numbers.begin(), numbers.end());
	numbers.resize(n);
	return numbers;
}

int main(){
	BlackRedTree<int> tree;
	srand(time(0));
	std::cout << "Inserting: unique random values from 1 to 100" << std::endl;
	std::vector<int> values = generate_unique_random_numbers(20, 1, 100);
	for (int value : values) {
		std::cout << "inserting " << value << std::endl;
		tree.insert(value);
	}
	std::cout << "Tree after insertions:" << std::endl;
	tree.display();
	std::cout << "Is valid black-red tree? " << (tree.is_black_red_tree() ? "Yes" : "No") << std::endl;
	std::cout << "Deleting: 5 random values from the inserted ones" << std::endl;
	std::random_shuffle(values.begin(), values.end());
	for (int i = 0; i < 5; ++i) {
		std::cout << "removing " << values[i] << std::endl;
		tree.remove(values[i]);
	}
	std::cout << "Tree after deletions:" << std::endl;
	tree.display();
	std::cout << "Is valid black-red tree? " << (tree.is_black_red_tree() ? "Yes" : "No") << std::endl;
}