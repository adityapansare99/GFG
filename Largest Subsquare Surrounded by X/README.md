# Largest Subsquare Surrounded by X

## Problem Statement

Given a square matrix `mat[][]` of size `n × n`, where every cell contains either `'X'` or `'O'`, find the size of the largest square submatrix whose **boundary is completely surrounded by `'X'`**.

The cells inside the square can contain either `'X'` or `'O'`. Only the four sides of the square need to contain `'X'`.

Return the side length of the largest such square submatrix.

### Important Points

* The square must have `'X'` on its **top boundary**.
* The square must have `'X'` on its **bottom boundary**.
* The square must have `'X'` on its **left boundary**.
* The square must have `'X'` on its **right boundary**.
* The cells strictly inside the square can be either `'X'` or `'O'`.
* A square of size `1` is valid if its only cell is `'X'`.
* If there is no `'X'` in the matrix, the answer is `0`.

---

## Examples

### Example 1

#### Input

```text
mat[][] = [
    [X, X, X, O],
    [X, O, X, X],
    [X, X, X, O],
    [X, O, X, X]
]
```

#### Output

```text
3
```

#### Explanation

The square from `(0,0)` to `(2,2)` is:

```text
X X X
X O X
X X X
```

Its boundary consists entirely of `'X'`.

The inside cell can be `'O'`, because only the boundary needs to be surrounded by `'X'`.

Therefore, the largest valid square has side length:

```text
3
```

---

### Example 2

#### Input

```text
mat[][] = [
    [X, X],
    [X, X]
]
```

#### Output

```text
2
```

#### Explanation

The entire matrix is surrounded by `'X'`.

```text
X X
X X
```

Therefore, the largest valid square has side length `2`.

---

## Constraints

```text
1 ≤ n, mat.size(), mat[i].size() ≤ 1000
```

Each cell contains either:

```text
'X' or 'O'
```

---

# Approach

The main challenge is checking whether the **four boundaries** of a square contain only `'X'`.

Checking every cell on all four boundaries separately for every possible square can be expensive.

To make these checks efficient, we precompute two DP tables:

1. `row`
2. `col`

These tables allow us to determine the number of consecutive `'X'` cells in a particular direction in `O(1)` time.

---

# DP Tables

## 1. `row` Table

For every cell `(i,j)`, `row[i][j]` stores the number of consecutive `'X'` cells starting from `(i,j)` and extending towards the **right**.

For example:

```text
X X X O
X O X X
X X X O
```

For the first row:

```text
X X X O
```

the `row` values are:

```text
3 2 1 0
```

because:

* Starting at the first `X`, there are `3` consecutive `X`s.
* Starting at the second `X`, there are `2`.
* Starting at the third `X`, there is `1`.
* `O` gives `0`.

We calculate this table by traversing each row from **right to left**.

```cpp
for(int i=0;i<n;i++){
    int c=0;
    for(int j=n-1;j>=0;j--){
        if(mat[i][j]=='X'){
            c++;
        }
        else{
            c=0;
        }

        row[i][j]=c;
    }
}
```

---

# 2. `col` Table

For every cell `(i,j)`, `col[i][j]` stores the number of consecutive `'X'` cells starting from `(i,j)` and extending **downwards**.

For example:

```text
X
X
X
O
```

The corresponding `col` values are:

```text
3
2
1
0
```

We calculate this table by traversing each column from **bottom to top**.

```cpp
for(int j=0;j<n;j++){
    int c=0;
    for(int i=n-1;i>=0;i--){
        if(mat[i][j]=='X'){
            c++;
        }
        else{
            c=0;
        }

        col[i][j]=c;
    }
}
```

---

# Key Observation

Suppose `(i,j)` is the **top-left corner** of a candidate square with side length `size`.

The square looks like:

```text
(i,j) -------------------- (i,right)
  |                            |
  |                            |
  |                            |
  |                            |
  |                            |
(i,bottom) -------------- (bottom,right)
```

where:

```cpp
right = j + size - 1;
bottom = i + size - 1;
```

For this square to be valid, all four boundaries must contain `'X'`.

---

# Checking the Four Boundaries

## Top Boundary

The top boundary starts at `(i,j)` and extends right.

We already know the number of consecutive `'X'` cells using:

```cpp
row[i][j]
```

Therefore:

```cpp
row[i][j] >= size
```

ensures that the complete top boundary contains `'X'`.

---

## Left Boundary

The left boundary starts at `(i,j)` and extends downward.

We use:

```cpp
col[i][j]
```

Therefore:

```cpp
col[i][j] >= size
```

ensures that the complete left boundary contains `'X'`.

---

## Bottom Boundary

The bottom-left corner of the square is:

```cpp
(bottom,j)
```

The bottom boundary extends towards the right.

Therefore, we check:

```cpp
row[bottom][j] >= size
```

If this is true, the complete bottom boundary contains `'X'`.

---

## Right Boundary

The top-right corner of the square is:

```cpp
(i,right)
```

The right boundary extends downward.

Therefore, we check:

```cpp
col[i][right] >= size
```

If this is true, the complete right boundary contains `'X'`.

---

# Complete Boundary Condition

Therefore, a square starting at `(i,j)` with side length `size` is valid when:

```cpp
row[bottom][j] >= size
&&
col[i][right] >= size
```

The top and left boundaries have already been used to determine the maximum possible candidate size:

```cpp
int size=min(col[i][j],row[i][j]);
```

So the remaining two boundaries are checked using:

```cpp
if(row[bottom][j]>=size && col[i][right]>=size)
```

---

# Why Start With `min(row, col)`?

For a square of side length `size` starting at `(i,j)`:

* We need at least `size` consecutive `'X'` cells to the right.
* We need at least `size` consecutive `'X'` cells downward.

Therefore, the maximum possible size based on the top-left corner is:

```cpp
min(row[i][j],col[i][j])
```

For example, if:

```text
row[i][j] = 7
col[i][j] = 5
```

then we cannot construct a square larger than `5`.

Hence:

```cpp
size = min(row[i][j],col[i][j]);
```

---

# Why Use `while(size > ans)`?

Suppose we have already found a valid square of size `5`.

There is no reason to check a square of size `5` or smaller if it cannot improve the answer.

Therefore, the code only checks:

```cpp
while(size>ans)
```

This helps skip unnecessary checks.

Whenever a valid square is found:

```cpp
ans=size;
break;
```

The current candidate becomes the best answer for that starting position.

---

# Step-by-Step Algorithm

```text
1. Let n be the size of the matrix.

2. Create two n × n DP tables:
      row
      col

3. Calculate row:
      Traverse every row from right to left.
      Count consecutive X characters.
      Store the count in row[i][j].

4. Calculate col:
      Traverse every column from bottom to top.
      Count consecutive X characters.
      Store the count in col[i][j].

5. Initialize:
      ans = 0

6. Consider every cell (i,j) as the top-left corner.

7. Calculate the maximum possible square size:
      size = min(row[i][j], col[i][j])

8. While size is greater than ans:
      right = j + size - 1
      bottom = i + size - 1

9. Check:
      row[bottom][j] >= size
      col[i][right] >= size

10. If both conditions are true:
      update ans = size
      stop checking smaller sizes for this position.

11. Return ans.
```

---

# Dry Run

Consider:

```text
X X X O
X O X X
X X X O
X O X X
```

For the top-left cell `(0,0)`:

```text
row[0][0] = 3
col[0][0] = 3
```

Therefore:

```text
size = min(3,3)
     = 3
```

Now:

```text
right = 0 + 3 - 1
      = 2

bottom = 0 + 3 - 1
       = 2
```

We check the bottom boundary:

```cpp
row[2][0] >= 3
```

which is true because:

```text
X X X
```

exists in row `2`.

Then we check the right boundary:

```cpp
col[0][2] >= 3
```

which is also true because:

```text
X
X
X
```

exists in column `2`.

Therefore, the square is valid:

```text
X X X
X O X
X X X
```

and:

```text
ans = 3
```

---

# Visual Representation

For a square of size `3`:

```text
      j                    right
      ↓                       ↓
      X  X  X
      X  O  X
      X  X  X
      ↑     ↑
      |     |
      |     right boundary
      |
      left boundary
```

The top and bottom rows are completely `'X'`.

The left and right columns are completely `'X'`.

The center cell can be either `'X'` or `'O'`.

---

# Correctness

The algorithm correctly identifies the largest square surrounded by `'X'`.

### 1. Correct Top Boundary

`row[i][j]` stores the number of consecutive `'X'` cells extending right from `(i,j)`.

Therefore, using:

```cpp
row[i][j]
```

ensures that the top boundary can contain the required number of `'X'` cells.

### 2. Correct Left Boundary

`col[i][j]` stores the number of consecutive `'X'` cells extending downward from `(i,j)`.

Therefore, it ensures that the left boundary can contain the required number of `'X'` cells.

### 3. Correct Bottom Boundary

For a square ending at row `bottom`, the bottom boundary starts at `(bottom,j)`.

The condition:

```cpp
row[bottom][j] >= size
```

guarantees that all cells on the bottom boundary are `'X'`.

### 4. Correct Right Boundary

For a square ending at column `right`, the right boundary starts at `(i,right)`.

The condition:

```cpp
col[i][right] >= size
```

guarantees that all cells on the right boundary are `'X'`.

### 5. Largest Valid Square

Every cell is considered as a possible top-left corner, and possible square sizes are tested while they can improve `ans`.

Therefore, the largest valid square found is returned.

---

# Complexity Analysis

Let `n` be the dimension of the square matrix.

## Time Complexity

### Building `row`

Every matrix cell is visited once:

```text
O(n²)
```

### Building `col`

Again, every matrix cell is visited once:

```text
O(n²)
```

### Searching for the largest square

For every cell, the code may test multiple possible sizes.

In the worst case:

```text
O(n³)
```

Therefore, the overall worst-case time complexity is:

```text
O(n³)
```

## Space Complexity

Two `n × n` matrices are maintained:

```text
row → O(n²)
col → O(n²)
```

Therefore:

```text
O(n²)
```

additional space is used.

---

# Complexity Summary

| Operation         |         Complexity |
| ----------------- | -----------------: |
| Build `row`       |            `O(n²)` |
| Build `col`       |            `O(n²)` |
| Search candidates | `O(n³)` worst case |
| **Total Time**    |          **O(n³)** |
| **Extra Space**   |          **O(n²)** |

---

# Edge Cases

## 1. Matrix Contains Only `'O'`

Example:

```text
O O
O O
```

There is no valid square.

Output:

```text
0
```

---

## 2. Matrix Contains a Single `'X'`

Example:

```text
X
```

A square of size `1` is valid.

Output:

```text
1
```

---

## 3. Matrix Contains a Single `'O'`

Example:

```text
O
```

No valid square exists.

Output:

```text
0
```

---

## 4. Entire Matrix Contains `'X'`

Example:

```text
X X X
X X X
X X X
```

The entire matrix is surrounded by `'X'`.

Output:

```text
3
```

---

## 5. Interior Contains `'O'`

Example:

```text
X X X
X O X
X X X
```

The square is still valid because only its boundary needs to contain `'X'`.

Output:

```text
3
```

---

# Key Takeaways

* The problem only requires the **boundary** of the square to contain `'X'`.
* The interior cells do not matter.
* `row[i][j]` stores consecutive `'X'` cells towards the right.
* `col[i][j]` stores consecutive `'X'` cells towards the bottom.
* `min(row[i][j], col[i][j])` gives the maximum possible size from a top-left corner.
* The bottom and right boundaries are verified using the precomputed DP tables.
* The solution uses `O(n²)` extra space.
* The worst-case time complexity is `O(n³)`.

---

# Code

The following is the original solution code:

```cpp
cclass Solution {
  public:
    int largestSubsquare(vector<vector<char>> &mat) {
        // code here
        int n=mat.size();
        vector<vector<int>> row(n,vector<int>(n,0));
        vector<vector<int>> col(n,vector<int>(n,0));
        
        bool present=false;
        
        for(int i=0;i<n;i++){
            int c=0;
            for(int j=n-1;j>=0;j--){
                if(mat[i][j]=='X'){
                    c++;
                    present=true;
                }
                
                else{
                    c=0;
                }
                
                row[i][j]=c;
            }
        }
        
        for(int j=0;j<n;j++){
            int c=0;
            for(int i=n-1;i>=0;i--){
                if(mat[i][j]=='X'){
                    c++;
                }
                
                else{
                    c=0;
                }
                
                col[i][j]=c;
            }
        }
        
        int ans=0;
        
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                int size=min(col[i][j],row[i][j]);
                
                while(size>ans){
                    int right=j+size-1;
                    int bottom=i+size-1;
                    
                    if(row[bottom][j]>=size && col[i][right]>=size){
                        ans=size;
                        break;
                    }
                    
                    size--;
                }
            }
        }
        
        return ans;
    }
};
```

---

# Summary

The solution uses **directional dynamic programming** to efficiently determine how many consecutive `'X'` cells exist to the right and downward from each position.

For every possible top-left corner, the maximum candidate square is determined using the precomputed values. The remaining two boundaries are then checked in constant time.

This avoids repeatedly scanning the entire boundary of every candidate square and provides an efficient way to solve the problem for large matrices.
