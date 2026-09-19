# Min Cost To Make Two Strings Identical

## Problem Statement

Given two strings **s1** and **s2**, and two integers **costS1** and **costS2**, where costS1 is the cost of deleting one character from s1 and costS2 is the cost of deleting one character from s2, find the minimum cost required to make the two strings identical.

You can delete any number of characters from either string, but the order of the remaining characters must be preserved.

## Examples

### Example 1

```text
Input: s1 = "abcd", s2 = "acdb", costS1 = 10, costS2 = 20
Output: 30
Explanation: Delete 'b' from both strings to obtain "acd". The total cost is 10 + 20 = 30.
```

### Example 2

```text
Input: s1 = "ef", s2 = "gh", costS1 = 10, costS2 = 20
Output: 60
Explanation: The two strings have no common characters, so delete all characters from both strings. The total cost is (2 × 10) + (2 × 20) = 60.
```

## Constraints

- 1 ≤ s1.size(), s2.size() ≤ 1000
- 1 ≤ costS1, costS2 ≤ 10^5

---

# Approach 1: Recursive DP + Memoization

## Idea

We process the strings from the end using two indices `i` and `j`.

For every pair of positions:

- If `s1[i] == s2[j]`, both characters can be kept, so move diagonally to `i-1, j-1`.
- If the characters are different, we have two choices:
  - Delete `s1[i]` with cost `cost1`.
  - Delete `s2[j]` with cost `cost2`.
- Take the minimum of these two choices.

The result for every `(i, j)` is stored in `dp` so that the same state is not calculated again.

## Base Cases

If both strings are completely processed:

```cpp
if(i<0 && j<0){
    return 0;
}
```

If only `s1` is completely processed, all remaining characters of `s2` must be deleted:

```cpp
if(i<0){
    return (j+1)*cost2;
}
```

If only `s2` is completely processed, all remaining characters of `s1` must be deleted:

```cpp
if(j<0){
    return (i+1)*cost1;
}
```

## Code

```cpp
class Solution {
    private:
    int solver(string &s1,string &s2,int i,int j,int cost1,int cost2,vector<vector<int>> &dp){
        if(i<0 && j<0){
            return 0;
        }

        if(i<0){
            return (j+1)*cost2;
        }

        if(j<0){
            return (i+1)*cost1;
        }

        if(dp[i][j]!=-1){
            return dp[i][j];
        }

        if(s1[i]==s2[j]){
            return dp[i][j]=solver(s1,s2,i-1,j-1,cost1,cost2,dp);
        }

        return dp[i][j]=min(cost1+solver(s1,s2,i-1,j,cost1,cost2,dp),cost2+solver(s1,s2,i,j-1,cost1,cost2,dp));
    }
  public:
    int findMinCost(string &s1, string &s2, int costS1, int costS2) {
        // code here
        int n=s1.size();
        int m=s2.size();

        vector<vector<int>> dp(n,vector<int>(m,-1));

        return solver(s1,s2,n-1,m-1,costS1,costS2,dp);
    }
};
```

## Complexity

- **Time:** `O(n × m)`
- **Space:** `O(n × m)` for the DP table + `O(n + m)` recursion stack

---

# Approach 2: Bottom-Up Tabulation

## Idea

The recursive solution can be converted into an iterative DP.

Define:

```text
dp[i][j] = minimum cost to make the first i characters of s1
           and the first j characters of s2 identical
```

### Initialization

If `s1` is empty, all `j` characters of `s2` must be deleted:

```cpp
dp[0][j]=j*costS2;
```

If `s2` is empty, all `i` characters of `s1` must be deleted:

```cpp
dp[i][0]=i*costS1;
```

### Transition

If the current characters are equal:

```cpp
dp[i][j]=dp[i-1][j-1];
```

No deletion is required.

Otherwise, either delete the current character from `s1` or delete the current character from `s2`:

```cpp
dp[i][j]=min(costS1+dp[i-1][j],costS2+dp[i][j-1]);
```

## Code

```cpp
class Solution {
  public:
    int findMinCost(string &s1, string &s2, int costS1, int costS2) {
        // code here
        int n=s1.size();
        int m=s2.size();

        vector<vector<int>> dp(n+1,vector<int>(m+1,1e9));
        dp[0][0]=0;

        for(int j=0;j<=m;j++){
            dp[0][j]=j*costS2;
        }

        for(int i=0;i<=n;i++){
            dp[i][0]=i*costS1;
        }

        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(s1[i-1]==s2[j-1]){
                    dp[i][j]=dp[i-1][j-1];
                }

                else{
                    dp[i][j]=min(costS1+dp[i-1][j],costS2+dp[i][j-1]);
                }
            }
        }

        return dp[n][m];
    }
};
```

## Complexity

- **Time:** `O(n × m)`
- **Space:** `O(n × m)`

---

# Approach 3: Space Optimized DP

## Idea

In the tabulation approach, `dp[i][j]` only needs:

- `dp[i-1][j]`
- `dp[i][j-1]`
- `dp[i-1][j-1]`

Therefore, instead of storing the complete 2D table, we only store the previous row and the current row.

The `prev` vector stores the previous row, while `curr` stores the current row.

For equal characters:

```cpp
curr[j]=prev[j-1];
```

For different characters:

```cpp
curr[j]=min(costS1+prev[j],costS2+curr[j-1]);
```

After completing a row:

```cpp
prev=curr;
```

## Code

```cpp
class Solution {
  public:
    int findMinCost(string &s1, string &s2, int costS1, int costS2) {
        // code here
        int n=s1.size();
        int m=s2.size();

        vector<int> prev(m+1,1e9);
        prev[0]=0;

        for(int j=0;j<=m;j++){
            prev[j]=j*costS2;
        }

        for(int i=1;i<=n;i++){
            vector<int> curr(m+1,1e9);
            curr[0]=i*costS1;

            for(int j=1;j<=m;j++){
                if(s1[i-1]==s2[j-1]){
                    curr[j]=prev[j-1];
                }

                else{
                    curr[j]=min(costS1+prev[j],costS2+curr[j-1]);
                }
            }

            prev=curr;
        }

        return prev[m];
    }
};
```

## Complexity

- **Time:** `O(n × m)`
- **Space:** `O(m)`

Here `m` is the size of `s2`.

---

# Comparison of All Three Approaches

| Approach | Technique | Time | Space |
|---|---|---:|---:|
| 1 | Recursion + Memoization | `O(n × m)` | `O(n × m)` + recursion stack |
| 2 | Bottom-Up Tabulation | `O(n × m)` | `O(n × m)` |
| 3 | Space Optimized DP | `O(n × m)` | `O(m)` |

## Key Observation

All three approaches use the same DP recurrence.

The main difference is how the DP states are stored:

```text
Recursive DP
     ↓
Memoization
     ↓
2D Tabulation
     ↓
1D Space Optimized DP
```

The space-optimized version keeps only the information required from the previous row and current row, reducing the auxiliary space from `O(n × m)` to `O(m)`.

## Final Takeaway

The problem is a variation of **Longest Common Subsequence (LCS)** where instead of maximizing the common subsequence length, we minimize the deletion cost.

When two characters are equal, keeping them is always optimal for the current DP state because there is no deletion cost.

When they are different, we choose the cheaper result between deleting from `s1` and deleting from `s2`.

The three implementations demonstrate the progression from:

1. **Top-down DP**
2. **Bottom-up DP**
3. **Space-optimized DP**
