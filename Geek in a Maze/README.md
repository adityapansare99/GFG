# Geek in a Maze

## Problem Statement

Given a maze `mat[][]` of size `n × m`, each cell is either:

* `.` representing an empty cell
* `#` representing an obstacle

Geek starts from cell `(r, c)`.

Geek can move:

```text
Up
Down
Left
Right
```

to an adjacent non-obstacle cell inside the maze.

There is a limit on vertical movements:

* At most `u` **upward** moves
* At most `d` **downward** moves
* There is no limit on left and right moves

Return the number of **distinct empty cells** that Geek can visit.

If the starting cell is an obstacle, return `0`.

---

## Intuition

The difficulty is that simply marking a cell as visited is **not enough**.

Suppose we reach the same cell through two different paths:

```text
Path 1 → remaining upward moves = 1
Path 2 → remaining upward moves = 3
```

The second state is better because Geek has more upward moves remaining and can potentially visit more cells.

Therefore, for every cell we store the **maximum remaining upward moves** with which we can reach that cell.

This is what the `visi` array represents:

```text
visi[i][j] = maximum remaining upward moves
             when reaching cell (i, j)
```

Initially:

```text
visi[r][c] = u
```

because Geek starts with all `u` upward moves available.

---

## Why Do We Only Need to Store Remaining Upward Moves?

At first, it may seem that we need both:

```text
remaining upward moves
remaining downward moves
```

for every cell.

But for a fixed cell `(i, j)`, the difference between the number of upward and downward moves is determined by how far the cell is from the starting row.

Suppose:

```text
upUsed = number of upward moves
downUsed = number of downward moves
```

Starting from row `r`, to reach row `i`:

```text
i = r - upUsed + downUsed
```

Therefore:

```text
downUsed - upUsed = i - r
```

So once `upUsed` is known, `downUsed` is also determined for that cell.

Because of this, keeping the best remaining upward moves is sufficient.

---

## Movement Logic

We maintain three arrays:

```text
visi[i][j]
up[i][j]
down[i][j]
```

For the current cell:

```text
up[i][j]
```

represents the remaining upward moves.

Similarly:

```text
down[i][j]
```

represents the remaining downward moves.

`visi[i][j]` is used to determine whether the new state gives the cell a better amount of remaining upward moves.

---

## Case 1: Move Left

Moving left does not consume an upward or downward move.

Therefore:

```text
new up = current up
new down = current down
```

We can update the neighboring cell if the new remaining upward moves are better:

```cpp
if(nj >= 0 &&
   visi[ni][nj] < up[i][j] &&
   mat[ni][nj] != '#')
```

Then:

```text
visi[ni][nj] = up[i][j]
up[ni][nj] = up[i][j]
down[ni][nj] = down[i][j]
```

---

## Case 2: Move Right

Moving right also does not consume any vertical move.

So:

```text
new up = current up
new down = current down
```

The logic is the same as moving left.

---

## Case 3: Move Up

When Geek moves upward, one upward move is consumed.

Therefore:

```text
new up = current up - 1
```

and:

```text
new down = current down
```

The move is possible only when:

```text
up[i][j] > 0
```

Your code checks:

```cpp
if(ni >= 0 &&
   visi[ni][nj] < up[i][j] - 1 &&
   up[i][j] > 0 &&
   mat[ni][nj] != '#')
```

Then:

```text
up[ni][nj] = up[i][j] - 1
down[ni][nj] = down[i][j]
```

---

## Case 4: Move Down

When Geek moves downward, one downward move is consumed.

Therefore:

```text
new up = current up
new down = current down - 1
```

The move is possible only when:

```text
down[i][j] > 0
```

Your code does:

```cpp
if(ni < n &&
   visi[ni][nj] < up[i][j] &&
   down[i][j] > 0 &&
   mat[ni][nj] != '#')
```

Then:

```text
down[ni][nj] = down[i][j] - 1
up[ni][nj] = up[i][j]
```

Notice that `visi` is updated with the unchanged `up[i][j]`.

---

## Why Left and Right Are Important

Left and right moves are unlimited.

For example, Geek can move:

```text
Left → Right → Left → Right
```

as many times as necessary, as long as the cells are not obstacles.

Therefore, these moves do not change:

```text
up
down
```

This is why horizontal movement can be used to explore many cells without consuming the vertical movement limits.

---

## Dry Run

Consider:

```text
mat =
[
    ['.', '.', '.'],
    ['.', '#', '.'],
    ['#', '.', '.']
]

r = 1
c = 0
u = 1
d = 1
```

The maze is:

```text
. . .
. # .
# . .
```

Geek starts at:

```text
(1,0)
```

with:

```text
up = 1
down = 1
```

Initially:

```text
visi[1][0] = 1
```

---

### Move Up

From:

```text
(1,0)
```

Geek can move to:

```text
(0,0)
```

One upward move is consumed:

```text
up = 0
down = 1
```

So:

```text
visi[0][0] = 0
```

---

### Move Right

From `(0,0)`:

```text
(0,0) → (0,1)
```

No vertical move is consumed.

Therefore:

```text
up = 0
down = 1
```

---

### Move Right Again

```text
(0,1) → (0,2)
```

Again:

```text
up = 0
down = 1
```

---

### Move Down

From:

```text
(0,2)
```

Geek can move to:

```text
(1,2)
```

One downward move is consumed:

```text
up = 0
down = 0
```

Therefore `(1,2)` is reachable.

The reachable cells are:

```text
(1,0)
(0,0)
(0,1)
(0,2)
(1,2)
```

So:

```text
Answer = 5
```

---

## Another Example

Consider:

```text
mat =
[
    ['.', '.', '.'],
    ['.', '#', '.'],
    ['.', '.', '.']
]

r = 2
c = 1
u = 1
d = 0
```

Geek starts at:

```text
(2,1)
```

Since:

```text
d = 0
```

Geek cannot move downward.

But Geek can move left and right freely.

From the starting cell:

```text
(2,1)
```

Geek can reach:

```text
(2,0)
(2,2)
```

From `(2,0)` Geek can move upward:

```text
(2,0) → (1,0)
```

This consumes the only upward move.

Similarly:

```text
(2,2) → (1,2)
```

can be reached.

Therefore the reachable cells are:

```text
(2,1)
(2,0)
(2,2)
(1,0)
(1,2)
```

So:

```text
Answer = 5
```

---

## Handling Obstacles

Before moving to any neighboring cell, the code checks:

```cpp
mat[ni][nj] != '#'
```

Therefore, an obstacle can never be added to the queue.

For example:

```text
. # .
```

The middle cell cannot be visited.

---

## Code

```cpp
class Solution {
public:
    int numberOfCells(int r, int c, int u, int d, vector<vector<char>> &mat) {
        int n = mat.size();
        int m = mat[0].size();

        if(mat[r][c] == '#'){
            return 0;
        }

        vector<vector<int>> visi(n, vector<int>(m, -1));
        vector<vector<int>> up(n, vector<int>(m, 0));
        vector<vector<int>> down(n, vector<int>(m, 0));

        queue<pair<int,int>> q;

        q.push({r,c});

        visi[r][c] = u;
        up[r][c] = u;
        down[r][c] = d;

        while(!q.empty()){
            auto top = q.front();
            q.pop();

            int i = top.first;
            int j = top.second;

            int ni = i;
            int nj = j - 1;

            if(nj >= 0 &&
               visi[ni][nj] < up[i][j] &&
               mat[ni][nj] != '#'){

                visi[ni][nj] = up[i][j];
                up[ni][nj] = up[i][j];
                down[ni][nj] = down[i][j];

                q.push({ni,nj});
            }

            ni = i;
            nj = j + 1;

            if(nj < m &&
               visi[ni][nj] < up[i][j] &&
               mat[ni][nj] != '#'){

                visi[ni][nj] = up[i][j];
                up[ni][nj] = up[i][j];
                down[ni][nj] = down[i][j];

                q.push({ni,nj});
            }

            ni = i - 1;
            nj = j;

            if(ni >= 0 &&
               visi[ni][nj] < up[i][j] - 1 &&
               up[i][j] > 0 &&
               mat[ni][nj] != '#'){

                up[ni][nj] = up[i][j] - 1;
                visi[ni][nj] = up[i][j] - 1;
                down[ni][nj] = down[i][j];

                q.push({ni,nj});
            }

            ni = i + 1;
            nj = j;

            if(ni < n &&
               visi[ni][nj] < up[i][j] &&
               down[i][j] > 0 &&
               mat[ni][nj] != '#'){

                down[ni][nj] = down[i][j] - 1;
                visi[ni][nj] = up[i][j];
                up[ni][nj] = up[i][j];

                q.push({ni,nj});
            }
        }

        int ans = 0;

        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(visi[i][j] != -1){
                    ans++;
                }
            }
        }

        return ans;
    }
};
```

---

## Complexity

Let:

```text
N = number of rows
M = number of columns
```

There are at most:

```text
N × M
```

cells.

The algorithm stores three `N × M` arrays:

```text
visi
up
down
```

and a queue of cells.

The intended traversal processes reachable cells and checks four neighbors for each cell.

Therefore:

```text
Time Complexity: O(N × M)
Space Complexity: O(N × M)
```

The important point is that we do **not** create a state for every possible combination of:

```text
cell × remaining_up × remaining_down
```

Instead, for each cell we retain the best reachable state using the remaining upward moves. This keeps the state space proportional to the number of cells.

---

## Key Takeaway

The main idea is to treat the problem as a **state-based grid traversal**.

For every cell, we care about:

```text
How many upward moves are still available?
```

because the number of downward moves is determined by the cell's row relative to the starting row.

The process is:

```text
Start from (r,c)
        ↓
Store u upward moves and d downward moves
        ↓
Explore all four directions
        ↓
Left / Right → no vertical move consumed
        ↓
Up → consume one upward move
        ↓
Down → consume one downward move
        ↓
If a cell can be reached with more remaining upward moves,
update it
        ↓
Count all cells that were reached
```

The crucial condition in the solution is:

```cpp
visi[ni][nj] < new_remaining_up
```

It means:

> Visit this cell again only when the new path gives us a better state than the state already stored for that cell.
