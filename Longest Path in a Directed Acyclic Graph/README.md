# Longest Path in a Directed Acyclic Graph

## Problem Statement

Given a weighted Directed Acyclic Graph (DAG) with `V` vertices numbered from `0` to `V - 1`, represented by `edges[][]`, where:

```text
edges[i] = [u, v, w]
```

represents a directed edge from vertex `u` to vertex `v` with weight `w`.

You are also given a source vertex `src`.

Return the distance array where:

```text
dist[i] = longest distance from src to vertex i
```

If a vertex is unreachable from `src`, store `INT_MIN` for that vertex.

---

## Intuition

We need to find the **maximum distance** from the source to every vertex.

We maintain:

```text
dist[i]
```

which represents the maximum distance currently known for vertex `i`.

Initially, every vertex is unreachable:

```text
dist[i] = INT_MIN
```

and the source has distance:

```text
dist[src] = 0
```

We use an adjacency list to store the graph.

Then we use a **max-priority queue** so that the vertex having the currently largest distance is processed first.

For every edge:

```text
u -> v
weight = w
```

we check whether going through `u` gives a longer path to `v`:

```text
dist[u] + w > dist[v]
```

If it does, we update:

```text
dist[v] = dist[u] + w
```

and push the updated distance into the priority queue.

---

## Dry Run

Consider:

```text
V = 6
src = 0

edges =
0 -> 1 (5)
0 -> 2 (3)
1 -> 3 (6)
1 -> 2 (2)
2 -> 4 (4)
2 -> 5 (2)
2 -> 3 (7)
3 -> 5 (1)
3 -> 4 (-1)
4 -> 5 (-2)
```

Initially:

```text
dist = [0, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN]
```

The priority queue contains:

```text
(0, 0)
```

### Process vertex 0

Edges from `0`:

```text
0 -> 1 = 5
0 -> 2 = 3
```

Update:

```text
dist[1] = 5
dist[2] = 3
```

Now:

```text
dist = [0, 5, 3, INT_MIN, INT_MIN, INT_MIN]
```

---

### Process vertex 1

Current distance:

```text
dist[1] = 5
```

Edge:

```text
1 -> 3 = 6
```

Therefore:

```text
dist[3] = 5 + 6 = 11
```

Edge:

```text
1 -> 2 = 2
```

We get:

```text
5 + 2 = 7
```

Since:

```text
7 > dist[2]
```

update:

```text
dist[2] = 7
```

Now:

```text
dist = [0, 5, 7, 11, INT_MIN, INT_MIN]
```

---

### Process vertex 2

Current distance:

```text
dist[2] = 7
```

For:

```text
2 -> 4 = 4
```

we get:

```text
dist[4] = 11
```

For:

```text
2 -> 5 = 2
```

we get:

```text
dist[5] = 9
```

For:

```text
2 -> 3 = 7
```

we get:

```text
7 + 7 = 14
```

Since `14 > 11`:

```text
dist[3] = 14
```

---

### Continue processing

The updated distances are propagated through the remaining edges.

The final `dist` array contains the longest distance from `src` to every reachable vertex.

For unreachable vertices, the value remains:

```text
INT_MIN
```

---

## Code

```cpp
class Solution {
public:
    vector<int> maxDistance(int V, int src, vector<vector<int>> &edges) {
        vector<vector<pair<int,int>>> adj(V);
        
        for(auto &it : edges){
            int u = it[0];
            int v = it[1];
            int w = it[2];
            
            adj[u].push_back({v, w});
        }
        
        vector<int> dist(V, INT_MIN);
        priority_queue<pair<int,int>> pq;
        
        pq.push({0, src});
        dist[src] = 0;
        
        while(!pq.empty()){
            auto top = pq.top();
            pq.pop();
            
            int we = top.first;
            int node = top.second;
            
            if(we < dist[node]){
                continue;
            }
            
            for(auto &it : adj[node]){
                int w = it.second;
                int n = it.first;
                
                if(we + w > dist[n]){
                    dist[n] = we + w;
                    pq.push({we + w, n});
                }
            }
        }
        
        return dist;
    }
};
```

---

## Complexity

Let:

```text
V = number of vertices
E = number of edges
```

### Time Complexity

Building the adjacency list takes:

```text
O(E)
```

Each relaxation can insert an updated distance into the priority queue.

Priority queue operations take:

```text
O(log E)
```

Therefore, for this implementation:

```text
O(E log E)
```

in the typical bound.

### Space Complexity

The adjacency list stores all edges:

```text
O(V + E)
```

The distance array requires:

```text
O(V)
```

The priority queue can contain multiple entries:

```text
O(E)
```

Therefore:

```text
O(V + E)
```

---

## Key Takeaway

The main idea is:

```text
Create adjacency list
        ↓
Initialize all distances to INT_MIN
        ↓
Set dist[src] = 0
        ↓
Use max-priority queue
        ↓
Take the vertex with maximum known distance
        ↓
Relax all outgoing edges
        ↓
Update distance if a longer path is found
        ↓
Return the distance array
```

Since the graph is a DAG, this problem can also be solved using **topological sorting + dynamic programming**, which is the standard DAG-specific approach. The above implementation instead uses a max-priority queue and follows the logic of the submitted solution.
