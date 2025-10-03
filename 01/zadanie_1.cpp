#include <iostream>
#include <cmath>


using namespace std;

struct punkt{
	int x;
	int y;
};

double odl(int x1, int y1, int x2, int y2) {
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2);
}


punkt naj_oddalona(int n, int m, char [][]tab, punkt k) {
	double d = 0;
	double nd = 0;
	punkt odp;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (tab[n][m] == 'k' && k.x != n && k.y != m) {
				nd = odl(k.x, k.y, n, m);
				if (nd > d) {
					d = nd;
					odp.x = n;
					odp.y = m;
				}
			}
		}
	}
	return odp;
}


int main() {
	int n, m;
	char tab[n][m];

	
}
