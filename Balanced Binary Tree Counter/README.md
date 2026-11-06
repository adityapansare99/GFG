# Balanced Binary Tree Counter

**Difficulty:** Easy  
**Platform:** GeeksforGeeks  
**Topics:** Dynamic Programming, Binary Trees, Space Optimization, Modular Arithmetic

## Problem Statement

Given a height `h`, find the maximum number of distinct balanced binary trees having height exactly `h`.

A binary tree is balanced if, for every node, the heights of its left and right subtrees differ by at most `1`.

The height definitions are:

- A single-node tree has height `1`.
- An empty tree has height `0`.

Since the answer can be very large, return it modulo:

\[
MOD = 10^9+7
\]

### Examples

**Example 1**

```text
Input:  h = 1
Output: 1
```

Only one tree of height `1` exists: a single node.

**Example 2**

```text
Input:  h = 2
Output: 3
```

There are three distinct balanced trees of height `2`.

**Example 3**

```text
Input:  h = 3
Output: 15
```

There are fifteen distinct balanced trees of height `3`.

### Constraints

\[
1 \le h \le 10^6
\]

---

## Approach: Dynamic Programming with Space Optimization

### 1. Key Observation

To construct a balanced binary tree of height exactly `h`, consider the possible heights of its left and right subtrees.

The height of a tree is:

\[
1+\max(height(left),height(right))
\]

Therefore, for the current tree to have height exactly `h`, at least one of its subtrees must have height `h-1`.

Because the tree must also be balanced, the difference between the two subtree heights cannot exceed `1`.

There are exactly three possible combinations:

1. Left subtree has height `h-1`, right subtree has height `h-1`.
2. Left subtree has height `h-1`, right subtree has height `h-2`.
3. Left subtree has height `h-2`, right subtree has height `h-1`.

No other combination can produce a balanced tree of height exactly `h`.

### 2. Deriving the Recurrence

Let:

\[
dp[h] = \text{number of distinct balanced binary trees of height }h
\]

For the first combination:

- The left subtree can be selected in `dp[h-1]` ways.
- The right subtree can independently be selected in `dp[h-1]` ways.

Number of combinations:

\[
dp[h-1]\times dp[h-1]
\]

For the second combination:

- Left subtree: `dp[h-1]` possibilities.
- Right subtree: `dp[h-2]` possibilities.

Number of combinations:

\[
dp[h-1]\times dp[h-2]
\]

For the third combination, the left and right subtree heights are reversed:

\[
dp[h-2]\times dp[h-1]
\]

Adding all three possibilities gives:

\[
dp[h]=dp[h-1]^2+
dp[h-1]\times dp[h-2]+
dp[h-2]\times dp[h-1]
\]

Combining the last two terms:

\[
\boxed{dp[h]=dp[h-1]^2+2\times dp[h-1]\times dp[h-2]}
\]

Every calculation is performed modulo \(10^9+7\).

### 3. Base Cases

The problem defines an empty tree as having height `0`.

There is exactly one empty tree, so:

\[
dp[0]=1
\]

A tree of height `1` contains only one node:

\[
dp[1]=1
\]

These two base cases are sufficient to calculate all subsequent values.

### 4. Why Space Optimization Is Possible

In the recurrence, the current answer depends only on the previous two DP states:

\[
dp[h-1]\quad\text{and}\quad dp[h-2]
\]

We do not need to store the entire DP array.

Instead, maintain two variables:

- `prev1`: number of balanced trees of the previous height, initially `dp[1]`.
- `prev2`: number of balanced trees two levels behind, initially `dp[0]`.

For every height from `2` to `h`, calculate:

```cpp
long long curr = (prev1 * prev1 % mod + 2 * prev1 * prev2 % mod) % mod;
```

Then update the previous states:

```cpp
prev2 = prev1;
prev1 = curr;
```

This keeps only the two previous DP values and the current result.

---

## C++ Code

The following is the solution exactly as provided, with its logic and formatting preserved.

```cpp
class Solution {
  public:
    int countBT(int h) {
        // code here
        int mod=1e9+7;

        if(h==1){
            return 1;
        }

        long long prev1=1;
        long long prev2=1;

        for(int i=2;i<=h;i++){
            long long curr=(prev1*prev1%mod+2*prev1*prev2%mod)%mod;
            prev2=prev1;
            prev1=curr;
        }

        return prev1;
    }
};
```

---

## Dry Run

Consider:

```text
h = 3
MOD = 1000000007
```

### Initialization

The base cases are:

```text
dp[0] = 1
dp[1] = 1
```

Therefore:

```text
prev1 = 1  // dp[1]
prev2 = 1  // dp[0]
```

### Iteration 1: `i = 2`

Apply the recurrence:

\[
dp[2]=dp[1]^2+2\times dp[1]\times dp[0]
\]

\[
=1^2+2\times1\times1
\]

\[
=1+2=3
\]

Update the variables:

```text
curr  = 3
prev2 = 1
prev1 = 3
```

Thus:

\[
dp[2]=3
\]

### Iteration 2: `i = 3`

Apply the recurrence:

\[
dp[3]=dp[2]^2+2\times dp[2]\times dp[1]
\]

\[
=3^2+2\times3\times1
\]

\[
=9+6=15
\]

Update the variables:

```text
curr  = 15
prev2 = 3
prev1 = 15
```

Thus:

\[
dp[3]=15
\]

### Final Result

```text
return prev1;
```

Output:

```text
15
```

### DP Values Summary

| Height | Number of balanced binary trees |
|---:|---:|
| 0 | 1 |
| 1 | 1 |
| 2 | 3 |
| 3 | 15 |
| 4 | 315 |
| 5 | 108675 |

---

## Complexity Analysis

Let `h` be the required height.

### Time Complexity

The loop runs from `2` to `h`, performing a constant number of arithmetic operations in every iteration.

Therefore:

\[
\boxed{O(h)}
\]

### Auxiliary Space Complexity

Only three variables are used to maintain the DP states:

- `prev1`
- `prev2`
- `curr`

No DP array or recursion stack is required.

Therefore:

\[
\boxed{O(1)}
\]

This is important because the constraint allows `h` to be as large as \(10^6\).

---

## Important Implementation Details

### 1. Why are `prev1` and `prev2` initialized to 1?

They represent the two base cases:

```text
prev1 = dp[1] = 1
prev2 = dp[0] = 1
```

The empty tree is counted as one possible subtree, which is why `dp[0]` is `1`, not `0`.

### 2. Why is `long long` used?

The recurrence involves multiplication:

\[
prev1\times prev1
\]

and:

\[
2\times prev1\times prev2
\]

Using `long long` provides sufficient range for these intermediate products after modular reduction of the stored DP values.

### 3. Why take modulo during multiplication?

The answer must be returned modulo \(10^9+7\).

The code applies modulo to the products and then to their sum:

```cpp
long long curr=(prev1*prev1%mod+2*prev1*prev2%mod)%mod;
```

This keeps the DP values within the required modular range.

### 4. Why is there a special case for `h == 1`?

For height `1`, there is only one possible tree: a single node.

The code directly returns `1`. For heights greater than `1`, it starts calculating from height `2`.

---

## Final Takeaway

This problem can be solved using **Dynamic Programming with Space Optimization**.

The important observation is that a balanced binary tree of height `h` can have subtree-height combinations only of:

- `(h-1, h-1)`
- `(h-1, h-2)`
- `(h-2, h-1)`

This gives the recurrence:

\[
dp[h]=dp[h-1]^2+2\times dp[h-1]\times dp[h-2]
\]

Since only the previous two DP states are needed, the full DP array can be replaced with two variables.

**Final Complexity:**

- **Time:** \(O(h)\)
- **Auxiliary Space:** \(O(1)\)
