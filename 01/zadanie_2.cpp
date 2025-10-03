#include <iostream>
#include <vector>
#include <map>

using namespace std;

// Funkcję najSasiedow napisz sam
char najSasiedow(int n, int m, vector<vector<char>>& tab, int k, vector<char>& col) {
    map<char, int> colors;
    for (int i = 0; i < k; i++) {
        colors[col[i]] = 0;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (tab[i][j] != '.') {
                for (int di = -1; di <= 1; di++) {
                    for (int dj = -1; dj <= 1; dj++) {
                        if (di == 0 && dj == 0) continue;
                        int ni = i + di;
                        int nj = j + dj;
                        if (ni >= 0 && ni < n && nj >= 0 && nj < m) {
                            if (colors.find(tab[ni][nj]) != colors.end()) {
                                colors[tab[ni][nj]]++;
                            }
                        }
                    }
                }
            }
        }
    }

}

int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<char>> tab(n, vector<char>(m));
    int k;
    cin >> k;
    vector<char> colors(k);

    for (int i = 0; i < k; i++)
    {
        cin >> colors[i];
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> tab[i][j];

    char wynik = najSasiedow(n, m, tab, k, colors);
    cout << wynik << endl;

    return 0;
}
