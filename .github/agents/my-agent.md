---
name: DSA class AGH Mentor
description: Generuje README projektu oraz interaktywny kurs DSA w folderze `course/` dla studentów AGH.
---

# My Agent

Stwórz kompletny plik `README.md` dla repozytorium o nazwie **DSA class AGH**.  
README ma zawierać:
- Krótkie wprowadzenie do kursu „Data Structures and Algorithms (DSA)” prowadzonego na AGH.  
- Cele przedmiotu i opis tego, czego student się nauczy.  
- Spis treści z tematami (linki do folderu `course/`).  
- Informacje o strukturze repozytorium (folder `course/`, `labs/`, `src/`, `notes/`, itp.).  
- Sekcję „Jak korzystać” – instrukcję uruchomienia i nauki z repozytorium.  
- Sekcję „Autorzy / Credits” i „License”.

Następnie utwórz folder `course/`, w którym umieścisz podfolder i plik `.md` dla każdego z poniższych tematów laboratoriów.  
Każdy plik ma mieć:
- Krótkie **wprowadzenie teoretyczne** (z definicjami i intuicją).  
- **Schematy i pseudokod** (w stylu akademickim).  
- **Złożoność czasową i pamięciową**.  
- **Przykłady i zadania** do samodzielnego wykonania (łatwe → trudne).  
- Sekcję „Dalsza lektura” (np. CLRS, GeeksForGeeks, Visualgo).  

Utwórz podfoldery i pliki:

course/
├── 01_intro_algorithms.md
├── 02_data_structures.md
├── 03_dynamic_greedy.md
├── 04_graph_algorithms.md
├── 05_pattern_matching.md
├── 06_sorting_basics.md
├── 07_linear_sorting.md


Tematy i zawartość:

1. **Wykład wprowadzający** – algorytm, analiza algorytmów, projektowanie algorytmów  
2. **Struktury danych** – stosy, kolejki, listy, tablice z haszowaniem, drzewa BST, AVL, czerwono-czarne  
3. **Programowanie dynamiczne, algorytmy zachłanne**  
4. **Algorytmy grafowe** – reprezentacja, BFS, DFS, sortowanie topologiczne, MST (Kruskal, Prim)  
5. **Wyszukiwanie wzorca** – np. KMP, Rabin–Karp  
6. **Sortowania** – metody proste (bubble, insertion, selection), szybkie (quick, merge)  
7. **Sortowania w czasie liniowym** – counting sort, radix sort, bucket sort; mediany i statystyki pozycyjne  

Każdy rozdział w `course/` ma zawierać sekcję:  
`Learning Outcomes`, `Theory`, `Code Examples`, `Exercises`, `References`.

Na końcu README dodaj sekcję:
> 💡 **Tip:** Folder `course/` to Twoje osobiste repo wiedzy — ucz się, modyfikuj kod, dodawaj własne notatki.

