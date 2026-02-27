# Dokumentacja Implementacji Drzewa Czerwono-Czarnego

## Ogólny opis

Implementacja generycznego szablonowego drzewa czerwono-czarnego (Red-Black Tree) w C++ bez użycia wartownika. Drzewo utrzymuje równowagę poprzez kolorowanie węzłów na czarno i czerwono, co gwarantuje, że wysokość drzewa pozostaje O(log n).

## Struktura węzła (`BSTNode<T>`)

```cpp
template <typename T>
struct BSTNode {
    T value;              // Wartość przechowywana w węźle
    bool is_black;        // true = czarny, false = czerwony
    BSTNode *left;        // Wskaźnik do lewego dziecka
    BSTNode *right;       // Wskaźnik do prawego dziecka
    BSTNode *parent;      // Wskaźnik do rodzica
};
```

## Główna klasa (`BlackRedTree<T>`)

### Konstruktory i destruktory
- `BlackRedTree()` - inicjalizacja pustego drzewa
- `~BlackRedTree()` - destruktor, zwalnia całe drzewo

---

## Publiczne metody

### Zarządzanie drzewem

#### `void clear()`
Czyści drzewo, usuwając wszystkie węzły.
```cpp
tree.clear();  // Drzewo jest teraz puste
```

#### `bool empty() const`
Zwraca `true`, jeśli drzewo jest puste, w przeciwnym razie `false`.
```cpp
if (tree.empty()) {
    std::cout << "Drzewo jest puste" << std::endl;
}
```

#### `T& top()`
Zwraca referencję do wartości w węźle root. Zakłada, że drzewo nie jest puste.
```cpp
int max = tree.top();  // Wartość w korzeniu
```

---

### Operacje wstawiania i usuwania

#### `void insert(const T& item)`
Wstawia nową wartość do drzewa, zachowując własności drzewa czerwono-czarnego.

**Algorytm:**
1. Wstaw element jak w zwykłym BST
2. Nowy węzeł jest kolorowany na czerwono
3. Jeśli korzeń jest czerwony, zmień go na czarny
4. Wykonaj naprawy (rotacje i przekolorowania), aż do przywrócenia własności RBT

```cpp
tree.insert(10);
tree.insert(5);
tree.insert(15);
```

#### `void remove(const T& item)`
Usuwa wartość z drzewa, zachowując własności RBT.

**Algorytm:**
1. Znajdź węzeł do usunięcia
2. Obsługuje 3 przypadki:
   - Węzeł liściowy (bez dzieci)
   - Węzeł z jednym dzieckiem
   - Węzeł z dwoma dziećmi (zastąp następnikiem)
3. Jeśli usunięty węzeł był czarny, wykonaj naprawy

```cpp
tree.remove(10);
```

---

### Wyszukiwanie

#### `BSTNode<T>* search(const T& item) const`
Wyszukuje węzeł zawierający daną wartość. Zwraca wskaźnik do węzła lub `nullptr`.

```cpp
BSTNode<int>* found = tree.search(10);
if (found != nullptr) {
    std::cout << "Znaleziono: " << found->value << std::endl;
}
```

#### `T* iter_search(const T& item) const`
Iteracyjna wersja wyszukiwania (szybsza, bez rekursji).

```cpp
int* ptr = tree.iter_search(10);
if (ptr != nullptr) {
    std::cout << "Wartość: " << *ptr << std::endl;
}
```

#### `T* find_min() const`
Zwraca wskaźnik do najmniejszej wartości (lewy koniec drzewa).

```cpp
int* min = tree.find_min();
if (min != nullptr) {
    std::cout << "Minimum: " << *min << std::endl;
}
```

#### `T* find_max() const`
Zwraca wskaźnik do największej wartości (prawy koniec drzewa).

```cpp
int* max = tree.find_max();
if (max != nullptr) {
    std::cout << "Maksimum: " << *max << std::endl;
}
```

---

### Walidacja

#### `bool is_black_red_tree() const`
Sprawdza, czy drzewo spełnia wszystkie własności drzewa czerwono-czarnego:
1. Korzeń jest czarny
2. Nie ma dwóch kolejnych węzłów czerwonych (Red Property)
3. Każda ścieżka od korzenia do liścia ma taką samą liczbę węzłów czarnych (Black Height)

```cpp
if (tree.is_black_red_tree()) {
    std::cout << "Drzewo jest poprawnym RBT" << std::endl;
}
```

---

### Przechodzenie drzewa

#### `void preorder()`
Przechodzenie w porządku root-lewo-prawo (Pre-order traversal).

```cpp
tree.preorder();  // Wypisuje: wartość root, lewa poddrzewo, prawa poddrzewo
```

#### `void inorder()`
Przechodzenie w porządku lewo-root-prawo (In-order traversal). Wypisuje wartości w porządku rosnącym.

```cpp
tree.inorder();   // Wypisuje wartości od najmniejszej do największej
```

#### `void postorder()`
Przechodzenie w porządku lewo-prawo-root (Post-order traversal).

```cpp
tree.postorder(); // Wypisuje: lewa poddrzewo, prawa poddrzewo, wartość root
```

#### `void bfs()`
Przechodzenie wszerz (Breadth-First Search) wykorzystując kolejkę.

```cpp
tree.bfs();       // Wypisuje wartości poziomo: root, jego dzieci, ich dzieci, ...
```

---

### Wizualizacja

#### `void display()`
Wyświetla drzewo w formatzie tekstowym, pokazując strukturę hierarchiczną.
- `C` oznacza węzeł czerwony (Red)
- `B` oznacza węzeł czarny (Black)

```cpp
tree.display();
// Przykładowe wyjście:
//    |---15B
// ---10C
//    |---5B
```

---

## Metody prywatne (implementacja wewnętrzna)

### Rotacje

#### `BSTNode<T>* rotate_right(BSTNode<T> *node)`
Obrót w prawo - przywraca równowagę drzewa. Lewe dziecko staje się nowym korzeniem poddrzewa.

#### `BSTNode<T>* rotate_left(BSTNode<T> *node)`
Obrót w lewo - przywraca równowagę drzewa. Prawe dziecko staje się nowym korzeniem poddrzewa.

### Pomocnicze metody
- `bool is_node_black(BSTNode<T> *node)` - sprawdza czy węzeł jest czarny (nullptr traktuje jako czarny)
- `BSTNode<T>* insert(...)` - wstawianie rekurencyjne
- `void preorder/inorder/postorder(BSTNode<T> *)` - przechodzenia rekurencyjne
- `void display(BSTNode<T> *, int)` - wyświetlanie rekurencyjne

---

## Własności drzewa czerwono-czarnego

1. **Każdy węzeł jest czerwony lub czarny**
2. **Korzeń jest czarny**
3. **Liście (nullptr) są czarne**
4. **Węzły czerwone mają tylko czarne dzieci** (Red Property)
5. **Wszystkie ścieżki od węzła do jego liści zawierają taką samą liczbę węzłów czarnych** (Black Height)

Te właściwości gwarantują, że drzewo pozostaje zbalansowane:
- Wysokość drzewa: **O(log n)**
- Operacje (insert, remove, search): **O(log n)**

---

## Złożoność czasowa

| Operacja | Złożoność |
|----------|-----------|
| `insert()` | O(log n) |
| `remove()` | O(log n) |
| `search()` | O(log n) |
| `find_min()` / `find_max()` | O(log n) |
| `inorder()` / `preorder()` / `postorder()` / `bfs()` | O(n) |
| `is_black_red_tree()` | O(n) |

---

## Przykład użycia

```cpp
#include "blackredtree.h"

int main() {
    BlackRedTree<int> tree;
    
    // Wstawianie
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    
    // Wyświetlanie
    std::cout << "Drzewo:" << std::endl;
    tree.display();
    
    // Przechodzenia
    std::cout << "In-order: ";
    tree.inorder();
    std::cout << std::endl;
    
    // Wyszukiwanie
    if (tree.search(7) != nullptr) {
        std::cout << "Znaleziono 7" << std::endl;
    }
    
    // Zakresy
    std::cout << "Min: " << *tree.find_min() << std::endl;
    std::cout << "Max: " << *tree.find_max() << std::endl;
    
    // Walidacja
    std::cout << "Valid RBT: " << (tree.is_black_red_tree() ? "Yes" : "No") << std::endl;
    
    // Usuwanie
    tree.remove(5);
    std::cout << "Po usunięciu 5:" << std::endl;
    tree.display();
    
    // Czyszczenie
    tree.clear();
    
    return 0;
}
```

---

## Referencje

- [Wikipedia - Drzewo czerwono-czarne](https://pl.wikipedia.org/wiki/Drzewo_czerwono-czarne)
- [eduinf.waw.pl - Algorytmy wyszukiwania](https://eduinf.waw.pl/inf/alg/001_search/0121.php)

---

## Notatki implementacji

- Drzewo **nie używa wartownika** - null wskaźniki są traktowane jako czarne liście
- Każdy węzeł posiada wskaźnik do rodzica, co ułatwia naprawy po usunięciu
- Template umożliwia pracę z dowolnymi typami danych obsługującymi porównania (`<`, `==`)
- Rotacje i przekolorowania zapewniają utrzymanie O(log n) wysokości drzewa
