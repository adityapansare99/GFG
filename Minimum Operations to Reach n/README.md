# Minimum Operations to Reach n

## Problem Statement

Given a number `n`, find the minimum number of operations required to reach `n`, starting from `0`.

Two operations are available:

1. **Double the number:** `x = x * 2`
2. **Add one to the number:** `x = x + 1`

The goal is to reach `n` using the minimum number of operations.

## Examples

### Example 1

**Input:**
```text
n = 8
```

**Output:**
```text
4
```

**Explanation:**

The sequence of operations is:

```text
0 + 1 = 1
1 + 1 = 2
2 * 2 = 4
4 * 2 = 8
```

Total operations = `4`.

### Example 2

**Input:**
```text
n = 7
```

**Output:**
```text
5
```

**Explanation:**

One optimal sequence is:

```text
0 + 1 = 1
1 + 1 = 2
2 + 1 = 3
3 * 2 = 6
6 + 1 = 7
```

Total operations = `5`.

## Constraints

```text
1 <= n <= 10^6
```

## Approach 1: Recursion with Dynamic Programming

### Intuition

Instead of starting from `0` and finding a sequence of operations to reach `n`, we can work backward from `n`.

To reach a number `n`, consider the operations that could have produced it.

There are two possibilities:

1. If `n` is even, the previous number could be `n / 2`, obtained by doubling.
2. The previous number could be `n - 1`, obtained by adding one.

Therefore, the recurrence is:

- If `n == 0`, the answer is `0`.
- If `n` is even, consider `1 + solver(n / 2, dp)`.
- Always consider `1 + solver(n - 1, dp)`.

The minimum among the valid choices gives the answer.

### Recurrence Relation

For `n > 0`:

\[
dp[n] = 1 + dp[n-1]
\]

When `n` is even, we also consider:

\[
dp[n] = \min(dp[n], 1 + dp[n/2])
\]

Combining both choices:

\[
dp[n] =
\begin{cases}
0 & n=0\\
\min(dp[n-1],dp[n/2])+1 & n>0,\ n\text{ even}\\
dp[n-1]+1 & n>0,\ n\text{ odd}
\end{cases}
\]

### Why Dynamic Programming Is Used

Many recursive calls can reach the same value of `n`. Without memoization, these repeated calculations would waste time.

The `dp` array stores the minimum number of operations for each number already calculated.

- `dp[n] == -1`: The answer has not been calculated.
- `dp[n] != -1`: The stored answer can be reused.

This technique is called **top-down dynamic programming with memoization**.

### Code Explanation

#### 1. Base Case for Negative Values

```cpp
if(n<0){
    return 1e9;
}
```

This returns a very large value for negative numbers, representing an invalid path.

Under the given constraints and recurrence, the normal calls do not need to go below zero, but this guard prevents negative states from being treated as valid solutions.

#### 2. Base Case for Zero

```cpp
if(n==0){
    return 0;
}
```

No operations are required to reach zero when starting from zero.

#### 3. Memoization Check

```cpp
if(dp[n]!=-1){
    return dp[n];
}
```

If the result has already been calculated, return it immediately.

#### 4. Initialize the Answer

```cpp
int ans=1e9;
```

The initial value is a large number so that a valid smaller answer can replace it.

#### 5. Try the Doubling Operation in Reverse

```cpp
if(n%2==0){
    ans=min(ans,1+solver(n/2,dp));
}
```

If `n` is even, it could have been obtained by doubling `n / 2`.

The current operation contributes one step, so the candidate answer is `1 + solver(n / 2, dp)`.

#### 6. Try the Add-One Operation in Reverse

```cpp
return dp[n]=min(ans,1+solver(n-1,dp));
```

The number `n` can always be reached from `n - 1` by adding one.

The function compares this candidate with the doubling candidate, if available, and stores the minimum in `dp[n]`.

#### 7. Initialize the DP Array

```cpp
vector<int> dp(n+1,-1);
```

The array has `n + 1` elements to represent all values from `0` through `n`. Each entry initially contains `-1`.

#### 8. Start the Recursion

```cpp
return solver(n,dp);
```

The recursive function calculates the minimum number of operations required to reach the target.

## Approach 2: Greedy, Working Backward

### Intuition

The second solution uses the same backward reasoning but avoids recursion and the DP array.

At every step:

- If `n` is even, divide it by two.
- If `n` is odd, subtract one.
- Increment the operation counter after each step.
- Continue until `n` becomes zero.

Why does this work?

When working backward, subtracting one reverses the add-one operation. Dividing an even number by two reverses doubling.

For an odd number greater than one, the last forward operation cannot have been doubling, because doubling always produces an even number. Therefore, subtracting one is the necessary reverse step.

### Code Explanation

#### 1. Initialize the Counter

```cpp
int ans = 0;
```

The variable `ans` counts the total number of operations.

#### 2. Continue Until Zero

```cpp
while (n > 0) {
```

Each iteration reverses one operation. The process stops when the target becomes zero.

#### 3. Reverse Doubling

```cpp
if (n % 2 == 0) {
    n /= 2;
}
```

An even number can be reduced to half its value by reversing a doubling operation.

#### 4. Reverse Adding One

```cpp
else {
    n--;
}
```

If the number is odd, subtract one to reverse the add-one operation.

#### 5. Count the Operation

```cpp
ans++;
```

Every backward step corresponds to one forward operation, so the counter is incremented.

#### 6. Return the Result

```cpp
return ans;
```

Once `n` becomes zero, `ans` contains the minimum number of operations.

## Dry Run

Consider `n = 8`.

| Current `n` | Operation | Updated `n` | Operations |
|---:|---|---:|---:|
| 8 | Divide by 2 | 4 | 1 |
| 4 | Divide by 2 | 2 | 2 |
| 2 | Divide by 2 | 1 | 3 |
| 1 | Subtract 1 | 0 | 4 |

The loop ends when `n = 0`.

**Output: `4`**

Now consider `n = 7`.

| Current `n` | Operation | Updated `n` | Operations |
|---:|---|---:|---:|
| 7 | Subtract 1 | 6 | 1 |
| 6 | Divide by 2 | 3 | 2 |
| 3 | Subtract 1 | 2 | 3 |
| 2 | Divide by 2 | 1 | 4 |
| 1 | Subtract 1 | 0 | 5 |

**Output: `5`**

## Why the Greedy Approach Works

The backward approach is optimal because the parity of the current number determines the possible final forward operation.

- **Even target:** A doubling operation may have produced the target, so dividing by two is an optimal reverse step. For even numbers greater than zero, reversing an add-one operation would lead to an odd predecessor, which would require at least as many steps to construct as the halved predecessor.
- **Odd target:** Doubling cannot produce an odd number. Therefore, the last forward operation must have been adding one, so subtracting one is necessary.

Repeating these choices reaches zero while reversing an optimal sequence of operations.

## Complexity Analysis

### Approach 1: Recursion with Memoization

**Time Complexity: O(n)**

Each state from `0` through `n` is calculated at most once, and each state performs constant work beyond its recursive calls.

**Auxiliary Space Complexity: O(n)**

- DP array: `O(n)`
- Recursion stack: up to `O(log n)` for the chosen backward transitions, bounded by `O(n)` overall.

Therefore, the total auxiliary space is `O(n)`.

### Approach 2: Greedy

**Time Complexity: O(log n)**

Each iteration either halves `n` or subtracts one. An odd number becomes even after subtracting one, and the following step halves it. Thus, the number decreases by roughly a factor of two every one or two iterations.

**Auxiliary Space Complexity: O(1)**

Only two integer variables are used, and there is no recursion or extra array.

## Exact Code — Approach 1

```cpp
class Solution {
   private:
   int solver(int n,vector<int> &dp){
       if(n<0){
           return 1e9;
       }
       
       if(n==0){
           return 0;
       }
       
       if(dp[n]!=-1){
           return dp[n];
       }
       
       int ans=1e9;
       
       if(n%2==0){
           ans=min(ans,1+solver(n/2,dp));
       }
       
       return dp[n]=min(ans,1+solver(n-1,dp));
   }
 public:
   int minOperation(int n) {
       // code here
       vector<int> dp(n+1,-1);
       
       return solver(n,dp);
   }
};
```

## Exact Code — Approach 2

```cpp
class Solution {
public:
   int minOperation(int n) {
       int ans = 0;

       while (n > 0) {
           if (n % 2 == 0) {
               n /= 2;
           } else {
               n--;
           }
           ans++;
       }

       return ans;
   }
};
```

## Comparison of Both Approaches

| Feature | Approach 1 | Approach 2 |
|---|---|---|
| Technique | Recursion + memoization | Greedy, working backward |
| Time complexity | O(n) | O(log n) |
| Auxiliary space | O(n) | O(1) |
| Uses recursion | Yes | No |
| Uses a DP array | Yes | No |
| Recommended | Good for understanding recurrence | Best for efficiency |

## Key Takeaways

1. Work backward from `n` instead of simulating operations forward.
2. Reverse doubling by dividing an even number by two.
3. Reverse adding one by subtracting one.
4. Memoization avoids repeated recursive calculations.
5. The greedy solution avoids both recursion and the DP array.
6. **The second solution is more efficient:** `O(log n)` time and `O(1)` auxiliary space.

The central idea is to repeatedly divide even numbers by two and subtract one from odd numbers until the value reaches zero.
