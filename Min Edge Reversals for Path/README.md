# Min Edge Reversals for Path

## Problem

Given a directed graph with `n` vertices numbered from `1` to `n`, where each edge `edges[i] = [u, v]` represents a directed edge from `u` to `v`.

You are also given a source vertex `src` and a destination vertex `dst`.

Find the **minimum number of edges that need to be reversed** so that there exists at least one path from `src` to `dst`.

If it is not possible to create a path from `src` to `dst`, return `-1`.

---

## Example 1

```text
Input:
n = 3
edges = [[1,2],[3,2]]
src = 1
dst = 3

Output:
1
```

Initially:

```text
1 → 2 ← 3
```

There is no path from `1` to `3`.

If we reverse the edge `3 → 2`, it becomes:

```text
1 → 2 → 3
```

Therefore, only `1` edge needs to be reversed.

---

## Example 2

```text
Input:
n = 4
edges = [[1,2],[2,3],[3,4]]
src = 1
dst = 4

Output:
0
```

A path already exists:

```text
1 → 2 → 3 → 4
```

Therefore, no edge reversal is required.

---

# Approach

## Dijkstra's Algorithm

The main idea is to convert the problem into a **shortest path problem**.

For every directed edge:

```text
u → v
```

there are two possible movements.

### 1. Move in the original direction

```text
u → v
```

No reversal is required.

Cost:

```text
0
```

### 2. Move in the reverse direction

```text
v → u
```

The edge must be reversed.

Cost:

```text
1
```

Therefore, every original edge can be treated as:

```text
u → v : cost 0
v → u : cost 1
```

Now the problem becomes:

> Find the minimum-cost path from `src` to `dst`.

The path cost represents the minimum number of edge reversals.

---

# Graph Representation

Two adjacency lists are created:

```cpp
vector<vector<int>> adj(n+1);
vector<vector<int>> reverse(n+1);
```

For every edge:

```text
u → v
```

we store:

```cpp
adj[u].push_back(v);
reverse[v].push_back(u);
```

Here:

- `adj` stores edges that can be followed without reversal.
- `reverse` stores edges that require one reversal.

For example:

```text
edge = [1,2]
```

is represented as:

```text
1 → 2   cost = 0
2 → 1   cost = 1
```

---

# Priority Queue

A priority queue is used to implement Dijkstra's algorithm.

```cpp
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
```

Each pair contains:

```text
{cost, node}
```

The node with the smallest reversal cost is processed first.

Initially:

```cpp
pq.push({0,src});
cost[src]=0;
```

The source requires `0` reversals.

---

# Processing Original Edges

For an edge stored in `adj[node]`, we are moving in the original direction.

Therefore, no reversal is required:

```cpp
if(cost[n]>cost[node]){
    cost[n]=cost[node];
    pq.push({cost[node],n});
}
```

The cost remains unchanged.

---

# Processing Reversed Edges

For an edge stored in `reverse[node]`, we are moving opposite to the original direction.

Therefore, one reversal is required:

```cpp
if(cost[n]>cost[node]+1){
    cost[n]=cost[node]+1;
    pq.push({cost[n],n});
}
```

The cost increases by `1`.

---

# Example Walkthrough

Consider:

```text
edges = [[1,2],[3,2]]
src = 1
dst = 3
```

Original graph:

```text
1 → 2 ← 3
```

From `1`, we can move:

```text
1 → 2
```

with cost `0`.

At node `2`, to reach `3`, we need to move opposite to:

```text
3 → 2
```

So:

```text
2 → 3
```

requires one reversal.

The resulting path is:

```text
1 → 2 → 3

cost = 0 + 1
     = 1
```

Therefore, the answer is:

```text
1
```

---

# Early Termination

When the destination is removed from the priority queue:

```cpp
if(node==dst){
    return val;
}
```

we can immediately return the current cost.

Dijkstra processes nodes in increasing order of cost, so the first time `dst` is removed from the priority queue, its cost is minimum.

---

# Code

```cpp
class Solution {
  public:
    int minimumEdgeReversal(vector<vector<int>> &edges, int n, int src, int dst) {
        // code here  
        vector<vector<int>> adj(n+1);
        vector<vector<int>> reverse(n+1);

        for(auto &it:edges){
            int u=it[0];
            int v=it[1];

            adj[u].push_back(v);
            reverse[v].push_back(u);
        }

        priority_queue<pair<int,int> , vector<pair<int,int>> , greater<>> pq;
        vector<int> cost(n+1,1e9);

        pq.push({0,src});
        cost[src]=0;

        while(!pq.empty()){
            auto top=pq.top();
            pq.pop();

            int node=top.second;
            int val=top.first;

            if(node==dst){
                return val;
            }

            for(auto &it:adj[node]){
                int n=it;
                if(cost[n]>cost[node]){
                    cost[n]=cost[node];
                    pq.push({cost[node],n});
                }
            }

            for(auto &it:reverse[node]){
                int n=it;
                if(cost[n]>cost[node]+1){
                    cost[n]=cost[node]+1;
                    pq.push({cost[n],n});
                }
            }
        }

        return -1;
    }
};
```

---

# Complexity

Let:

- `n` = number of vertices
- `m` = number of edges

Each original edge creates two possible movements:

```text
Original direction → cost 0
Reverse direction  → cost 1
```

Using Dijkstra with a priority queue:

```text
Time Complexity: O((n + m) log n)
Space Complexity: O(n + m)
```

---

# Key Observation

The most important transformation is:

```text
Original Edge

u ─────→ v
  cost 0

v ─────→ u
  cost 1
```

After this transformation, the problem is simply a shortest path problem.

The total path cost represents the number of edges that need to be reversed.

---

# Algorithm

1. Create an adjacency list for the original edges.
2. Create another adjacency list for reverse movements.
3. Assign cost `0` to original-direction movements.
4. Assign cost `1` to reverse-direction movements.
5. Run Dijkstra's algorithm from `src`.
6. When `dst` is reached, return its minimum cost.
7. If `dst` cannot be reached, return `-1`.

---

# Key Takeaway

```text
Directed Graph
      |
      ↓
Original edge → Cost 0
Reverse edge  → Cost 1
      |
      ↓
Shortest Path
      |
      ↓
Minimum Edge Reversals
```

**Core Concept:** Convert every edge reversal into an edge with cost `1` and every original edge into an edge with cost `0`. Then find the minimum-cost path from `src` to `dst`.
