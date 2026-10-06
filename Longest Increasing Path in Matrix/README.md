# Your Social Network

## Problem Statement

Geek is creating a social networking site called **Geeksbook** with `n` users numbered from `1` to `n`.

Each user `i` where `2 <= i <= n` has exactly one friend, and that friend always has a smaller user number than `i`.

User `1` has no friend.

The friends of users `2` to `n` are given in an array `arr[]` of size `n - 1`:

- `arr[0]` is the friend of user `2`.
- `arr[1]` is the friend of user `3`.
- `arr[i - 2]` is the friend of user `i`.

The relationship is **one-way**.

A user can reach another user by repeatedly following their friend's link.

For every user `i` from `2` to `n`, find every user `j` where:

```text
1 <= j < i
```

that can be reached from `i`.

For every reachable pair `(i, j)`, create:

```text
[i, j, k]
```

where:

- `i` = starting user
- `j` = reachable user
- `k` = number of links that must be followed to reach `j` from `i`

The result must follow this ordering:

1. Process users `i` from `2` to `n`.
2. For every user `i`, consider users `j` from `1` to `i - 1` in increasing order.
3. Add `[i, j, k]` only when `j` is reachable from `i`.

---

# Examples

## Example 1

```text
Input:
arr[] = [1, 2]

Output:
[[2, 1, 1], [3, 1, 2], [3, 2, 1]]
```

### Explanation

The links are:

```text
2 -> 1
3 -> 2
```

Therefore:

```text
2 -> 1
```

User `2` reaches user `1` in `1` link:

```text
[2, 1, 1]
```

User `3` can reach user `2` directly:

```text
[3, 2, 1]
```

User `3` can also reach user `1` through user `2`:

```text
3 -> 2 -> 1
```

which requires `2` links:

```text
[3, 1, 2]
```

Following the required ordering gives:

```text
[[2, 1, 1], [3, 1, 2], [3, 2, 1]]
```

---

## Example 2

```text
Input:
arr[] = [1, 1]

Output:
[[2, 1, 1], [3, 1, 1]]
```

### Explanation

The links are:

```text
2 -> 1
3 -> 1
```

User `2` reaches user `1` in one link:

```text
[2, 1, 1]
```

User `3` also reaches user `1` in one link:

```text
[3, 1, 1]
```

Therefore:

```text
[[2, 1, 1], [3, 1, 1]]
```

---

# Constraints

- `2 <= arr.size() <= 500`
- `1 <= arr[i] <= 500`

---

# Approach

The solution uses a **directed graph** to represent the friendship relationships.

For every user `i`, there is a directed edge:

```text
i -> friend[i]
```

For example, if:

```text
arr = [1, 2]
```

then:

```text
2 -> 1
3 -> 2
```

The code builds this graph using an adjacency list.

After constructing the graph, the solution processes every user separately.

For each starting user, the helper function `solver()` calculates the shortest distance from that user to every other user.

Since every friendship link has a cost of `1`, the distance represents the **number of links followed**.

---

# Graph Representation

The code creates:

```cpp
vector<vector<int>> adj(v);
```

This is an adjacency list.

The graph is directed because the friendship relationship is one-way.

For example:

```text
arr = [1, 2, 1]
```

represents:

```text
2 -> 1
3 -> 2
4 -> 1
```

The adjacency list becomes approximately:

```text
adj[1] = {}
adj[2] = {1}
adj[3] = {2}
adj[4] = {1}
```

The important point is that the edge is stored as:

```text
current user -> friend
```

which is exactly the direction required to follow the friendship links.

---

# Building the Graph

Inside `socialNetwork()`, the code starts with:

```cpp
int curr=2;
```

because `arr[0]` represents the friend of user `2`.

The loop is:

```cpp
for(int i=0;i<n;i++){
    int val=arr[i];

    adj[curr].push_back(val);
    curr++;
}
```

For every element:

```text
arr[i]
```

the corresponding edge is:

```text
curr -> arr[i]
```

Then `curr` is increased to represent the next user.

---

# Why `v = n + 2`

The code uses:

```cpp
int n=arr.size();
int v=n+2;
```

The array contains the friends of users `2` through `n`.

Therefore, if:

```text
arr.size() = n
```

then the users represented are:

```text
2, 3, ..., n+1
```

The code therefore allocates an adjacency list large enough to safely use these indices.

The loops also use:

```cpp
for(int i=2;i<v;i++)
```

so the starting users processed by the implementation are represented by the indices from `2` through `v-1`.

---

# Shortest Path Calculation

The helper function is:

```cpp
solver(adj, v, src)
```

where:

- `adj` = graph
- `v` = number of allocated vertices
- `src` = current starting user

The function calculates the distance from `src` to every reachable vertex.

---

# Distance Array

The function initializes:

```cpp
vector<int> dist(v,1e9);
```

Every vertex initially has distance:

```text
1e9
```

which represents that the vertex has not been reached yet.

The starting vertex has distance `0`:

```cpp
dist[src]=0;
```

This makes sense because no edge needs to be followed to reach the starting vertex itself.

---

# Priority Queue

The code uses:

```cpp
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
```

The priority queue stores:

```text
(distance, node)
```

The smallest distance is processed first.

Initially:

```cpp
pq.push({0,src});
```

So the source vertex is inserted with distance `0`.

---

# Relaxation

The main graph traversal is:

```cpp
while(!pq.empty()){
    auto top=pq.top();
    pq.pop();

    int node=top.second;
    int val=top.first;

    for(auto &it:adj[node]){
        if(dist[it]>dist[node]+1){
            pq.push({dist[node]+1,it});
            dist[it]=dist[node]+1;
        }
    }
}
```

For every neighbor:

```cpp
it
```

the code checks whether reaching that neighbor through the current node produces a shorter distance.

The edge has weight `1`, so:

```text
new distance = dist[node] + 1
```

If this is better than the currently stored distance:

```cpp
dist[it]>dist[node]+1
```

the distance is updated.

---

# Why Shortest Distance Represents Number of Links

Every friendship link has exactly the same cost:

```text
1
```

Therefore, if a user can be reached through:

```text
i -> a -> b -> j
```

then the number of links is:

```text
3
```

The distance calculated by the algorithm is also:

```text
3
```

Therefore:

```text
distance = number of links
```

which is exactly the value required for `k`.

---

# Collecting the Result

After calculating all distances from `src`, the helper function creates:

```cpp
vector<vector<int>> res;
```

Then it checks users smaller than `src`:

```cpp
for(int i=1;i<src;i++){
    if(dist[i]!=1e9){
        res.push_back({src,i,dist[i]});
    }
}
```

There are two important conditions here.

### Condition 1: `i < src`

The problem requires only users with smaller numbers:

```text
j < i
```

Therefore, the loop goes from:

```text
1
```

to:

```text
src - 1
```

### Condition 2: `dist[i] != 1e9`

If the distance is still `1e9`, the user was never reached.

Therefore, only reachable users are added.

The result entry is:

```cpp
{src,i,dist[i]}
```

which represents:

```text
[starting user, reachable user, number of links]
```

---

# Maintaining the Required Ordering

The main function processes starting users using:

```cpp
for(int i=2;i<v;i++){
    auto ans=solver(adj,v,i);
    res.insert(res.end(),ans.begin(),ans.end());
}
```

The users are processed in increasing order:

```text
2, 3, 4, ...
```

Inside `solver()`, the destination users are also processed in increasing order:

```text
1, 2, 3, ..., src-1
```

Therefore, the implementation follows the ordering required by the problem.

---

# Dry Run

Consider:

```text
arr = [1,2]
```

The graph is:

```text
2 -> 1
3 -> 2
```

---

## Starting User = 2

Distances start as:

```text
dist[2] = 0
```

From user `2`, we can go to:

```text
2 -> 1
```

Therefore:

```text
dist[1] = 1
```

The destination users smaller than `2` are:

```text
1
```

Since user `1` is reachable:

```text
[2,1,1]
```

is added.

---

## Starting User = 3

Initially:

```text
dist[3] = 0
```

From user `3`:

```text
3 -> 2
```

Therefore:

```text
dist[2] = 1
```

Then from user `2`:

```text
2 -> 1
```

Therefore:

```text
dist[1] = 2
```

Now destinations smaller than `3` are checked in increasing order:

```text
1
2
```

For user `1`:

```text
[3,1,2]
```

For user `2`:

```text
[3,2,1]
```

Therefore the final result is:

```text
[[2,1,1],[3,1,2],[3,2,1]]
```

---

# Algorithm

1. Determine the number of vertices used by the implementation.
2. Create a directed adjacency list.
3. Start with user `2`.
4. For every value in `arr`:
   - Create an edge from the current user to the corresponding friend.
   - Move to the next user.
5. For every starting user:
   - Run `solver()`.
   - Calculate the shortest distance from the starting user to every reachable user.
6. Check all users smaller than the current starting user.
7. For every reachable user, add:
   ```text
   [source, destination, distance]
   ```
8. Append the result for the current source to the final result.
9. Return the complete 2D array.

---

# Complexity Analysis

Let `V` be the number of vertices and `E` be the number of edges.

For every starting vertex, the code calls `solver()`.

Inside `solver()`, Dijkstra's algorithm is used with a priority queue.

The complexity of one Dijkstra traversal is approximately:

```text
O((V + E) log V)
```

The traversal is performed for every starting vertex.

Therefore, the overall complexity is approximately:

```text
O(V * (V + E) log V)
```

In this problem, each user has only one outgoing friend, so the number of edges is linear with respect to the number of users:

```text
E = O(V)
```

Therefore, this becomes approximately:

```text
O(V² log V)
```

The result itself can contain `O(V²)` entries in the worst case, because many pairs can be reachable.

---

# Space Complexity

The adjacency list requires:

```text
O(V + E)
```

The distance array requires:

```text
O(V)
```

The priority queue can contain multiple entries during the traversal.

The result can contain up to:

```text
O(V²)
```

reachable pairs.

Therefore, including the output:

```text
O(V²)
```

space may be required.

Ignoring the output storage, the auxiliary space is approximately:

```text
O(V + E)
```

which is:

```text
O(V)
```

for this particular graph structure.

---

# Important Observations

## 1. The Graph Is Directed

The relationship is one-way.

If:

```text
2 -> 1
```

we can travel from `2` to `1`.

But we cannot travel from `1` to `2`.

Therefore, the graph must preserve the direction of the relationship.

---

## 2. Every Edge Has Weight 1

Every friendship link counts as exactly one step.

For example:

```text
4 -> 3 -> 2 -> 1
```

requires:

```text
3
```

links.

Therefore, every edge has weight `1`.

---

## 3. Only Smaller Users Are Considered

For every source `i`, only:

```text
j < i
```

must be considered.

This is implemented by:

```cpp
for(int i=1;i<src;i++)
```

inside `solver()`.

---

## 4. Result Ordering Is Important

The problem does not simply ask for all reachable pairs.

The output must follow a specific order.

The implementation maintains this by:

- Processing source users in increasing order.
- Processing destination users in increasing order.

---

# Why the Priority Queue Is Used

The implementation uses Dijkstra's shortest-path technique:

```cpp
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>>
```

The priority queue ensures that the currently smallest known distance is processed first.

Since all edges have weight `1`, the shortest distance represents the minimum number of friendship links required to reach a user.

Although a BFS-based solution could also be used for this unweighted graph, the submitted implementation uses a priority queue and is therefore analyzed accordingly.

---

# Code

> **Important:** The following code is reproduced exactly as provided. No line of the implementation has been changed.

```cpp
class Solution {
   private:
   vector<vector<int>> solver(vector<vector<int>> &adj,int v,int src){
       vector<int> dist(v,1e9);
       priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
       dist[src]=0;
       pq.push({0,src});
       
       while(!pq.empty()){
           auto top=pq.top();
           pq.pop();
           
           int node=top.second;
           int val=top.first;
           
           for(auto &it:adj[node]){
               if(dist[it]>dist[node]+1){
                   pq.push({dist[node]+1,it});
                   dist[it]=dist[node]+1;
               }
           }
       }
       
       vector<vector<int>> res;
       for(int i=1;i<src;i++){
           if(dist[i]!=1e9){
               res.push_back({src,i,dist[i]});
           }
       }
       
       return res;
   }
 public:
   vector<vector<int>> socialNetwork(vector<int>& arr) {
       // code here
       int n=arr.size();
       
       int v=n+2;
       
       vector<vector<int>> adj(v);
       int curr=2;
       
       for(int i=0;i<n;i++){
           int val=arr[i];
           
           // adj[val].push_back(curr);
           adj[curr].push_back(val);
           curr++;
       }
       
       vector<vector<int>> res;
       
       for(int i=2;i<v;i++){
           auto ans=solver(adj,v,i);
           res.insert(res.end(),ans.begin(),ans.end());
       }
       
       return res;
   }
};
```

---

# Code Structure

The implementation is divided into two main functions.

## `socialNetwork()`

```cpp
vector<vector<int>> socialNetwork(vector<int>& arr)
```

This is the main function.

Its responsibilities are:

- Construct the graph.
- Process every starting user.
- Call `solver()`.
- Combine all partial results.
- Return the final answer.

---

## `solver()`

```cpp
vector<vector<int>> solver(vector<vector<int>> &adj,int v,int src)
```

This helper function handles one starting user.

Its responsibilities are:

- Calculate distances from `src`.
- Determine which smaller users are reachable.
- Store the required `[src, destination, distance]` entries.
- Return those entries to `socialNetwork()`.

---

# Final Complexity Summary

| Component | Complexity |
|---|---:|
| Graph construction | `O(V)` |
| One `solver()` call | `O((V + E) log V)` |
| All source users | `O(V(V + E) log V)` |
| For this graph | `O(V² log V)` |
| Auxiliary space | `O(V)` |
| Output space | `O(V²)` |

---

# Key Takeaways

- The problem can be modeled naturally as a **directed graph**.
- Each user points toward their friend.
- Following a friendship link corresponds to traversing a directed edge.
- The number of links is the shortest-path distance.
- The submitted implementation calculates distances independently for every starting user.
- A priority queue is used to perform Dijkstra-style shortest-path traversal.
- Only destinations with smaller user numbers are included.
- The output is generated in the required source-and-destination ordering.
- The worst-case output itself can contain a quadratic number of entries.

## Core Idea

```text
Build Directed Graph
        ↓
For Every Starting User
        ↓
Find Shortest Distances
        ↓
Check Smaller Users
        ↓
Add [source, destination, distance]
        ↓
Combine All Results
```