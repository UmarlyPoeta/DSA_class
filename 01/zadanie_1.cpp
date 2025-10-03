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




punkt naj_oddalona(int n, int m, char tab[][100], punkt k) {
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


int main() {
	int n, m;
	cin >> n >> m;
	char tab[n][m];

	for (int i = 0; i < n; i++)
	    for (int j = 0; j < m; j++)
	        cin >> tab[i][j];

	return 0;
}
