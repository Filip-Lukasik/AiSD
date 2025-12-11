#ifndef BINSEARCHTREE
#define BINSEARCHTREE

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
// Szablon dla binarnego drzewa poszukiwań.
template <typename T>
class BinarySearchTree {
    BSTNode<T> *root;
public:
    BinarySearchTree() : root(nullptr) {} // konstruktor domyślny
    ~BinarySearchTree() { delete root; } // trzeba wyczyścić
    void clear() { delete root; root = nullptr; }
    bool empty() const { return root == nullptr; }
    T& top() { assert(root != nullptr); return root->value; } // podgląd korzenia
    void insert(const T& item) { root = insert(root, item); }
    void remove(const T& item); // usuwanie przez złączanie
    // Szukając element dostajemy wskaźnik do elementu lub nullptr.
    T* search(const T& item) const {
        auto ptr = search(root, item);
        return ((ptr == nullptr) ? nullptr : &(ptr->value));
    }
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
    void iter_preorder();
    void iter_inorder(); // trudne
    void iter_postorder(); // trudne
    void bfs(); // przejście poziomami (wszerz)
    void display() { display(root, 0); }
    void DSW() { vine_to_tree(tree_to_vine()); }
    int tree_to_vine();
    void vine_to_tree(int size);
    void compress(int count);

    // Metody bezpośrednio odwołujące się do node.
    // Mogą działać na poddrzewie.
    BSTNode<T> * insert(BSTNode<T> *node, const T& item); // zwraca nowy korzeń
    BSTNode<T> * search(BSTNode<T> *node, const T& item) const; // zwraca węzeł
    BSTNode<T> * remove(BSTNode<T> *node); // zwraca nowy korzeń poddrzewa
    BSTNode<T> * rotate_right(BSTNode<T> *node); // zwraca nowy korzeń poddrzewa
    BSTNode<T> * rotate_left(BSTNode<T> *node); // zwraca nowy korzeń poddrzewa
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
BSTNode<T> * BinarySearchTree<T>::insert(BSTNode<T> *node, const T& item) {
    if (node == nullptr) {
        return new BSTNode<T>(item);
    }
    if (item < node->value) {
        node->left = insert(node->left, item);
    } else {
        node->right = insert(node->right, item);
    }
    return node; // zwraca nowy korzeń
}

template <typename T>
BSTNode<T> * BinarySearchTree<T>::search(BSTNode<T> *node, const T& item) const {
    if (node == nullptr || node->value == item) {
        return node;
    } else if (item < node->value) {
        return search(node->left, item);
    } else {
        return search(node->right, item);
    }
}

template <typename T>
BSTNode<T> * BinarySearchTree<T>::rotate_right(BSTNode<T> *node) {
    if (node->left == nullptr)
        return node; // bez zmian
    BSTNode<T> *top = node; // węzeł X
    node = top->left; // węzeł Y
    top->left = node->right; // przepinamy węzeł B
    node->right = top; // przepinamy węzeł X
    return node; // zwracamy węzeł Y
}

template <typename T>
BSTNode<T> * BinarySearchTree<T>::rotate_left(BSTNode<T> *node) {
    if (node->right == nullptr)
        return node; // bez zmian
    BSTNode<T> *top = node; // węzeł Y
    node = top->right; // węzeł X
    top->right = node->left; // przepinamy węzeł B
    node->left = top; // przepinamy węzeł Y
    return node; // zwracamy węzeł X
}
template <typename T>
void BinarySearchTree<T>::display(BSTNode<T> *node, int level) {
    if (node == nullptr) return;
    display(node->right, level + 1);
    for (int i = 0; i < level; i++) {
        std::cout << "   |";
    }
    std::cout << "---" << node->value << std::endl;
    display(node->left, level + 1);
}

template <typename T>
void BinarySearchTree<T>::remove(const T& item) { // usuwanie przez złączanie
    // Najpierw znajdujemy węzeł i jego rodzica.
    BSTNode<T> *node = root;
    BSTNode<T> *prev = nullptr;
    while (node != nullptr) {
        if (node->value == item)
            break;
        prev = node;
        if (item < node->value) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    // Szukamy przyczyny przerwania pętli while.
    if (node != nullptr && node->value == item) {
        // node ma być usunięty.
        if (node == root) {
            root = remove(node);
        } else if (prev->left == node) {
            prev->left = remove(node);
        } else {
            prev->right = remove(node);
        }
    } else if (root != nullptr) {
        ; // klucza nie znaleziono
    } else { // root == nullptr
        ; // drzewo jest puste
    }
}

template <typename T>
BSTNode<T> * BinarySearchTree<T>::remove(BSTNode<T> *node) {
    // Mamy usunąć węzeł i zwrócić nowy korzeń poddrzewa.
    assert(node != nullptr);
    BSTNode<T> *new_root;
    if (node->right == nullptr) { // node nie ma prawego dziecka
        new_root = node->left;
    } else if (node->left == nullptr) { // node nie ma lewego dziecka
        new_root = node->right;
    } else { // obecne lewe i prawe dziecko
        new_root = node; // zapisujemy stary korzeń
        node = node->left; // idziemy w lewo
        while (node->right != nullptr) { // idziemy w prawo do końca
            node = node->right;
        }
        node->right = new_root->right; // prawe poddrzewo przełączone
        node = new_root; // węzeł do usunięcia
        new_root = node->left; // nowy korzeń
    }
    delete node;
    return new_root;
}
template <typename T>
int BinarySearchTree<T>::tree_to_vine() {
	if(root == nullptr) { return 0; }
	BSTNode<T> * cur;
	int size = 1;
	while(root->left != nullptr){
		root = rotate_right(root);
	}
	cur = root;
	while(cur->right != nullptr){
		if(cur->right->left == nullptr){
			cur = cur->right;
			size++;
		}
		else {
			cur->right = rotate_right(cur->right);
		}
	}
	return size;
}
template <typename T>
void BinarySearchTree<T>::vine_to_tree(int size) {
	int leaves = size + 1;	//1. leaves = size + 1 - 2^(|_lg(size+1)_|)
	int i = 0;				//2. size = size - leaves
	while(leaves>>i != 1){	//-2^(|_lg(size+1)_|) to tak naprawde odjęcie najbradzie znaczącego bitu z (size + 1)
		i++;				//zatem zapisujemy do leaves = size + 1
	}						//przesuwamy w prawo (bitowo) aż znajdziemy pozycje najbardziej znaczącego bitu
	size = (1<<i);			//zapisujemy 2^(|_lg(size+1)_|) do size
	leaves -= size;			//odejmując od leaves size odejmujemy 2^(|_lg(size+1)_|) zatem pierwszy linijka komentarza wykonana
	size--;					//size ma być równy size - leaves czyli po podstawieniu za leaves wychodzi size = -1 + 2^(|_lg(size+1)_|)
	compress(leaves);		//size jest obecnie równy 2^(|_lg(size+1)_|) zatem wystarczy odjąć 1 i druga linijka komentarza wykonana
	while (size > 1) {
		size = size/2;
		compress(size);
	}
}
template <typename T>
void BinarySearchTree<T>::compress(int count){
	if(count == 0) { return; }
	root = rotate_left(root);	
	count--;	
	BSTNode<T> * cur = root;
	while(count){
		count--;
		cur->right = rotate_left(cur->right);
		cur = cur->right;
	}
}

#endif
