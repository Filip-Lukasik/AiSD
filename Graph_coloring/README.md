# Dokumentacja implementacji algorytmu kolorowania wierzchołków grafu

## 1. Cel implementacji

Projekt realizuje kolorowanie wierzchołków grafu za pomocą algorytmu zachłannego LF (Largest First).
Algorytm najpierw ustala kolejność przetwarzania wierzchołków według ich stopnia, a następnie przypisuje każdemu wierzchołkowi najmniejszy możliwy kolor, który nie jest używany przez jego sąsiadów.

## 2. Główne komponenty projektu

- [graph.h](graph.h) – reprezentacja grafu w postaci listy sąsiedztwa wraz z iteratorami.
- [graphnodecoloring.h](graphnodecoloring.h) – klasa odpowiedzialna za ustalenie kolejności i przypisanie kolorów.
- [main.cpp](main.cpp) – przykładowe uruchomienie algorytmu na grafie losowym.

## 3. Zasada działania algorytmu LF

Algorytm działa w dwóch etapach:

1. Ustalenie kolejności przetwarzania wierzchołków.
   - Dla każdego wierzchołka obliczany jest jego stopień.
   - Wierzchołki są porządkowane tak, aby najpierw przetwarzać te o największym stopniu.
   - W implementacji do tego celu wykorzystano wariant sortowania przez zliczanie.

2. Kolorowanie wierzchołków.
   - Wierzchołki są przetwarzane w ustalonej kolejności od końca tablicy `order`.
   - Dla każdego wierzchołka sprawdzane są kolory jego sąsiadów, które są już pokolorowane.
   - Przydzielany jest najmniejszy kolor, który nie występuje wśród kolorów sąsiadów.

## 4. Jak działa sortowanie przez zliczanie w tej implementacji

W klasie `GraphNodeColoring` przechowywana jest tablica `degree`, która liczy, ile wierzchołków ma dany stopień.
Na podstawie tych zliczeń tworzona jest kolejność wierzchołków:

- najpierw rozkładamy wierzchołki według stopnia,
- następnie umieszczamy je w tablicy `order` w odpowiednich pozycjach,
- na końcu otrzymujemy uporządkowaną listę, w której wierzchołki o większych stopniach są umieszczone bliżej końca tej tablicy.

Dzięki temu podczas iteracji od końca tablicy `order` algorytm najpierw przetwarza wierzchołki o największych stopniach, zgodnie z heurystyką LF.

## 5. Szczegóły implementacji

### 5.1. Struktura danych

- `order` – wektor przechowujący kolejność przetwarzania wierzchołków.
- `degree` – wektor z licznikami stopni wierzchołków.
- `nodeColors` – mapa przypisująca każdemu wierzchołkowi numer koloru.

### 5.2. Konstruktor klasy `GraphNodeColoring`

W konstruktorze:

- inicjalizowane są tablice `order` i `degree`,
- dla każdego wierzchołka ustawiany jest początkowy kolor `-1`, co oznacza, że wierzchołek nie jest jeszcze pokolorowany,
- obliczane są stopnie węzłów,
- na podstawie zliczeń tworzona jest kolejność kolorowania.

### 5.3. Metoda `run()`

Metoda `run()` realizuje właściwe kolorowanie:

1. Przejście po wierzchołkach z tablicy `order` od końca.
2. Dla aktualnego wierzchołka zbadanie kolorów jego sąsiadów.
3. Wybór najmniejszego koloru wolnego.
4. Przypisanie tego koloru do wierzchołka.

## 6. Złożoność obliczeniowa

Dla grafu z `V` wierzchołkami i `E` krawędziami:

- ustalenie kolejności: `O(V + E)` w praktyce, ze względu na liniowe przeglądanie stopni i wierzchołków,
- kolorowanie wierzchołków: `O(V + E)`, ponieważ każdy wierzchołek jest sprawdzany raz, a jego sąsiedzi są przeglądani tylko raz,
- pamięć: `O(V + E)`.

## 7. Uwagi praktyczne

- Algorytm jest zachłanny, więc nie gwarantuje minimalnej liczby kolorów.
- Działa poprawnie dla grafu nieskierowanego, który jest używany w tym projekcie.
- W praktyce daje dobre wyniki dla wielu grafów, zwłaszcza gdy wierzchołki o dużych stopniach są kolorowane wcześniej.

## 8. Przykład użycia

Program w [main.cpp](main.cpp) tworzy dwa przykładowe grafy losowe, koloruje je i wypisuje przypisane kolory dla każdego wierzchołka.
