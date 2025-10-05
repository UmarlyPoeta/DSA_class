#include <iostream>
#include <cmath>

using namespace std;

struct punkt{
    int x;
    int y;
};

double odl(int x1, int y1, int x2, int y2) {
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}


punkt naj_oddalona_stara(int n, int m, char** tab, punkt k) {
	double d = 0;
	double nd = 0;
	punkt odp = { -1, -1 };

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (tab[i][j] == 'k' && (k.x != i || k.y != j)) {
				nd = odl(k.x, k.y, i, j);
				if (nd > d) {
					d = nd;
					odp.x = i;
					odp.y = j;
                }
            }
		}
	}
	return odp;
}




punkt naj_oddalona(int n, int m, char** tab, punkt p) {

    // najw odl czebyszewa p -> koniec
    int maxR = max(max(p.x, n-1 - p.x), max(p.y, m-1 - p.y));

    // pasy otoczen moorea
    for (int r = 1; r <= maxR; r++) {
        for (int dx = -r; dx <= r; dx++) {
            for (int dy = -r; dy <= r; dy++) {
                if (max(abs(dx), abs(dy)) == r) { //odleglosc czebyszewa
                    int x = p.x + dx;
                    int y = p.y + dy;
                    if (x >= 0 && x < n && y >= 0 && y < m) {
                        if (tab[x][y] == 'k')
                            return punkt{x, y};
                    }
                }
            }
        }
    }

    return {-1, -1};
}
int main(){
    int n, m;
    cin >> n >> m;
    char** tab = new char*[n];
    for (int i = 0; i < n; ++i) {
        tab[i] = new char[m];
        for (int j = 0; j < m; ++j) {
            cin >> tab[i][j];
        }q
    }
    punkt p;
    cin >> p.x >> p.y;

    punkt odp = naj_oddalona(n, m, tab, p);

    return 0;
}

// testy napisane przez czata sa w pliku 01/test_zadanie_1_optym.cpp

