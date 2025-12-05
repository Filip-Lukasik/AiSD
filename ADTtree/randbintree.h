#ifndef RANDBINTREE
#define RANDBINTREE

#include <cstdlib>   // std::rand(), RAND_MAX, std::srand()
#include <iostream>
#include <cassert>
#include <stack>

// Szablon dla węzła drzewa binarnego i drzewa BST.
template <typename T>
struct BSTNode {
// the default access mode and default inheritance mode are public
    T value;
    BSTNode *left, *right;
    //BSTNode *parent;   // używane w pewnych zastosowaniach
    // kostruktor domyślny
    BSTNode() : value(T()), left(nullptr), right(nullptr) {}
    // konstruktor zwykły
    BSTNode(const T& item) : value(item), left(nullptr), right(nullptr) {}
    ~BSTNode() { delete left; delete right; } // destruktor rekurencyjny
    // UWAGA Jeżeli w BSTNode będzie domyślny destruktor postaci
    // ~BSTNode() = default; lub
    // ~BSTNode() {}
    // to wtedy destruktor drzewa i metoda clear() muszą zwolnić pamięć
    // wszystkich węzłów.
};

// Szablon dla przypadkowego drzewa binarnego.
template <typename T>
class RandomBinaryTree {
    BSTNode<T> *root;
public:
    RandomBinaryTree() : root(nullptr) {} // konstruktor domyślny
    ~RandomBinaryTree() { delete root; } // trzeba wyczyścić (rekurencyjnie)
    void clear() { delete root; root = nullptr; }
    bool empty() const { return root == nullptr; }
    T& top() { assert(root != nullptr); return root->value; } // podgląd korzenia
    void insert(const T& item) { root = insert(root, item); }
    //void remove(const T& item); // na razie nie usuwamy elementów
    // Szukając element dostajemy wskaźnik do elementu lub nullptr.
    T* search(const T& item) const {
        auto ptr = search(root, item);
        return ((ptr == nullptr) ? nullptr : &(ptr->value));
    }
    T* find_min() const;
    T* find_max() const;
    void preorder() { preorder(root); }
    void inorder() { inorder(root); }
    void postorder() { postorder(root); }
    void iter_preorder();
    void iter_inorder(); // trudne
    void iter_postorder(); // trudne
    void bfs(); // przejście poziomami (wszerz)
    void display() { display(root, 0); }
    int iter_calc_height();
    int rec_calc_height() { return rec_calc_height(root); }
    int rec_calc_height(BSTNode<T> *node);

    // Metody bezpośrednio odwołujące się do node.
    // Mogą działać na poddrzewie.
    BSTNode<T> * insert(BSTNode<T> *node, const T& item); // zwraca nowy korzeń
    BSTNode<T> * search(BSTNode<T> *node, const T& item) const;
    void preorder(BSTNode<T> *node);
    void inorder(BSTNode<T> *node);
    void postorder(BSTNode<T> *node);
    void display(BSTNode<T> *node, int level);
    virtual void visit(BSTNode<T> *node) {
        assert(node != nullptr);
        std::cout << "visiting " << node->value << std::endl;
    }
};

template <typename T>
BSTNode<T> * RandomBinaryTree<T>::insert(BSTNode<T> *node, const T& item) {
    if (node == nullptr) {
        return new BSTNode<T>(item);
    }
    //std::srand(std::time(nullptr)); // use current time as seed for random generator
    if (std::rand() % 2) { // można lepiej
        node->left = insert(node->left, item);
    } else {
        node->right = insert(node->right, item);
    }
    return node; // zwraca nowy korzeń
}
// Wyświetlanie obróconego (counterclockwise) drzewa binarnego.
template <typename T>
void RandomBinaryTree<T>::display(BSTNode<T> *node, int level) {
    if (node == nullptr) return;
    display(node->right, level + 1);
    for (int i = 0; i < level; i++) {
        std::cout << "   |";
    }
    std::cout << "---" << node->value << std::endl;
    display(node->left, level + 1);
}

template <typename T>
int RandomBinaryTree<T>::iter_calc_height() {
	if(root == nullptr){ return 0; }
	std::stack<BSTNode<T> *> s1;
	std::stack<BSTNode<T> *> s2;
	BSTNode<T> * cur;
	int height = 0;
	bool process_s1 = true;
	s1.push(root);
	while( !s1.empty() || !s2.empty() ){
		height++;
		if(process_s1){
			while( !s1.empty() ){
				cur = s1.top();
				s1.pop();
				if(cur->left != nullptr){
					s2.push(cur->left);
				}
				if(cur->right != nullptr){
					s2.push(cur->right);	
				}		
			}
			process_s1 = false;
		}
		else{
			while( !s2.empty() ){
				cur = s2.top();
				s2.pop();
				if(cur->left != nullptr){
					s1.push(cur->left);
				}
				if(cur->right != nullptr){
					s1.push(cur->right);	
				}		
			}
			process_s1 = true;
		}
	}
	return height;
}

template <typename T>
int RandomBinaryTree<T>::rec_calc_height(BSTNode<T> *node) {
	if(node == nullptr){ return 0; }
	int left = rec_calc_height(node->left);
	int right = rec_calc_height(node->right);
	if(left>right){ return 1 + left; }
	else{ return 1 + right; }
}
#endif
