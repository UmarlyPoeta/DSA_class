# 04. Graph Algorithms

## Learning Outcomes

After completing this module, you will be able to:

- Represent graphs using different data structures
- Implement graph traversal algorithms (BFS, DFS)
- Perform topological sorting on directed acyclic graphs
- Find shortest paths in weighted and unweighted graphs
- Compute minimum spanning trees using Kruskal's and Prim's algorithms
- Detect cycles in graphs
- Analyze time and space complexity of graph algorithms

## Theory

### What is a Graph?

A **graph** G = (V, E) consists of:
- **V**: Set of vertices (nodes)
- **E**: Set of edges (connections between vertices)

### Graph Types

1. **Directed vs Undirected**
   - **Directed (Digraph)**: Edges have direction (A → B)
   - **Undirected**: Edges are bidirectional (A — B)

2. **Weighted vs Unweighted**
   - **Weighted**: Edges have associated weights/costs
   - **Unweighted**: All edges have equal weight

3. **Cyclic vs Acyclic**
   - **Cyclic**: Contains at least one cycle
   - **Acyclic**: No cycles (DAG = Directed Acyclic Graph)

4. **Connected vs Disconnected**
   - **Connected**: Path exists between every pair of vertices
   - **Disconnected**: Some vertices are unreachable

### Graph Terminology

- **Degree**: Number of edges connected to a vertex
  - In-degree: Incoming edges (directed)
  - Out-degree: Outgoing edges (directed)
- **Path**: Sequence of vertices connected by edges
- **Cycle**: Path that starts and ends at the same vertex
- **Connected Component**: Maximal set of connected vertices
- **Spanning Tree**: Subgraph that connects all vertices with minimum edges (V-1 edges)

## Graph Representation

### 1. Adjacency Matrix

2D array where matrix[i][j] = 1 if edge exists from vertex i to j, 0 otherwise.

**Example:**
```
Graph:  0 → 1
        ↓   ↓
        2 → 3

Matrix:
    0  1  2  3
0 [ 0  1  1  0 ]
1 [ 0  0  0  1 ]
2 [ 0  0  0  1 ]
3 [ 0  0  0  0 ]
```

**Properties:**
- **Space**: O(V²)
- **Check edge (u,v)**: O(1)
- **Add/Remove edge**: O(1)
- **Find all neighbors**: O(V)
- **Good for**: Dense graphs

### 2. Adjacency List

Array of lists where list[i] contains all neighbors of vertex i.

**Example:**
```
Graph:  0 → 1
        ↓   ↓
        2 → 3

List:
0 → [1, 2]
1 → [3]
2 → [3]
3 → []
```

**Properties:**
- **Space**: O(V + E)
- **Check edge (u,v)**: O(degree(u))
- **Add edge**: O(1)
- **Find all neighbors**: O(degree(u))
- **Good for**: Sparse graphs

### 3. Edge List

List of all edges as pairs (u, v).

**Example:**
```
Edges: [(0,1), (0,2), (1,3), (2,3)]
```

**Properties:**
- **Space**: O(E)
- **Good for**: Kruskal's algorithm, simple representation

## Graph Traversal Algorithms

### 1. Breadth-First Search (BFS)

**Strategy**: Explore vertices level by level, starting from source.

**Uses**:
- Shortest path in unweighted graphs
- Level-order traversal
- Connected components
- Bipartite graph detection

#### Pseudocode

```
BFS(G, source):
    // Initialize
    for each vertex v in G.V:
        v.color = WHITE
        v.distance = ∞
        v.parent = NIL
    
    source.color = GRAY
    source.distance = 0
    source.parent = NIL
    
    Q = empty queue
    Enqueue(Q, source)
    
    while Q is not empty:
        u = Dequeue(Q)
        
        for each v in G.Adj[u]:
            if v.color == WHITE:
                v.color = GRAY
                v.distance = u.distance + 1
                v.parent = u
                Enqueue(Q, v)
        
        u.color = BLACK
```

**Time Complexity**: O(V + E)  
**Space Complexity**: O(V)

**Colors**:
- WHITE: Undiscovered
- GRAY: Discovered but not fully explored
- BLACK: Fully explored

### 2. Depth-First Search (DFS)

**Strategy**: Explore as deep as possible before backtracking.

**Uses**:
- Cycle detection
- Topological sorting
- Finding strongly connected components
- Path finding
- Maze solving

#### Pseudocode

```
DFS(G):
    for each vertex u in G.V:
        u.color = WHITE
        u.parent = NIL
    
    time = 0
    
    for each vertex u in G.V:
        if u.color == WHITE:
            DFS_Visit(G, u)

DFS_Visit(G, u):
    time = time + 1
    u.discovery = time
    u.color = GRAY
    
    for each v in G.Adj[u]:
        if v.color == WHITE:
            v.parent = u
            DFS_Visit(G, v)
    
    u.color = BLACK
    time = time + 1
    u.finish = time
```

**Time Complexity**: O(V + E)  
**Space Complexity**: O(V)

**Properties**:
- **Discovery time**: When vertex is first discovered
- **Finish time**: When all descendants are explored
- **Parenthesis theorem**: For any vertices u and v, exactly one holds:
  - Intervals [u.d, u.f] and [v.d, v.f] are disjoint
  - One interval is contained in the other

## Topological Sorting

**Definition**: Linear ordering of vertices in a DAG such that for every edge (u, v), u comes before v.

**Applications**:
- Task scheduling
- Course prerequisites
- Build dependencies
- Makefiles

### Algorithm (Using DFS)

```
TopologicalSort(G):
    stack = empty stack
    visited = set()
    
    for each vertex v in G.V:
        if v not in visited:
            TopologicalSortUtil(v, visited, stack)
    
    return stack

TopologicalSortUtil(v, visited, stack):
    visited.add(v)
    
    for each neighbor u of v:
        if u not in visited:
            TopologicalSortUtil(u, visited, stack)
    
    stack.push(v)  // Push after visiting all descendants
```

**Time Complexity**: O(V + E)  
**Space Complexity**: O(V)

**Note**: Topological sort is only possible for DAGs. If graph has a cycle, no topological ordering exists.

### Kahn's Algorithm (BFS-based)

```
TopologicalSort_Kahn(G):
    // Compute in-degree for all vertices
    inDegree = array of size V, initialized to 0
    for each vertex u in G.V:
        for each v in G.Adj[u]:
            inDegree[v]++
    
    // Queue all vertices with in-degree 0
    Q = empty queue
    for each vertex v in G.V:
        if inDegree[v] == 0:
            Enqueue(Q, v)
    
    result = []
    count = 0
    
    while Q is not empty:
        u = Dequeue(Q)
        result.append(u)
        count++
        
        for each v in G.Adj[u]:
            inDegree[v]--
            if inDegree[v] == 0:
                Enqueue(Q, v)
    
    if count != V:
        return "Graph has a cycle"
    
    return result
```

## Minimum Spanning Tree (MST)

**Definition**: A spanning tree of a connected, weighted graph that has minimum total edge weight.

**Properties**:
- Contains V-1 edges
- Connects all vertices
- No cycles
- Minimum total weight

### 1. Kruskal's Algorithm (Greedy)

**Strategy**: Sort edges by weight, add edge if it doesn't create cycle.

**Uses**: Union-Find (Disjoint Set) data structure

```
Kruskal(G):
    MST = empty set
    
    // Create disjoint sets for each vertex
    for each vertex v in G.V:
        MakeSet(v)
    
    // Sort edges by weight (non-decreasing)
    edges = sort(G.E by weight)
    
    for each edge (u, v, weight) in edges:
        if FindSet(u) != FindSet(v):
            MST.add((u, v, weight))
            Union(u, v)
    
    return MST
```

**Time Complexity**: O(E log E) or O(E log V)  
**Space Complexity**: O(V)

### 2. Prim's Algorithm (Greedy)

**Strategy**: Start from arbitrary vertex, grow tree by adding minimum weight edge.

```
Prim(G, source):
    // Initialize
    for each vertex v in G.V:
        v.key = ∞
        v.parent = NIL
    
    source.key = 0
    
    Q = all vertices in G.V  // Min-priority queue by key
    
    while Q is not empty:
        u = ExtractMin(Q)
        
        for each v in G.Adj[u]:
            if v in Q and weight(u,v) < v.key:
                v.parent = u
                v.key = weight(u,v)
                DecreaseKey(Q, v)
```

**Time Complexity**: 
- With binary heap: O(E log V)
- With Fibonacci heap: O(E + V log V)

**Space Complexity**: O(V)

### Kruskal vs Prim

| Feature | Kruskal | Prim |
|---------|---------|------|
| Strategy | Edge-based | Vertex-based |
| Data Structure | Union-Find | Priority Queue |
| Best for | Sparse graphs | Dense graphs |
| Implementation | Simpler | More complex |

## Shortest Path Algorithms

### 1. Single-Source Shortest Path (Unweighted) - BFS

For unweighted graphs, BFS finds shortest paths from source to all vertices.

**Time Complexity**: O(V + E)

### 2. Dijkstra's Algorithm (Non-negative weights)

**Strategy**: Greedy - always expand closest vertex.

```
Dijkstra(G, source):
    // Initialize
    for each vertex v in G.V:
        v.distance = ∞
        v.parent = NIL
    
    source.distance = 0
    
    Q = all vertices in G.V  // Min-priority queue by distance
    
    while Q is not empty:
        u = ExtractMin(Q)
        
        for each v in G.Adj[u]:
            // Relaxation
            if v.distance > u.distance + weight(u,v):
                v.distance = u.distance + weight(u,v)
                v.parent = u
                DecreaseKey(Q, v)
```

**Time Complexity**: O((V + E) log V) with binary heap  
**Space Complexity**: O(V)

**Note**: Does NOT work with negative edge weights!

### 3. Bellman-Ford Algorithm (Allows negative weights)

**Strategy**: Relax all edges V-1 times.

```
BellmanFord(G, source):
    // Initialize
    for each vertex v in G.V:
        v.distance = ∞
        v.parent = NIL
    
    source.distance = 0
    
    // Relax edges V-1 times
    for i = 1 to |V| - 1:
        for each edge (u, v) in G.E:
            if v.distance > u.distance + weight(u,v):
                v.distance = u.distance + weight(u,v)
                v.parent = u
    
    // Check for negative cycles
    for each edge (u, v) in G.E:
        if v.distance > u.distance + weight(u,v):
            return "Negative cycle detected"
    
    return distances
```

**Time Complexity**: O(VE)  
**Space Complexity**: O(V)

**Advantage**: Detects negative cycles

## Code Examples

### BFS Implementation (C++)

```cpp
#include <iostream>
#include <vector>
#include <queue>

void BFS(const std::vector<std::vector<int>>& graph, int source) {
    int n = graph.size();
    std::vector<bool> visited(n, false);
    std::vector<int> distance(n, -1);
    
    std::queue<int> q;
    q.push(source);
    visited[source] = true;
    distance[source] = 0;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        std::cout << "Visiting vertex " << u 
                  << " at distance " << distance[u] << std::endl;
        
        for (int v : graph[u]) {
            if (!visited[v]) {
                visited[v] = true;
                distance[v] = distance[u] + 1;
                q.push(v);
            }
        }
    }
}

int main() {
    // Adjacency list representation
    std::vector<std::vector<int>> graph = {
        {1, 2},    // 0 -> 1, 2
        {3},       // 1 -> 3
        {3},       // 2 -> 3
        {}         // 3 -> (none)
    };
    
    BFS(graph, 0);
    return 0;
}
```

### DFS Implementation (C++)

```cpp
#include <iostream>
#include <vector>

void DFSUtil(const std::vector<std::vector<int>>& graph, 
             int v, std::vector<bool>& visited) {
    visited[v] = true;
    std::cout << "Visiting vertex " << v << std::endl;
    
    for (int u : graph[v]) {
        if (!visited[u]) {
            DFSUtil(graph, u, visited);
        }
    }
}

void DFS(const std::vector<std::vector<int>>& graph) {
    int n = graph.size();
    std::vector<bool> visited(n, false);
    
    for (int v = 0; v < n; v++) {
        if (!visited[v]) {
            DFSUtil(graph, v, visited);
        }
    }
}

int main() {
    std::vector<std::vector<int>> graph = {
        {1, 2},
        {3},
        {3},
        {}
    };
    
    DFS(graph);
    return 0;
}
```

### Topological Sort (C++)

```cpp
#include <iostream>
#include <vector>
#include <stack>

void topologicalSortUtil(int v, const std::vector<std::vector<int>>& graph,
                        std::vector<bool>& visited, std::stack<int>& stack) {
    visited[v] = true;
    
    for (int u : graph[v]) {
        if (!visited[u]) {
            topologicalSortUtil(u, graph, visited, stack);
        }
    }
    
    stack.push(v);
}

void topologicalSort(const std::vector<std::vector<int>>& graph) {
    int n = graph.size();
    std::vector<bool> visited(n, false);
    std::stack<int> stack;
    
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            topologicalSortUtil(i, graph, visited, stack);
        }
    }
    
    std::cout << "Topological order: ";
    while (!stack.empty()) {
        std::cout << stack.top() << " ";
        stack.pop();
    }
    std::cout << std::endl;
}

int main() {
    // DAG: 0→1, 0→2, 1→3, 2→3
    std::vector<std::vector<int>> graph = {
        {1, 2},
        {3},
        {3},
        {}
    };
    
    topologicalSort(graph);  // Output: 0 2 1 3 (or 0 1 2 3)
    return 0;
}
```

### Dijkstra's Algorithm (C++)

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using pii = std::pair<int, int>;  // (distance, vertex)

void dijkstra(const std::vector<std::vector<pii>>& graph, int source) {
    int n = graph.size();
    std::vector<int> dist(n, std::numeric_limits<int>::max());
    
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
    
    dist[source] = 0;
    pq.push({0, source});
    
    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();
        
        if (d > dist[u]) continue;
        
        for (auto [v, weight] : graph[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    
    std::cout << "Shortest distances from vertex " << source << ":\n";
    for (int i = 0; i < n; i++) {
        std::cout << "Vertex " << i << ": " << dist[i] << std::endl;
    }
}

int main() {
    // Graph as adjacency list with weights
    // graph[u] = {(v, weight), ...}
    std::vector<std::vector<pii>> graph = {
        {{1, 4}, {2, 1}},      // 0
        {{3, 1}},               // 1
        {{1, 2}, {3, 5}},      // 2
        {}                      // 3
    };
    
    dijkstra(graph, 0);
    return 0;
}
```

## Exercises

### Easy

1. **Connected Components**: Count the number of connected components in an undirected graph.

2. **Path Exists**: Determine if a path exists between two vertices using BFS or DFS.

3. **Graph Representation**: Convert an edge list to an adjacency list representation.

### Medium

4. **Cycle Detection**: Detect if an undirected graph contains a cycle using DFS.

5. **Bipartite Check**: Determine if a graph is bipartite using BFS with coloring.

6. **Course Schedule**: Given course prerequisites, determine if all courses can be completed (topological sort).

7. **Number of Islands**: Count islands in a 2D grid (connected components).

8. **Clone Graph**: Deep copy a graph.

### Hard

9. **Bridges in Graph**: Find all bridges (edges whose removal disconnects the graph).

10. **Articulation Points**: Find all vertices whose removal increases number of connected components.

11. **Strongly Connected Components**: Find all SCCs in a directed graph (Kosaraju's or Tarjan's algorithm).

12. **Shortest Path with K Edges**: Find shortest path with exactly K edges.

### Challenge

13. **Floyd-Warshall**: Implement all-pairs shortest path algorithm in O(V³).

14. **Network Delay Time**: Find time for signal to reach all nodes from source.

15. **Critical Connections**: Find all critical connections in a network (Tarjan's bridge-finding).

## Algorithm Comparison

| Algorithm | Use Case | Time | Space |
|-----------|----------|------|-------|
| BFS | Shortest path (unweighted) | O(V+E) | O(V) |
| DFS | Cycle detection, topology | O(V+E) | O(V) |
| Topological Sort | Task scheduling, DAG | O(V+E) | O(V) |
| Kruskal's MST | Sparse graphs | O(E log V) | O(V) |
| Prim's MST | Dense graphs | O(E log V) | O(V) |
| Dijkstra | Shortest path (non-neg) | O((V+E) log V) | O(V) |
| Bellman-Ford | Shortest path (neg ok) | O(VE) | O(V) |

## References

### Books
- **Introduction to Algorithms (CLRS)** - Chapters 22-24
  - Chapter 22: Elementary Graph Algorithms
  - Chapter 23: Minimum Spanning Trees
  - Chapter 24: Single-Source Shortest Paths

- **Algorithm Design** by Kleinberg & Tardos - Chapters 3, 4

### Online Resources
- [VisuAlgo - Graph Algorithms](https://visualgo.net/en/dfsbfs)
- [GeeksforGeeks - Graph Data Structure](https://www.geeksforgeeks.org/graph-data-structure-and-algorithms/)
- [Graph Theory Playlist - William Fiset](https://www.youtube.com/playlist?list=PLDV1Zeh2NRsDGO4--qE8yH72HFL1Km93P)
- [Graph Traversal Visualization](https://www.cs.usfca.edu/~galles/visualization/BFS.html)

## Summary

In this module, we covered:
- ✅ Graph representations (adjacency matrix, list, edge list)
- ✅ Graph traversal: BFS and DFS
- ✅ Topological sorting for DAGs
- ✅ Minimum spanning trees: Kruskal's and Prim's
- ✅ Shortest path algorithms: Dijkstra and Bellman-Ford

**Next Steps:** Proceed to [Module 5: Pattern Matching](05_pattern_matching.md) to learn string searching algorithms.

---

*💡 Tip: Choose BFS for shortest paths and level-order, DFS for topology and connectivity!*
