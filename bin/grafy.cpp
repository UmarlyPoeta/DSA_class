#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <climits>
#include <functional>
#include <numeric>
using namespace std;

struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

class Graph {
private:
    int vertices;
    vector<vector<pair<int, int>>> adjList; 

public:
    Graph(int v) : vertices(v), adjList(v) {}

    void addEdge(int u, int v, int weight) {
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight});
    }

    void bfs(int start) {
        vector<bool> visited(vertices, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            for (auto [neighbor, weight] : adjList[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }

    void dfs(int start) {
        vector<bool> visited(vertices, false);
        dfsHelper(start, visited);
        cout << endl;
    }

    // z czata
    void dfsHelper(int node, vector<bool>& visited) {
        visited[node] = true;
        cout << node << " ";
        for (auto [neighbor, weight] : adjList[node]) {
            if (!visited[neighbor]) {
                dfsHelper(neighbor, visited);
            }
        }
    }

    void kruskal(vector<Edge>& edges) {
        sort(edges.begin(), edges.end());
        vector<int> parent(vertices);
        iota(parent.begin(), parent.end(), 0);

        function<int(int)> find = [&](int x) {
            return parent[x] == x ? x : parent[x] = find(parent[x]);
        };

        int totalCost = 0;
        cout << "Kruskal's MST:\n";
        for (auto& e : edges) {
            int pu = find(e.u), pv = find(e.v);
            if (pu != pv) {
                parent[pu] = pv;
                cout << e.u << "-" << e.v << ": " << e.weight << endl;
                totalCost += e.weight;
            }
        }
        cout << "Total cost: " << totalCost << endl;
    }

    void prim() {
        vector<bool> inMST(vertices, false);
        vector<int> key(vertices, INT_MAX);
        key[0] = 0;
        int totalCost = 0;

        cout << "Prim's MST:\n";
        for (int count = 0; count < vertices; count++) {
            int u = -1;
            for (int v = 0; v < vertices; v++) {
                if (!inMST[v] && (u == -1 || key[v] < key[u])) {
                    u = v;
                }
            }
            inMST[u] = true;

            for (auto [v, weight] : adjList[u]) {
                if (!inMST[v] && weight < key[v]) {
                    key[v] = weight;
                    if (count > 0) {
                        cout << u << "-" << v << ": " << weight << endl;
                        totalCost += weight;
                    }
                }
            }
        }
        cout << "Total cost: " << totalCost << endl;
    }
};


// z czata testy
int main() {
    cout << "=== Problem 1: Graph Traversals ===\n";
    Graph g1(6);
    g1.addEdge(0, 1, 1);
    g1.addEdge(0, 2, 4);
    g1.addEdge(1, 3, 2);
    g1.addEdge(2, 3, 3);
    g1.bfs(0);
    g1.dfs(0);


    cout << "\n=== Problem 2: Kruskal's MST ===\n";
    vector<Edge> edges2 = {
        {0, 1, 1}, {0, 2, 4}, {1, 3, 2}, {2, 3, 3},
        {2, 4, 1}, {3, 5, 5}, {4, 5, 5}
    };
    Graph g2(6);
    g2.kruskal(edges2);

    cout << "\n=== Problem 3: Prim's MST ===\n";
    Graph g3(6);
    g3.addEdge(0, 1, 6);
    g3.addEdge(0, 2, 1);
    g3.addEdge(0, 3, 5);
    g3.addEdge(1, 2, 5);
    g3.addEdge(1, 4, 3);
    g3.addEdge(2, 3, 5);
    g3.addEdge(2, 4, 6);
    g3.addEdge(2, 5, 4);
    g3.addEdge(3, 5, 2);
    g3.addEdge(4, 5, 6);
    g3.prim();

    return 0;
}