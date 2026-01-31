#include <bits/stdc++.h>

const int M = 1005;
const int N = 2005;

int head[N], to[M], nxt[M], ecount = 0;
int dist[N]; int parent[N];
int que[N];

void add(int from, int toVertex) {
    to[ecount] = toVertex;
    nxt[ecount] = head[from];
    head[from] = ecount++;
}

void add(int u, int v) {
    to[ecount] = v;
    nxt[ecount] = head[u];
    head[u] = ecount++;
}

int main() {
    int n, m;


    for (int i = 1; i < n; i++) {
        head[i] = dist[i] = parent[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int u, v;
        std::cin >> u >> v;
        add(u, v);
        add(v, u);
    }

    int s; std::cin >> s;

    int l = 0; int r = 0;
    dist[s] = 0;
    que[r++] = s;

    while (l < r) {
        int u = que[l++];
        for (int e = head[u]; e != -1; e = nxt[e]) {
            int v = to[e];
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                parent[v] = u;
                que[r++] = v;
            }
        }
    }

    
}