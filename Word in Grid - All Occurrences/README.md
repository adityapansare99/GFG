# Word in Grid - All Occurrences

## Problem Statement

Given a 2D grid `mat[][]` of size `n × m` containing characters and a string `word`, find all starting positions where the given word occurs in the grid.

The word can be formed by moving from a cell in any of the **8 possible directions**:

* Left
* Right
* Up
* Down
* Top-left diagonal
* Top-right diagonal
* Bottom-left diagonal
* Bottom-right diagonal

Once a direction is chosen, the word must be formed in a **straight line without changing direction**.

Each occurrence must start from a valid starting cell, and all unique starting positions should be returned in **lexicographically smallest order**.

---

## Examples

### Example 1

**Input:**

```text
mat[][] = {
    {a, b, a, b},
    {a, b, e, b},
    {e, b, e, b}
}

word = "abe"
```

**Output:**

```text
{{0,0}, {0,2}, {1,0}}
```

**Explanation:**

The word `"abe"` can be found from:

* `(0,0)` → right-down diagonal
* `(0,2)` → left-down diagonal
* `(1,0)` → right direction

Therefore, the starting positions are:

```text
(0,0), (0,2), (1,0)
```

---

### Example 2

**Input:**

```text
mat[][] = {
    {G,E,E,K,S,F,O,R,G,E,E,K,S},
    {G,E,E,K,S,Q,U,I,Z,G,E,E,K},
    {I,D,E,Q,A,P,R,A,C,T,I,C,E}
}

word = "GEEKS"
```

**Output:**

```text
{{0,0}, {0,8}, {1,0}}
```

**Explanation:**

The word `"GEEKS"` occurs horizontally from:

```text
(0,0)
(0,8)
(1,0)
```

Hence these starting coordinates are returned.

---

## Approach

The solution checks **every cell as a possible starting position** and then tries to find the word in **all 8 directions**.

Two nested loops are used to visit every cell:

```cpp
for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
```

For every cell `(i,j)`, two more loops generate the 8 possible directions.

```cpp
for(int x = -1; x <= 1; x++){
    for(int y = -1; y <= 1; y++){
```

Here:

* `x` represents the row movement.
* `y` represents the column movement.

The possible direction vectors are:

```text
(-1,-1)  (-1,0)  (-1,1)
( 0,-1)  ( 0,0)  ( 0,1)
( 1,-1)  ( 1,0)  ( 1,1)
```

The `(0,0)` direction does not move to another cell, but it is harmless in the implementation because a word of length greater than one cannot normally be matched using it.

---

## Direction Movement

For every starting cell, the current position is initialized as:

```cpp
int ni = i;
int nj = j;
```

The variable `z` keeps track of how many characters of the word have been matched.

```cpp
int z = 0;
```

The following loop checks the characters:

```cpp
while(z < word.size() &&
      ni >= 0 && ni < n &&
      nj < m && nj >= 0 &&
      mat[ni][nj] == word[z])
```

The loop continues only when:

1. We have not matched the complete word.
2. The current row is inside the grid.
3. The current column is inside the grid.
4. The current grid character matches the required character of the word.

---

## Moving to the Next Character

When the current character matches:

```cpp
z++;
ni += x;
nj += y;
```

The index `z` moves to the next character of the word.

The position is moved according to the selected direction:

```text
new row    = current row + x
new column = current column + y
```

For example, for the right direction:

```text
(x, y) = (0, 1)
```

For the bottom-right diagonal:

```text
(x, y) = (1, 1)
```

For the top-left diagonal:

```text
(x, y) = (-1, -1)
```

---

## Checking a Complete Occurrence

After the `while` loop finishes, we check:

```cpp
if(z == word.size()){
    ans.insert({i,j});
}
```

If `z` becomes equal to the length of the word, then the complete word was successfully matched.

The original starting position `(i,j)` is inserted into the answer.

---

## Why a Set Is Used

The code uses:

```cpp
set<pair<int,int>> ans;
```

A `set` is useful for two reasons:

### 1. Avoid Duplicate Coordinates

The same starting position may contain the word in more than one direction.

For example, a word might occur from the same cell in two different directions.

We only need to return the starting position once.

The set automatically removes duplicates.

### 2. Lexicographical Ordering

A C++ `set<pair<int,int>>` stores pairs in sorted order.

For coordinates:

```text
(row, column)
```

the rows are compared first, followed by the columns.

Therefore, the coordinates are automatically stored in **lexicographically smallest order**, as required by the problem.

---

## Converting the Set to the Result

After checking the complete grid:

```cpp
vector<vector<int>> res;

for(auto &it : ans){
    res.push_back({it.first, it.second});
}
```

Each pair from the set is converted into a vector:

```text
(row, column)
```

The final vector `res` is returned.

---

## Algorithm

1. Get the dimensions of the grid.
2. Create a set `ans` to store valid starting positions.
3. Visit every cell `(i,j)` in the grid.
4. For each cell, try all 8 possible directions.
5. Start matching the word from the current cell.
6. Continue moving in the selected direction while:

   * The position remains inside the grid.
   * The current character matches the corresponding character of the word.
7. If the complete word is matched, insert `(i,j)` into the set.
8. Convert the sorted set into a vector.
9. Return the result.

---

## Complexity Analysis

Let:

* `n` = number of rows
* `m` = number of columns
* `L` = length of the word

There are `n × m` cells.

For every cell, the algorithm checks 9 `(x,y)` combinations from `-1` to `1`. The `(0,0)` case does not create movement, while the other 8 correspond to the required directions.

For each direction, at most `L` characters are checked.

Therefore, the main searching complexity is:

```text
O(n × m × 8 × L)
```

Since `8` is a constant:

```text
O(n × m × L)
```

The set insertion can take:

```text
O(log K)
```

where `K` is the number of unique starting positions.

Thus, the overall complexity can be expressed as approximately:

```text
O(n × m × L × 8 + K log K)
```

or, ignoring constants:

```text
O(n × m × L + K log K)
```

### Space Complexity

The set stores at most `n × m` starting positions:

```text
O(n × m)
```

The result vector also stores the valid positions:

```text
O(n × m)
```

Therefore, the auxiliary/result storage is:

```text
O(n × m)
```

---

## C++ Implementation

```cpp
class Solution {
  public:
    vector<vector<int>> searchWord(vector<vector<char>> &mat, string &word) {
        // Code here
        int n = mat.size();
        int m = mat[0].size();

        set<pair<int,int>> ans;

        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){

                // Try all 8 directions
                for(int x = -1; x <= 1; x++){
                    for(int y = -1; y <= 1; y++){

                        int z = 0;
                        int ni = i;
                        int nj = j;

                        while(z < word.size() &&
                              ni >= 0 && ni < n &&
                              nj < m && nj >= 0 &&
                              mat[ni][nj] == word[z]) {

                            z++;
                            ni += x;
                            nj += y;
                        }

                        // Complete word found
                        if(z == word.size()){
                            ans.insert({i, j});
                        }
                    }
                }
            }
        }

        vector<vector<int>> res;

        for(auto &it : ans){
            res.push_back({it.first, it.second});
        }

        return res;
    }
};
```

---

## Key Idea

The core idea is:

```text
For every cell
      ↓
Try every direction
      ↓
Match the word character by character
      ↓
If complete word is found
      ↓
Store the starting position
```

The `set<pair<int,int>>` ensures that the final answer contains **unique coordinates in lexicographical order**.

### Direction Representation

The 8 directions are represented using `(x,y)`:

```text
(-1,-1)  (-1,0)  (-1,1)
( 0,-1)          ( 0,1)
( 1,-1)  ( 1,0)  ( 1,1)
```

This makes it possible to search the word uniformly in all eight directions using the same code.
