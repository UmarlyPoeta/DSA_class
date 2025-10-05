#include <map>
#include <iostream>
#include <vector>

using namespace std;

char najSasiedow(int n, int m, vector<vector<char>>& tab, int k, vector<char>& col) {
    map<char, int> color_neighbors;

    for (char color : col) color_neighbors[color] = 0;

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char c = tab[i][j];
            for (int d = 0; d < 4; ++d) {
                int ni = i + dx[d], nj = j + dy[d];
                if (ni >= 0 && ni < n && nj >= 0 && nj < m && tab[ni][nj] == c) {
                    color_neighbors[c]++;
                }
            }
        }
    }

    char best_color = col[0];
    int max_neighbors = color_neighbors[best_color];
    for (char color : col) {
        if (color_neighbors[color] > max_neighbors) {
            max_neighbors = color_neighbors[color];
            best_color = color;
        }
    }
    return best_color;
}
