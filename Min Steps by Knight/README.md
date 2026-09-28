# Min Steps by Knight

## Problem

Given an `n × n` chessboard, the initial position of a Knight and the target position are given.

The task is to find the **minimum number of moves** required for the Knight to reach the target position.

The Knight can move in 8 possible directions:

* `(x - 2, y + 1)`
* `(x - 2, y - 1)`
* `(x + 2, y + 1)`
* `(x + 2, y - 1)`
* `(x - 1, y + 2)`
* `(x - 1, y - 2)`
* `(x + 1, y + 2)`
* `(x + 1, y - 2)`

The positions in the problem are **1-based indexed**.

---

## Approach

The solution uses a **Dijkstra-style shortest path algorithm**.

Each cell of the chessboard can be considered as a node in a graph.

* Each valid Knight move represents an edge.
* Every move has a cost of `1`.
* Therefore, we need to find the shortest path from the starting cell to the target cell.

### Distance Matrix

A 2D `dist` array is maintained:

```cpp
vector<vector<int>> dist(n,vector<int>(n,1e9));
```

`dist[i][j]` stores the minimum number of moves currently known to reach cell `(i, j)`.

Initially, every cell is assigned a very large value.

The starting position is assigned distance `0`.

---

## Priority Queue

A min-priority queue is used:

```cpp
priority_queue<pair<int,pair<int,int>>,
               vector<pair<int,pair<int,int>>>,
               greater<>> pq;
```

Each element contains:

```text
{distance, {row, column}}
```

The cell with the smallest distance is processed first.

Initially, the Knight's starting position is inserted with distance `0`.

---

## 1-Based to 0-Based Conversion

The problem uses 1-based indexing, while the C++ vector uses 0-based indexing.

Therefore, the starting position is converted using:

```cpp
knightPos[0] - 1
knightPos[1] - 1
```

Similarly, the target position is checked using:

```cpp
targetPos[0] - 1
targetPos[1] - 1
```

For example:

```text
Chessboard position: (3, 3)
Array position:      (2, 2)
```

---

## Processing a Cell

For every current cell `(i, j)`, all 8 possible Knight moves are checked.

For example:

```cpp
ni=i-2;
nj=j+1;
```

If the new position is inside the board and reaching it through the current cell gives a smaller distance, its distance is updated:

```cpp
if(ni>=0 && nj<n && dist[ni][nj]>dist[i][j]+1){
    dist[ni][nj]=val+1;
    pq.push({val+1,{ni,nj}});
}
```

The same process is repeated for all 8 possible Knight moves.

---

## Target Check

Whenever a cell is removed from the priority queue, the solution checks whether it is the target:

```cpp
if(targetPos[0]-1==i && targetPos[1]-1==j){
    return val;
}
```

Since the priority queue processes the smallest distance first, the first time the target is reached, the minimum number of moves has been found.

---

## Why This Works

Every Knight move has the same cost:

```text
Cost of every move = 1
```

Therefore, the problem is a shortest-path problem where every edge has equal weight.

The algorithm maintains the smallest known distance to every board cell and continuously explores the cell having the smallest distance.

Whenever a shorter path to a neighboring cell is found, its distance is updated and the cell is added to the priority queue.

Thus, when the target position is removed from the priority queue, its distance represents the minimum number of Knight moves required.

---

## Algorithm

1. Create an `n × n` distance matrix and initialize every value to a large number.
2. Convert the starting position from 1-based indexing to 0-based indexing.
3. Set the starting cell's distance to `0`.
4. Insert the starting cell into the min-priority queue.
5. While the priority queue is not empty:

   * Remove the cell having the smallest distance.
   * Check if it is the target.
   * Generate all 8 possible Knight moves.
   * For every valid move:

     * Check whether the new distance is smaller.
     * Update the distance.
     * Push the new cell into the priority queue.
6. If the target cannot be reached, return `-1`.

---

## Example

### Input

```text
n = 3
knightPos = [3, 3]
targetPos = [1, 2]
```

The Knight starts at:

```text
(3, 3)
```

The target is:

```text
(1, 2)
```

A Knight can directly move:

```text
(3, 3) → (1, 2)
```

Therefore:

```text
Output: 1
```

---

## Complexity Analysis

There are `n²` cells on the board.

Each cell can have at most `8` possible moves.

### Time Complexity

Using a priority queue:

```text
O(n² log(n²))
```

which can also be written as:

```text
O(n² log n)
```

because:

```text
log(n²) = 2 log n
```

### Space Complexity

The distance matrix contains `n²` elements, and the priority queue can also contain board positions.

```text
O(n²)
```

---

## Implementation

```cpp
class Solution {
  public:
    int minStepToReachTarget(vector<int>& knightPos, vector<int>& targetPos, int n) {
        // Code here
        vector<vector<int>> dist(n,vector<int>(n,1e9));
        
        priority_queue<pair<int,pair<int,int>> , vector<pair<int,pair<int,int>>>, greater<>> pq;
        
        pq.push({0,{knightPos[0]-1,knightPos[1]-1}});
        
        dist[knightPos[0]-1][knightPos[1]-1]=0;
        
        while(!pq.empty()){
            auto top=pq.top();
            pq.pop();
            
            int val=top.first;
            int i=top.second.first;
            int j=top.second.second;
            
            if(targetPos[0]-1==i && targetPos[1]-1==j){
                return val;
            }
            
            int ni=i;
            int nj=j;
            
            ni=i-2;
            nj=j+1;
            
            if(ni>=0 && nj<n && dist[ni][nj]>dist[i][j]+1){
                dist[ni][nj]=val+1;
                pq.push({val+1,{ni,nj}});
            }
            
            ni=i-2;
            nj=j-1;
            
            if(ni>=0 && nj>=0 && dist[ni][nj]>dist[i][j]+1){
                dist[ni][nj]=val+1;
                pq.push({val+1,{ni,nj}});
            }
            
            ni=i+2;
            nj=j+1;
            
            if(ni<n && nj<n && dist[ni][nj]>dist[i][j]+1){
                dist[ni][nj]=val+1;
                pq.push({val+1,{ni,nj}});
            }
            
            ni=i+2;
            nj=j-1;
            
            if(ni<n && nj>=0 && dist[ni][nj]>dist[i][j]+1){
                dist[ni][nj]=val+1;
                pq.push({val+1,{ni,nj}});
            }
            
            ni=i-1;
            nj=j+2;
            
            if(ni>=0 && nj<n && dist[ni][nj]>dist[i][j]+1){
                dist[ni][nj]=val+1;
                pq.push({val+1,{ni,nj}});
            }
            
            ni=i-1;
            nj=j-2;
            
            if(ni>=0 && nj>=0 && dist[ni][nj]>dist[i][j]+1){
                dist[ni][nj]=val+1;
                pq.push({val+1,{ni,nj}});
            }
            
            ni=i+1;
            nj=j+2;
            
            if(ni<n && nj<n && dist[ni][nj]>dist[i][j]+1){
                dist[ni][nj]=val+1;
                pq.push({val+1,{ni,nj}});
            }
            
            ni=i+1;
            nj=j-2;
            
            if(ni<n && nj>=0 && dist[ni][nj]>dist[i][j]+1){
                dist[ni][nj]=val+1;
                pq.push({val+1,{ni,nj}});
            }
            
        }
        
        return -1;
    }
};
```

---

## Key Points

* The chessboard can be treated as a **graph**.
* Every valid Knight move represents an edge.
* Every edge has a cost of `1`.
* A `dist` matrix stores the minimum known distance to every cell.
* A **min-priority queue** processes cells according to their current distance.
* There are at most **8 moves** from every cell.
* The input positions are **1-based**, so they are converted to **0-based** indexing.
* If the target is unreachable, the function returns `-1`.

---

## Pattern Used

```text
Graph
   ↓
Shortest Path
   ↓
Weighted Graph with Edge Cost = 1
   ↓
Priority Queue
   ↓
Dijkstra-style Traversal
```

This problem is also closely related to the standard **shortest path on a grid** pattern.
