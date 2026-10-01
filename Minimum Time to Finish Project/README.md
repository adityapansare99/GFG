# Minimum Project Completion Time

## Problem

An IT company is working on a large project consisting of `n` modules.

* `duration[i]` represents the time required to complete the `i`th module.
* `dependencies[i] = [u, v]` means module `v` can be started only after module `u` is completed.
* Multiple modules can be completed simultaneously if all their dependencies are satisfied.

The task is to find the **minimum time required to complete the entire project**.

If the dependency graph contains a cycle, the project cannot be completed, so return `-1`.

A module is never dependent on itself.

## Examples

### Example 1

**Input:**

```text
duration[] = [10, 20, 30, 10, 30, 20]

dependencies[][] = [
    [5, 2],
    [5, 0],
    [4, 0],
    [4, 1],
    [2, 3],
    [3, 1]
]
```

**Output:**

```text
80
```

### Explanation

The important dependency paths include:

```text
5 -> 2 -> 3 -> 1
```

The total time for this path is:

```text
20 + 30 + 10 + 20 = 80
```

Although multiple modules can run simultaneously, the project completion time is determined by the **longest dependency path**.

Therefore, the minimum time required is:

```text
80
```

### Example 2

**Input:**

```text
duration[] = [5, 5, 5]

dependencies[][] = [
    [0, 1],
    [1, 2],
    [2, 0]
]
```

**Output:**

```text
-1
```

### Explanation

The dependencies form a cycle:

```text
0 -> 1 -> 2 -> 0
```

Because there is no module that can break this cycle and start the project, the project cannot be completed.

Therefore, return:

```text
-1
```

## Approach

This problem can be modeled as a **Directed Acyclic Graph (DAG)**.

Each module is represented by a vertex, and each dependency:

```text
u -> v
```

represents a directed edge from module `u` to module `v`.

The solution uses:

* **Topological Sorting**
* **Kahn's Algorithm**
* **Dynamic Programming**

### 1. Build the Graph

For every dependency `[u, v]`:

```text
u -> v
```

Add `v` to the adjacency list of `u`.

Also increase the indegree of `v`.

`indeg[v]` represents the number of modules that must be completed before module `v` can start.

### 2. Initialize the Queue

Every module with:

```text
indeg[i] == 0
```

has no dependencies.

Therefore, these modules can start immediately.

Add all such modules to the queue.

### 3. Calculate Completion Time

The array:

```cpp
finish[i]
```

stores the earliest time at which module `i` can be completed.

Initially:

```cpp
finish[i] = duration[i]
```

because modules with no dependencies can start at time `0`.

For an edge:

```text
u -> v
```

module `v` can start only after `u` finishes.

Therefore:

```cpp
finish[v] = max(finish[v], finish[u] + duration[v]);
```

We take the maximum because `v` may have multiple dependencies, and it must wait for the **last dependency to finish**.

### 4. Detect a Cycle

While performing topological sorting, count how many modules are processed.

If:

```text
count == n
```

then every module was processed and there is no cycle.

If:

```text
count != n
```

then some modules could not be processed because they belong to a cycle.

In that case, return:

```text
-1
```

### 5. Find the Project Completion Time

The complete project is finished when the last module finishes.

Therefore:

```cpp
max(finish[i])
```

is the answer.

## Code

```cpp
class Solution {
  public:
    int minTime(vector<int> &dura, vector<vector<int>> &edges) {
        // code here
        int n=dura.size();
        int m=edges.size();
        
        vector<vector<int>> adj(n);
        vector<int> finish=dura;
        vector<int> indeg(n,0);
        
        int c=0;
        for(auto &it:edges){
            int u=it[0];
            int v=it[1];
            
            indeg[v]++;
            
            adj[u].push_back(v);
        }
        
        queue<int> q;
        
        for(int i=0;i<n;i++){
            if(indeg[i]==0){
                q.push(i);
                c++;
            }
        }
        
        while(!q.empty()){
            auto top=q.front();
            q.pop();
            
            for(auto &it:adj[top]){
                indeg[it]--;
                finish[it]=max(finish[it],finish[top]+dura[it]);
                
                if(indeg[it]==0){
                    q.push(it);
                    c++;
                }
            }
        }
        
        if(c!=n){
            return -1;
        }
        
        return *max_element(finish.begin(),finish.end());
    }
};
```

## Dry Run

Consider:

```text
duration = [2, 3, 4, 5]

dependencies = [
    [0, 1],
    [1, 2],
    [2, 3]
]
```

The graph is:

```text
0 -> 1 -> 2 -> 3
```

Initial completion times:

```text
finish = [2, 3, 4, 5]
```

### Process Module 0

Module `0` finishes at:

```text
2
```

Module `1` can then finish at:

```text
2 + 3 = 5
```

So:

```text
finish[1] = 5
```

### Process Module 1

Module `2` can finish at:

```text
5 + 4 = 9
```

So:

```text
finish[2] = 9
```

### Process Module 2

Module `3` can finish at:

```text
9 + 5 = 14
```

So:

```text
finish[3] = 14
```

Therefore:

```text
answer = 14
```

## Why `max()` Is Used

Suppose module `3` has two dependencies:

```text
0 -> 3
1 -> 3
```

and:

```text
finish[0] = 10
finish[1] = 20
duration[3] = 5
```

Module `3` cannot start at time `10` because module `1` is still running.

It must wait until **all dependencies are completed**.

Therefore:

```text
start time = max(10, 20)
           = 20
```

and:

```text
finish[3] = 20 + 5
          = 25
```

Hence:

```cpp
finish[it]=max(finish[it],finish[top]+dura[it]);
```

is the key dynamic programming transition.

## Cycle Detection

Kahn's algorithm processes only vertices that eventually reach indegree `0`.

For:

```text
0 -> 1
1 -> 2
2 -> 0
```

the initial indegrees are:

```text
indeg[0] = 1
indeg[1] = 1
indeg[2] = 1
```

There is no vertex with indegree `0`.

Therefore, the queue remains empty and:

```text
c = 0
```

Since:

```text
c != n
```

the graph contains a cycle.

The solution returns:

```text
-1
```

## Complexity Analysis

Let:

* `n` = number of modules
* `m` = number of dependencies

### Time Complexity

Building the graph takes:

```text
O(n + m)
```

Topological sorting processes every module and dependency once:

```text
O(n + m)
```

Finding the maximum completion time takes:

```text
O(n)
```

Therefore, the total time complexity is:

```text
O(n + m)
```

### Space Complexity

The adjacency list requires:

```text
O(n + m)
```

The `indeg`, `finish`, and queue structures require:

```text
O(n)
```

Therefore, the total space complexity is:

```text
O(n + m)
```

## Key Concepts

* Directed Graph
* Topological Sort
* Kahn's Algorithm
* Indegree
* Dynamic Programming on DAG
* Longest Path in a DAG
* Cycle Detection

## Important Observation

Because modules can be executed **simultaneously**, we should not simply add the duration of all modules.

Instead, the answer is determined by the **longest dependency chain**.

For a DAG:

```text
      A
     / \
    B   C
     \ /
      D
```

`B` and `C` can execute simultaneously after `A`.

Therefore, the total project time is determined by the dependency path that takes the longest amount of time.

This is why the solution combines **topological sorting with dynamic programming**.
