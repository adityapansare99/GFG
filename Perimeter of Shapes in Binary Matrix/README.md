# Perimeter of Shapes in Binary Matrix

## Problem

Given a binary matrix `mat[][]` of size `n × m`, where every cell contains either `0` or `1`, find the total perimeter of all figures formed by cells containing `1`.

Two cells are adjacent if they share a common side.

A single `1` cell contributes 4 to the perimeter. If two `1` cells share a side, that shared side is not part of the outer perimeter.

---

## Important Note About Example 2

The example

```text
1 0
1 1
```

has three `1` cells and two shared sides.

Therefore:

```text
3 × 4 - 2 × 2 = 8
```

So the stated output `8` is correct.

The explanation saying that there are only two adjacent cells and the perimeter is `6` is inconsistent with the matrix. The correct perimeter is **8**.

---

## Approach

For every cell containing `1`, initially add all four sides:

```cpp
ans += 4;
```

Then check its four possible neighbors:

- up
- down
- left
- right

If a neighboring cell is also `1`, the two cells share a side. That side must be removed from the perimeter, so subtract `1`.

Because the matrix is binary, this can be written directly as:

```cpp
ans -= mat[neighbor];
```

If the neighbor is `0`, zero is subtracted. If it is `1`, one is subtracted.

---

## Why the Approach Works

Suppose we have:

```text
1 1
```

Initially:

```text
4 + 4 = 8
```

The cells share one side. That side is counted once for each cell, so it must be removed twice:

```text
8 - 2 = 6
```

Thus the perimeter is:

```text
6
```

In the implementation, each cell sees the other cell as a neighboring `1`, so the shared side is automatically subtracted twice.

---

## Four Neighbor Checks

For `mat[i][j] == 1`:

### Up

```cpp
if(i>0){
    ans -= mat[i-1][j];
}
```

### Down

```cpp
if(i<n-1){
    ans -= mat[i+1][j];
}
```

### Left

```cpp
if(j>0){
    ans -= mat[i][j-1];
}
```

### Right

```cpp
if(j<m-1){
    ans -= mat[i][j+1];
}
```

The boundary checks are necessary to avoid accessing outside the matrix.

---

## Example 1

Input:

```text
0 1 0 0 0
1 1 1 0 0
1 0 0 0 0
```

There are five `1` cells.

Initial contribution:

```text
5 × 4 = 20
```

Shared sides:

```text
(0,1) - (1,1)
(1,0) - (1,1)
(1,1) - (1,2)
(1,0) - (2,0)
```

There are four shared sides.

Each shared side is counted twice initially:

```text
20 - 4 × 2 = 12
```

Therefore:

```text
Output = 12
```

---

## Example 2

Input:

```text
1 0
1 1
```

There are three cells containing `1`.

Initial contribution:

```text
3 × 4 = 12
```

Shared sides:

```text
(0,0) - (1,0)
(1,0) - (1,1)
```

There are two shared sides.

Therefore:

```text
12 - 2 × 2 = 8
```

Output:

```text
8
```

---

## Step-by-Step Code Explanation

### 1. Get dimensions

```cpp
int n=mat.size();
int m=mat[0].size();
```

`n` is the number of rows and `m` is the number of columns.

### 2. Initialize the answer

```cpp
int ans=0;
```

### 3. Visit every cell

```cpp
for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
```

### 4. Process only `1` cells

```cpp
if(mat[i][j]==1){
```

A `0` cell contributes nothing.

### 5. Add four sides

```cpp
ans+=4;
```

### 6. Remove shared sides

For every valid neighbor, subtract its value.

For example:

```cpp
if(i>0){
    ans-=mat[i-1][j];
}
```

Since the neighbor is either `0` or `1`, this removes exactly one side when the neighbor is another shape cell.

---

## Correctness Proof

Consider every cell containing `1`.

The algorithm first adds four sides for that cell. Thus every possible side is initially counted.

For each of its four neighboring positions:

- If the neighbor is outside the matrix, there is no neighboring cell, so the boundary side remains counted.
- If the neighbor is `0`, the side is exposed, so it remains counted.
- If the neighbor is `1`, the side is shared and is not part of the outer perimeter, so the algorithm subtracts one.

Every shared side is encountered from both adjacent `1` cells. Hence it is removed twice, once for each cell that initially counted it.

Therefore, all exposed sides are counted exactly once and all internal shared sides are removed completely.

Thus `ans` is exactly the total perimeter.

---

## Mathematical Interpretation

Let:

```text
k = number of cells containing 1
e = number of pairs of adjacent 1-cells
```

Every `1` contributes four sides:

```text
4k
```

Every adjacent pair shares one side, and that shared side was counted twice.

Therefore:

```text
perimeter = 4k - 2e
```

The implementation computes this implicitly by checking all four neighbors of every `1`.

---

## Dry Run

For:

```text
mat =
[
    [1,0],
    [1,1]
]
```

Start:

```text
ans = 0
```

### Cell `(0,0)`

It is `1`:

```text
ans = 4
```

Its down neighbor is `1`:

```text
ans = 3
```

Its other valid neighbor is `0`.

### Cell `(0,1)`

It is `0`, so nothing changes.

### Cell `(1,0)`

It is `1`:

```text
ans = 7
```

It shares a side with `(0,0)`:

```text
ans = 6
```

It also shares a side with `(1,1)`:

```text
ans = 5
```

### Cell `(1,1)`

It is `1`:

```text
ans = 9
```

It shares a side with `(1,0)`:

```text
ans = 8
```

Final:

```text
ans = 8
```

---

## Edge Cases

### Single cell

```text
1
```

Answer:

```text
4
```

### Single zero

```text
0
```

Answer:

```text
0
```

### Horizontal pair

```text
1 1
```

Answer:

```text
6
```

### Vertical pair

```text
1
1
```

Answer:

```text
6
```

### L-shape

```text
1 0
1 1
```

Answer:

```text
8
```

### Completely filled 2 × 2 matrix

```text
1 1
1 1
```

Initial:

```text
4 × 4 = 16
```

There are four shared sides:

```text
16 - 4 × 2 = 8
```

Answer:

```text
8
```

---

## Complexity Analysis

Let the matrix have `n` rows and `m` columns.

Every cell is visited once, and at most four neighboring cells are checked.

### Time Complexity

```text
O(n × m)
```

### Auxiliary Space Complexity

```text
O(1)
```

No additional matrix or data structure is created.

The input matrix itself occupies `O(n × m)` space, but that is not additional space used by the algorithm.

---

## Final Code

```cpp
class Solution {
  public:
    int findPerimeter(vector<vector<int>> &mat) {
        int n=mat.size();
        int m=mat[0].size();

        int ans=0;

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(mat[i][j]==1){
                    ans+=4;

                    if(i>0){
                        ans-=mat[i-1][j];
                    }

                    if(i<n-1){
                        ans-=mat[i+1][j];
                    }

                    if(j>0){
                        ans-=mat[i][j-1];
                    }

                    if(j<m-1){
                        ans-=mat[i][j+1];
                    }
                }
            }
        }

        return ans;
    }
};
```

---

## Key Takeaways

1. Every `1` initially contributes `4`.
2. Every neighboring `1` represents one shared side.
3. A shared side is counted from both cells, so it is subtracted twice overall.
4. `ans -= mat[neighbor]` works because every matrix value is either `0` or `1`.
5. Boundary checks prevent out-of-bounds access.
6. The matrix does not need to be copied or modified.
7. Time complexity is `O(n × m)`.
8. Auxiliary space complexity is `O(1)`.
9. For the second supplied example, the correct answer is `8`; the statement's explanation claiming `6` is incorrect.
