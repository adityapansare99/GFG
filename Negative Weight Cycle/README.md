# Negative Weight Cycle

## Problem Statement

Given a weighted directed graph containing `V` vertices numbered from `0` to `V - 1` and `E` directed edges, determine whether the graph contains a **negative weight cycle**.

Each edge is represented as:

```text
[u, v, w]
```

which means there is a directed edge:

```text
u → v
```

with weight `w`.

A **negative weight cycle** is a cycle whose total edge weight is negative.

Return:

```text
true
```

if a negative weight cycle exists, otherwise return:

```text
false
```

---

## Intuition

This problem can be solved using the **Bellman-Ford algorithm**.

The important property of Bellman-Ford is:

> If we can still relax an edge after performing `V - 1` complete rounds of relaxation, then the graph contains a negative weight cycle.

Why?

In a graph without a negative cycle, the longest possible simple path contains at most `V - 1` edges.

Therefore, after `V - 1` rounds, all shortest distances should have stabilized.

If some distance can still be improved in the `V`th round, the improvement must come from repeatedly going through a cycle.

For that improvement to continue, the cycle must have a **negative total weight**.

---

## Why Initialize All Distances to 0?

We are not given a source vertex.

The negative cycle could exist in **any disconnected component** of the graph.

For example:

```text
0 → 1

2 → 3 → 2
```

The negative cycle may be in the component containing `2`, even though vertex `0` has no path to it.

If we started Bellman-Ford from only one source, we could miss that cycle.

Instead, we initialize:

```text
dist[i] = 0
```

for every vertex.

This is equivalent to adding a virtual source connected to every vertex with a zero-weight edge.

Therefore, every vertex can be considered reachable.

---

## Bellman-Ford Relaxation

For every edge:

```text
u → v
weight = w
```

we check:

```text
dist[u] + w < dist[v]
```

If this is true, we can improve the distance to `v`:

```text
dist[v] = dist[u] + w
```

We perform this for all edges `V - 1` times.

---

## Detecting the Negative Cycle

After `V - 1` rounds, we perform one additional pass over all edges.

If we find:

```text
dist[u] + w < dist[v]
```

then the distance can still be improved.

Therefore:

```text
Negative weight cycle exists
```

and we return:

```text
true
```

Otherwise:

```text
false
```

---

## Dry Run

Consider:

```text
V = 4

edges =
[
    [1,0,4],
    [3,1,-2],
    [1,2,-6],
    [2,3,5]
]
```

The graph is:

```text
1 → 0   weight = 4
↑
|
3 ← 2
```

More clearly, the important cycle is:

```text
1 → 2 → 3 → 1
```

Its total weight is:

```text
-6 + 5 + (-2)
= -3
```

Therefore, this is a negative cycle.

---

### Initial Distances

Since there is no source:

```text
dist = [0, 0, 0, 0]
```

---

### Relaxation

Consider:

```text
1 → 2  (-6)
```

We get:

```text
dist[2] = min(0, 0 - 6)
        = -6
```

Then:

```text
2 → 3  (5)
```

gives:

```text
dist[3] = -6 + 5
        = -1
```

Then:

```text
3 → 1  (-2)
```

gives:

```text
dist[1] = -1 - 2
        = -3
```

The value of `dist[1]` keeps decreasing because we can continue going around:

```text
1 → 2 → 3 → 1
```

The cycle has total weight `-3`, so every additional traversal makes the distance smaller.

---

## Final Negative Cycle Check

After `V - 1` rounds, we check every edge again.

For the edge:

```text
3 → 1 (-2)
```

we can still improve:

```text
dist[3] + (-2) < dist[1]
```

Therefore, a negative cycle exists.

```text
Answer = true
```

---

## Example Without a Negative Cycle

Consider:

```text
V = 4

edges =
[
    [0,3,6],
    [1,0,4],
    [1,2,6],
    [3,1,2]
]
```

There is a cycle:

```text
1 → 0 → 3 → 1
```

Its total weight is:

```text
4 + 6 + 2
= 12
```

Since:

```text
12 > 0
```

the cycle is not negative.

After `V - 1` relaxation rounds, no edge can be further relaxed.

Therefore:

```text
Answer = false
```

---

## Code

```cpp
class Solution {
public:
    bool isNegativeWeightCycle(int V, vector<vector<int>>& edges) {
        vector<long long> dist(V, 0);

        // Relax all edges V - 1 times
        for (int i = 0; i < V - 1; i++) {
            bool changed = false;

            for (auto &it : edges) {
                int u = it[0];
                int v = it[1];
                int w = it[2];

                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    changed = true;
                }
            }

            if (!changed) {
                break;
            }
        }

        // One more relaxation to detect a negative cycle
        for (auto &it : edges) {
            int u = it[0];
            int v = it[1];
            int w = it[2];

            if (dist[u] + w < dist[v]) {
                return true;
            }
        }

        return false;
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

Bellman-Ford relaxes all `E` edges for at most `V - 1` rounds:

```text
O(V × E)
```

The final cycle detection requires one additional pass:

```text
O(E)
```

Therefore:

```text
Time Complexity: O(V × E)
```

### Space Complexity

We only maintain the distance array:

```text
dist[V]
```

Therefore:

```text
Space Complexity: O(V)
```

---

## Key Takeaway

The main idea is:

```text
Initialize all distances to 0
        ↓
Relax every edge V - 1 times
        ↓
Perform one extra relaxation
        ↓
If any distance improves
        ↓
Negative weight cycle exists
```

The most important Bellman-Ford property is:

```text
If an edge can still be relaxed after V - 1 rounds,
the graph contains a negative weight cycle.
```

Since the problem asks whether **anywhere in the graph** there is a negative cycle, initializing every distance to `0` lets us detect cycles even in disconnected components.
