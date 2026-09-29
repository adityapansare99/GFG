# Ways to Reach Origin

## Problem Statement

Geek is standing at a point `(x, y)` on a 2D grid and wants to reach the origin `(0, 0)`.

From any point, Geek can move in only two directions:

* Left: `(x, y) -> (x - 1, y)`
* Down: `(x, y) -> (x, y - 1)`

Find the total number of distinct paths for Geek to reach `(0, 0)` from `(x, y)`.

Since the answer can be very large, return it modulo `10^9 + 7`.

### Example 1

```text
Input: x = 3, y = 0
Output: 1
```

Explanation:

The only possible path is:

```text
(3, 0) -> (2, 0) -> (1, 0) -> (0, 0)
```

Since `y = 0`, there is no option to move down.

### Example 2

```text
Input: x = 3, y = 6
Output: 84
```

There are a total of `84` distinct paths from `(3, 6)` to `(0, 0)` using only left and down moves.

### Constraints

```text
0 ≤ x, y ≤ 500
```

---

# Approach 1: Top-Down Dynamic Programming

## Intuition

At every point `(x, y)`, Geek has two possible moves:

1. Move left to `(x - 1, y)`
2. Move down to `(x, y - 1)`

Therefore:

```text
ways(x, y) = ways(x - 1, y) + ways(x, y - 1)
```

The base case is:

```text
ways(0, 0) = 1
```

If either coordinate becomes negative, that path is invalid:

```text
x < 0 || y < 0
```

To avoid calculating the same state multiple times, a `dp` table is used to store already calculated results.

This is a **top-down DP with memoization** approach.

## Algorithm

1. Create a `dp` table initialized with `-1`.
2. Start the recursive function from `(x, y)`.
3. If `x < 0` or `y < 0`, return `0`.
4. If `(x, y) == (0, 0)`, return `1`.
5. If the current state is already calculated, return its stored value.
6. Calculate:

   ```text
   ways(x, y) = ways(x - 1, y) + ways(x, y - 1)
   ```
7. Store the result in `dp`.
8. Return the answer modulo `10^9 + 7`.

## Code

```cpp
class Solution {
    int mod=1e9+7;
    
    int solver(int x,int y,vector<vector<int>> &dp){
        if(x<0 || y<0){
            return 0;
        }
        
        if(x==0 && y==0){
            return 1;
        }
        
        if(dp[x][y]!=-1){
            return dp[x][y];
        }
        
        return dp[x][y]=((solver(x-1,y,dp)%mod)+(solver(x,y-1,dp))%mod)%mod;
    }
  public:
    int ways(int x, int y) {
        // code here
        vector<vector<int>> dp(x+1,vector<int>(y+1,-1));
        return solver(x,y,dp);
    }
};
```

## Complexity

Let the number of states be `(x + 1) * (y + 1)`.

* **Time Complexity:** `O(x * y)`
* **Space Complexity:** `O(x * y)` for the DP table
* **Recursion Stack:** `O(x + y)`

---

# Approach 2: Bottom-Up Dynamic Programming

## Intuition

Instead of using recursion, we can build the DP table iteratively.

We use:

```text
dp[i][j]
```

to represent the number of ways to reach that position.

For every state, the answer comes from the top and left states:

```text
dp[i][j] = dp[i-1][j] + dp[i][j-1]
```

The starting state is initialized using:

```text
dp[1][1] = 1
```

The table is shifted by one position so that the boundaries can be handled without special cases for `x = 0` and `y = 0`.

## Algorithm

1. Create a 2D DP table initialized with `0`.
2. Set:

   ```text
   dp[1][1] = 1
   ```
3. Iterate through all required states.
4. For each state, calculate the number of paths using the top and left states.
5. Take modulo `10^9 + 7`.
6. Return `dp[x+1][y+1]`.

## Code

```cpp
class Solution {
    int mod=1e9+7;
  public:
    int ways(int x, int y) {
        // code here
        vector<vector<int>> dp(x+2,vector<int>(y+2,0));
        dp[1][1]=1;
        
        for(int i=1;i<=x+1;i++){
            for(int j=1;j<=y+1;j++){
                if(i==1 && j==1){
                    continue;
                }
                
                dp[i][j]=((dp[i-1][j]%mod)+(dp[i][j-1]%mod))%mod;
            }
        }
        
        return dp[x+1][y+1];
    }
};
```

## Complexity

* **Time Complexity:** `O(x * y)`
* **Space Complexity:** `O(x * y)`

---

# Approach 3: Space Optimized Dynamic Programming

## Intuition

In the previous approach, to calculate the current state, we only need:

* The value from the previous row
* The value from the current row

Therefore, we do not need to store the complete 2D DP table.

We use two arrays:

```text
prev
curr
```

`prev` stores the previous row, while `curr` stores the current row.

After completing one row:

```text
prev = curr
```

This reduces the space complexity from `O(x * y)` to `O(y)`.

## Algorithm

1. Create a `prev` array.
2. Initialize the starting position.
3. Iterate through each row.
4. Create a `curr` array for the current row.
5. Calculate each state using:

   ```text
   curr[j] = prev[j] + curr[j-1]
   ```
6. Replace `prev` with `curr`.
7. Return the final value.

## Code

```cpp
class Solution {
    int mod=1e9+7;
  public:
    int ways(int x, int y) {
        // code here
        vector<int> prev(y+2,0);
        prev[1]=1;
        
        for(int i=1;i<=x+1;i++){
            vector<int> curr(y+2,0);
            if(i==1){
                curr[1]=1;
            }
            
            for(int j=1;j<=y+1;j++){
                if(i==1 && j==1){
                    continue;
                }
                
                curr[j]=((prev[j]%mod)+(curr[j-1]%mod))%mod;
            }
            
            prev=curr;
        }
        
        return prev[y+1];
    }
};
```

## Complexity

* **Time Complexity:** `O(x * y)`
* **Space Complexity:** `O(y)`

---

# Comparison of Approaches

| Approach   | Technique                 |       Time |      Space |
| ---------- | ------------------------- | ---------: | ---------: |
| Approach 1 | Top-Down DP + Memoization | `O(x * y)` | `O(x * y)` |
| Approach 2 | Bottom-Up 2D DP           | `O(x * y)` | `O(x * y)` |
| Approach 3 | Space Optimized DP        | `O(x * y)` |     `O(y)` |

---

# Key Concept

The main recurrence used in all three approaches is:

```text
ways(x, y) = ways(x - 1, y) + ways(x, y - 1)
```

This works because every valid path reaching `(x, y)` must come from exactly one of two directions:

```text
(x - 1, y)
```

or

```text
(x, y - 1)
```

The three implementations differ only in how the previously calculated states are stored and accessed.

---

# Final Takeaway

This problem is a classic **Grid Dynamic Programming** problem.

The progression of the three solutions is:

```text
Recursion
    ↓
Recursion + Memoization
    ↓
Bottom-Up DP
    ↓
Space Optimized DP
```

The final approach provides the same `O(x * y)` time complexity while reducing the auxiliary DP space to `O(y)`.
