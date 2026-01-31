#include <bits/stdc++.h>

using namespace std;

const int N = 1005;
const int M = 2005;

int head[N], to[M], nxt[M], ecnt = 0;
int dist[N], par[N];
int q[N];
void add(int u, int v) {
    to[ecnt] = v;
    nxt[ecnt] = head[u];
    head[u] = ecnt++;
}


void inp_node_connect(int n, int m) {
    int u, v;


    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }
}

void print_dist(int n) {
    for (int i = 1; i <= n; i++) {
        cout << dist[i];
        if (i < n) cout << " ";
    }
    cout << "\n";
}

void min_graph(int n, int m) {
    for (int i = 1; i <= n; i++)
        head[i] = dist[i] = par[i] = -1;

    inp_node_connect(n, m);

    int s;
    cin >> s;

    int l = 0, r = 0;
    dist[s] = 0;
    q[r++] = s;

    while (l < r) {
        int u = q[l++];
        for (int e = head[u]; e != -1; e = nxt[e]) {
            int v = to[e];
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                par[v] = u;
                q[r++] = v;
            }
        }
    }

    print_dist(n);

    int qn;
    cin >> qn;
    while (qn--) {
        int t;
        cin >> t;

        cout << "dist(s,t) = " << dist[t] << "\n";
        cout << "path: ";

        if (dist[t] == -1) {
            cout << "nie ma dasdsdsd\n";


        } else {
            int p[N], k = 0;

            while (t != -1) {
                p[k++] = t;
                t = par[t];
            }
            for (int i = k - 1; i >= 0; i--) {
                cout << p[i];
                if (i) cout << " -> ";
            }
            cout << "\n";
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    min_graph(n, m);
}
