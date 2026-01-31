#include <bits/stdc++.h>

const int MAX_VERTICES = 1005;
const int MAX_EDGES = 2005;

int firstEdge[MAX_VERTICES];   
int edgeTo[MAX_EDGES];         
int nextEdge[MAX_EDGES];       
int edgeCount = 0;


void addEdge(int from, int toVertex) {
    edgeTo[edgeCount] = toVertex;
    nextEdge[edgeCount] = firstEdge[from];
    firstEdge[from] = edgeCount;
    edgeCount++;
}


int main() {
    int n, m;
    std::cin >> n >> m;

    for (int i = 1; i <= n;i++) {
        firstEdge[i] = -1;
    }

    for (int i =0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }

    int s;
    std::cin >> s;

    
}
