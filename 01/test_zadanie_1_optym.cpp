#include <iostream>
#include <chrono>
#include <cassert>
#include <vector>
#include <cstring>
#include "zadanie_1_optym.cpp" // Zakładamy, że funkcje są w tym pliku

using namespace std;

// Pomocnicza funkcja do tworzenia tablicy
char** make_tab(const vector<string>& rows) {
    int n = rows.size();
    int m = rows[0].size();
    char** tab = new char*[n];
    for (int i = 0; i < n; ++i) {
        tab[i] = new char[m];
        memcpy(tab[i], rows[i].c_str(), m);
    }
    return tab;
}

// Pomocnicza funkcja do zwalniania pamięci
void free_tab(char** tab, int n) {
    for (int i = 0; i < n; ++i) delete[] tab[i];
    delete[] tab;
}

// Prosty test dla obu wersji funkcji
void test_simple() {
    vector<string> rows = {
        "....",
        ".k..",
        "..k.",
        "...."
    };
    char** tab = make_tab(rows);
    punkt p = {1, 1}; // pozycja pierwszego 'k'
    punkt res1 = naj_oddalona(4, 4, tab, p); // nowa wersja
    punkt res2 = naj_oddalona_stara(4, 4, tab, p); // stara wersja (oba mają tę samą sygnaturę)
    assert((res1.x == 2 && res1.y == 2) || (res1.x == 1 && res1.y == 1)); // drugi 'k'
    assert(res1.x == res2.x && res1.y == res2.y);
    free_tab(tab, 4);
    cout << "test_simple passed\n";
}

// Test wydajności i pamięci
void test_performance() {
    int n = 500, m = 500;
    vector<string> rows(n, string(m, '.'));
    rows[0][0] = 'k';
    rows[n-1][m-1] = 'k';
    char** tab = make_tab(rows);
    punkt p = {0, 0};

    auto start = chrono::high_resolution_clock::now();
    punkt res1 = naj_oddalona(n, m, tab, p); // nowa wersja
    auto end = chrono::high_resolution_clock::now();
    auto time1 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::high_resolution_clock::now();
    punkt res2 = naj_oddalona_stara(n, m, tab, p); // stara wersja
    end = chrono::high_resolution_clock::now();
    auto time2 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "Nowa wersja czas: " << time1 << "us\n";
    cout << "Stara wersja czas: " << time2 << "us\n";
    assert(res1.x == n-1 && res1.y == m-1);
    assert(res2.x == n-1 && res2.y == m-1);
    free_tab(tab, n);
    cout << "test_performance passed\n";
}

int main() {
    test_simple();
    test_performance();
    cout << "All tests passed!\n";
    return 0;
}