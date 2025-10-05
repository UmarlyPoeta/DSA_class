#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

struct punkt {
    int x;
    int y;
};

punkt punkt_iloczyn(int** tab, int n, int m, int N) {
    vector<punkt> punkty;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if ((i + j) % N) {
                punkty.push_back(punkt{i, j});
            }
        }
    }

    int x, y;
    int w_iloczyn = __INT_MAX__;
    int iloczyn;
    punkt wynik = punkt{-1, -1};

    for (punkt p : punkty) {
        iloczyn = 1;

        for (int r = -1; r <= 1; r++) {
            for (int s = -1; s <= 1; s++) {
                x = p.x + r;
                y = p.y + s;
                if (x >= 0 && x < n && y >= 0 && y < m) {
                    iloczyn *= tab[x][y];
                }
                
            }
        }

        if (iloczyn < w_iloczyn) {
            w_iloczyn = iloczyn;
            wynik = p;
        }
    }

    return wynik;
}


int main(){

    int m, n;
    cin >> m >> n;

    int** tab = new int*[n];

    for (int i = 0; i < n; i++) {
        tab[i] = new int[m];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> tab[i][j];
        }
    }

    int N;
    cin >> N;

    punkt wynik = punkt_iloczyn(tab, n, m, N);

    cout << wynik.x << " " << wynik.y << endl;

    return 0;

}