#ifndef BLACKREDTREE
#define BLACKREDTREE

#include <iostream>
#include <queue>

template <typename T>
struct BSTNode {
    T value;
    bool is_black;
    BSTNode *left, *right;
    BSTNode *parent;
    BSTNode() : value(T()), is_black(false), left(nullptr), right(nullptr), parent(nullptr) {}
    BSTNode(const T& item) : value(item), is_black(false), left(nullptr), right(nullptr), parent(nullptr) {}
    ~BSTNode() { delete left; delete right; }
};

template <typename T>
class BlackRedTree {
    BSTNode<T> *root;
public:
    BlackRedTree() : root(nullptr) {}
    ~BlackRedTree() { delete root; }
    void clear() { delete root; root = nullptr; }
    bool empty() const { return root == nullptr; }
	bool is_black_red_tree() const;
    T& top() { assert(root != nullptr); return root->value; }
    void insert(const T& item);
	void remove(const T& item);
	BSTNode<T>* search(const T& item) const { return search(root, item); }
    T* iter_search(const T& item) const { // wg libavl
        for (auto node=root; node != nullptr; ) {
            if (item == node->value) {
                return &(node->value);
            } else if (item < node->value) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return nullptr;
    }
    T* find_min() const;
    T* find_max() const;
    void preorder() { preorder(root); }
    void inorder() { inorder(root); }
    void postorder() { postorder(root); }
    void bfs();
    void display() { display(root, 0); }
private:
    BSTNode<T> * insert(BSTNode<T> *node,BSTNode<T> *parent, BSTNode<T> *nowy);
    BSTNode<T> * search(BSTNode<T> *node, const T& item) const;
    BSTNode<T> * rotate_right(BSTNode<T> *node);
    BSTNode<T> * rotate_left(BSTNode<T> *node);
    bool is_node_black(BSTNode<T> *node) const {
    	if ( node == nullptr){
			return true;
		}
		return node->is_black;
    }
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
void BlackRedTree<T>::insert(const T& item) {
	BSTNode<T> *cur = new BSTNode<T>(item);
    root = insert(root,nullptr,cur);
	BSTNode<T> *temp;
	if(cur == root) { root->is_black = true; }
	while(cur != root && !is_node_black(cur->parent)){
		if(cur->parent->parent->left == cur->parent){
			if(is_node_black(cur->parent->parent->right)){
				if(cur == cur->parent->right){
					cur = cur->parent;
					temp = cur->parent;
					if(temp->left == cur){
						temp->left = rotate_left(cur);
						temp->left->parent = temp;
					}
					else{
						temp->right = rotate_left(cur);
						temp->right->parent = temp;
					}
				}
				cur->parent->is_black = true;
				cur->parent->parent->is_black = false;
				if(cur->parent->parent == root){
					root = rotate_right(root);
					root->parent = nullptr;
					root->is_black = true;
				}
				else{
					temp = cur->parent->parent->parent;
					if(temp->left == cur->parent->parent){
						temp->left = rotate_right(cur->parent->parent);
						temp->left->parent = temp;
					}
					else{
						temp->right = rotate_right(cur->parent->parent);
						temp->right->parent = temp;
					}
				}
			}
			else{
				cur->parent->is_black = true;
				cur->parent->parent->right->is_black = true;
				cur = cur->parent->parent;
				if(cur != root){
					cur->is_black = false;
				}
			}
		}
		else{	
			if(is_node_black(cur->parent->parent->left)){
				if(cur == cur->parent->left){
					cur = cur->parent;
					temp = cur->parent;
					if(temp->left == cur){
						temp->left = rotate_right(cur);
						temp->left->parent = temp;
					}
					else{
						temp->right = rotate_right(cur);
						temp->right->parent = temp;
					}
				}
				cur->parent->is_black = true;
				cur->parent->parent->is_black = false;
				if(cur->parent->parent == root){
					root = rotate_left(root);
					root->parent = nullptr;
					root->is_black = true;
				}
				else{
					temp = cur->parent->parent->parent;
					if(temp->left == cur->parent->parent){
						temp->left = rotate_left(cur->parent->parent);
						temp->left->parent = temp;
					}
					else{
						temp->right = rotate_left(cur->parent->parent);
						temp->right->parent = temp;
					}
				}
			}
			else{
				cur->parent->is_black = true;
				cur->parent->parent->left->is_black = true;
				cur = cur->parent->parent;
				if(cur != root){
					cur->is_black = false;
				}
			}
		}
	}	
}

template <typename T>
BSTNode<T> * BlackRedTree<T>::insert(BSTNode<T> *node,BSTNode<T> *parent,BSTNode<T> *nowy) {
    if (node == nullptr) {
        nowy->parent = parent;
	return nowy;
    }
    if (nowy->value < node->value) {
        node->left = insert(node->left,node, nowy);
    } else {
        node->right = insert(node->right,node, nowy);
    }
    return node;
}

template <typename T>
void BlackRedTree<T>::remove(const T& item) {
	BSTNode<T> *node = search(root, item);
	if (node == nullptr) return;
	BSTNode<T> *extra_black_node = nullptr;
	BSTNode<T> *extra_black_parent = nullptr;
	bool fix_needed = false;
	if (node->left == nullptr && node->right == nullptr) {
		if (node == root) {
			delete root;
			root = nullptr;
		} else {
			if (node->parent->left == node) {
				node->parent->left = nullptr;
			} else {
				node->parent->right = nullptr;
			}
			if (is_node_black(node)) {
				fix_needed = true;
				extra_black_node = nullptr;
				extra_black_parent = node->parent;
			}
		}
	} else if (node->left == nullptr) {
		if(node->parent == nullptr){
			root = node->right;
			root->parent = nullptr;
		}
		else if (node->parent->left == node) {
			node->parent->left = node->right;
			node->right->parent = node->parent;
		} else {
			node->parent->right = node->right;
			node->right->parent = node->parent;
		}
		if(is_node_black(node)){
			node->right->is_black = true;
		}
	} else if (node->right == nullptr) {
		if(node->parent == nullptr){
			root = node->left;
			root->parent = nullptr;
		}
		else if (node->parent->left == node) {
			node->parent->left = node->left;
			node->left->parent = node->parent;
		} else {
			node->parent->right = node->left;
			node->left->parent = node->parent;
		}
		if(is_node_black(node)){
			node->left->is_black = true;
		}
	} else {
		BSTNode<T> *successor = node->right;
		while (successor->left != nullptr) {
			successor = successor->left;
		}
		if (successor == node->right) {
			successor->parent = node->parent;
			if (node->parent == nullptr) {
				root = successor;
			} else if (node->parent->left == node) {
				node->parent->left = successor;
			} else {
				node->parent->right = successor;
			}
			successor->left = node->left;
			node->left->parent = successor;
			if(is_node_black(successor)){
					fix_needed = true;
					extra_black_node = successor->right;
					extra_black_parent = successor;
				}
			if(is_node_black(node)){
				successor->is_black = true;
			}
			else{
				successor->is_black = false;
			}
		}
		else {
			node->value = successor->value;
			if(successor->right == nullptr){
				successor->parent->left = nullptr;
			}
			else{
				successor->parent->left = successor->right;
				successor->right->parent = successor->parent;
			}
			if(is_node_black(successor)){
				fix_needed = true;
				extra_black_node = successor->right;
				extra_black_parent = successor->parent;
			}
			node = successor;
		}
		node->left = nullptr;
		node->right = nullptr;
		delete node;
	}
	if(fix_needed){
		BSTNode<T> *sibling, *temp;
		
		while(extra_black_node != root && is_node_black(extra_black_node)){
			if(extra_black_node == nullptr){
				if(extra_black_parent->left == extra_black_node){
					sibling = extra_black_parent->right;
				}
				else{
					sibling = extra_black_parent->left;
				}
			}
			else{
				extra_black_parent = extra_black_node->parent;
				if(extra_black_parent->left == extra_black_node){
					sibling = extra_black_parent->right;
				}
				else{
					sibling = extra_black_parent->left;
				}
			}
			if(!is_node_black(sibling)){
				sibling->is_black = true;
				extra_black_parent->is_black = false;
				temp = extra_black_parent->parent;
				if(sibling == extra_black_parent->right){	
					if(temp == nullptr){
						root = rotate_left(extra_black_parent);
						root->parent = nullptr;
					}
					else if(temp->left == extra_black_parent){
						temp->left = rotate_left(extra_black_parent);
						temp->left->parent = temp;
					}
					else{
						temp->right = rotate_left(extra_black_parent);
						temp->right->parent = temp;
					}
				}
				else{
					if(temp == nullptr){
						root = rotate_right(extra_black_parent);
						root->parent = nullptr;
					}
					else if(temp->left == extra_black_parent){
						temp->left = rotate_right(extra_black_parent);
						temp->left->parent = temp;
					}
					else{
						temp->right = rotate_right(extra_black_parent);
						temp->right->parent = temp;
					}
				}
			}
			else if(sibling != nullptr && is_node_black(sibling->left) && is_node_black(sibling->right)){
				sibling->is_black = false;
				extra_black_node = extra_black_parent;
				extra_black_parent = extra_black_parent->parent;
				continue;
			}
			else{
				if(sibling != nullptr){
					if(sibling == extra_black_parent->right){
						if(is_node_black(sibling->right)){
							sibling->left->is_black = true;
							sibling->is_black = false;
							temp = sibling->parent;
							temp->right = rotate_right(sibling);
							temp->right->parent = temp;
							sibling = sibling->parent;
						}
						sibling->is_black = extra_black_parent->is_black;
						extra_black_parent->is_black = true;
						if(sibling->right != nullptr){
							sibling->right->is_black = true;
						}
						temp = extra_black_parent->parent;
						if (temp == nullptr){
							root = rotate_left(extra_black_parent);
							root->parent = nullptr;
						}
						else if(extra_black_parent == temp->left){
							temp->left = rotate_left(extra_black_parent);
							temp->left->parent = temp;
						}
						else{
							temp->right = rotate_left(extra_black_parent);
							temp->right->parent = temp;
						}
					}
					else{
						if(is_node_black(sibling->left)){
							sibling->right->is_black = true;
							sibling->is_black = false;
							temp = sibling->parent;
							temp->left = rotate_left(sibling);
							temp->left->parent = temp;
							sibling = sibling->parent;
						}
						sibling->is_black = extra_black_parent->is_black;
						extra_black_parent->is_black = true;
						if(sibling->left != nullptr){
							sibling->left->is_black = true;
						}
						temp = extra_black_parent->parent;
						if (temp == nullptr){
							root = rotate_right(extra_black_parent);
							root->parent = nullptr;
						}
						else if(extra_black_parent == temp->left){
							temp->left = rotate_right(extra_black_parent);
							temp->left->parent = temp;
						}
						else{
							temp->right = rotate_right(extra_black_parent);
							temp->right->parent = temp;
						}
					}
					extra_black_node = root;
				}
				else{
					extra_black_node = extra_black_parent;
				}
			}
		}
		extra_black_node->is_black = true;
	}
}

template <typename T>
BSTNode<T> * BlackRedTree<T>::search(BSTNode<T> *node, const T& item) const {
    if (node == nullptr || node->value == item) {
        return node;
    } else if (item < node->value) {
        return search(node->left, item);
    } else {
        return search(node->right, item);
    }
}

template <typename T>
BSTNode<T> * BlackRedTree<T>::rotate_right(BSTNode<T> *node) {
    if (node->left == nullptr)
        return node;
    BSTNode<T> *top = node;
    node = top->left;
    top->left = node->right;
    if( top->left != nullptr){
    	top->left->parent = top;
    }
    node->right = top;
    if( node->right != nullptr){
    	node->right->parent = node;
    }
    return node;
}

template <typename T>
BSTNode<T> * BlackRedTree<T>::rotate_left(BSTNode<T> *node) {
    if (node->right == nullptr)
        return node;
    BSTNode<T> *top = node;
    node = top->right;
    top->right = node->left;
    if(top->right != nullptr){
    	top->right->parent = top;
    }
    node->left = top;
    if(node->left != nullptr){
    	node->left->parent = node;
    }
    return node;
}

template <typename T>
void BlackRedTree<T>::display(BSTNode<T> *node, int level) {
    if (node == nullptr) return;
    display(node->right, level + 1);
    for (int i = 0; i < level; i++) {
        std::cout << "   |";
    }
    if (is_node_black(node)){
    	std::cout << "---" << node->value << "B" << std::endl;
	}
    else{
    	std::cout << "---" << node->value << "C" << std::endl;
    }
    display(node->left, level + 1);
}

template <typename T>
void BlackRedTree<T>::preorder(BSTNode<T> *node) {
	if (node == nullptr) return;
	std::cout << node->value << " ";
	preorder(node->left);
	preorder(node->right);
}

template <typename T>
void BlackRedTree<T>::inorder(BSTNode<T> *node) {
	if (node == nullptr) return;
	inorder(node->left);
	std::cout << node->value << " ";
	inorder(node->right);
}

template <typename T>
void BlackRedTree<T>::postorder(BSTNode<T> *node) {
	if (node == nullptr) return;
	postorder(node->left);
	postorder(node->right);
	std::cout << node->value << " ";
}

template <typename T>
void BlackRedTree<T>::bfs() {
	if (root == nullptr) return;
	std::queue<BSTNode<T>*> q;
	q.push(root);
	while (!q.empty()) {
		BSTNode<T>* node = q.front();
		q.pop();
		std::cout << node->value << " ";
		if (node->left != nullptr) q.push(node->left);
		if (node->right != nullptr) q.push(node->right);
	}
}

template <typename T>
T* BlackRedTree<T>::find_min() const {
	if (root == nullptr) return nullptr;
	BSTNode<T>* current = root;
	while (current->left != nullptr) {
		current = current->left;
	}
	return &(current->value);
}

template <typename T>
T* BlackRedTree<T>::find_max() const {
	if (root == nullptr) return nullptr;
	BSTNode<T>* current = root;
	while (current->right != nullptr) {
		current = current->right;
	}
	return &(current->value);
}

template <typename T>
bool BlackRedTree<T>::is_black_red_tree() const {
	if (root == nullptr) return true;
	if (!root->is_black) return false;
	std::queue<std::pair<BSTNode<T>*, int>> q;
	q.push({root, 0});
	int black_count = -1;
	BSTNode<T>* node = nullptr;
	int count = 0;
	while (!q.empty()) {
		node = q.front().first;
		count = q.front().second;
		q.pop();
		if (is_node_black(node)) {
			count++;
		} else {
			if (!is_node_black(node->left)) return false;
			if (!is_node_black(node->right)) return false;
		}
		if (node->left == nullptr && node->right == nullptr) {
			if (black_count == -1) {
				black_count = count;
			} else if (count != black_count) {
				return false;
			}
		}
		if (node->left != nullptr) q.push({node->left, count});
		if (node->right != nullptr) q.push({node->right, count});
	}
	return true;
}

#endif