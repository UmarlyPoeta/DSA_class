#include <iostream>
#include <vector>
#include <map>

using namespace std;

// Funkcję najSasiedow napisz sam
char najSasiedow(int n, int m, vector<vector<char>>& tab, int k, vector<char>& col) {
    map <char, pair<int, int>> colors;
    for (char color : col) {
        
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
