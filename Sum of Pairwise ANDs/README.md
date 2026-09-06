# Sum of Pairwise ANDs

## Problem Statement

Given an array `arr[]` of integers, calculate the sum of the bitwise AND of all pairs of elements where the first index is less than the second index.

For every pair `(i, j)` where:

```text
i < j
```

calculate:

```text
arr[i] & arr[j]
```

and return the sum of all these values.

---

## Example 1

**Input:**

```text
arr = [5, 10, 15]
```

**Output:**

```text
15
```

**Explanation:**

The valid pairs are:

```text
(5, 10)  → 5 & 10  = 0
(5, 15)  → 5 & 15  = 5
(10, 15) → 10 & 15 = 10
```

Therefore:

```text
0 + 5 + 10 = 15
```

---

## Example 2

**Input:**

```text
arr = [10, 20, 30, 40]
```

**Output:**

```text
46
```

The pairwise AND values are:

```text
10 & 20 = 0
10 & 30 = 10
10 & 40 = 8
20 & 30 = 20
20 & 40 = 0
30 & 40 = 8
```

Therefore:

```text
0 + 10 + 8 + 20 + 0 + 8 = 46
```

---

# Approach

A direct approach would calculate the AND for every pair, which would take `O(n²)` time.

Since `n` can be as large as `10⁵`, this is too slow.

Instead, we use a **bitwise counting approach**.

The key observation is that the AND operation works independently for every bit.

A bit `i` will be set in:

```text
arr[x] & arr[y]
```

only when **bit `i` is set in both elements**.

Therefore, for every bit position, we count how many array elements have that bit set.

---

## Bit Contribution

Suppose bit `i` is set in `set_count` elements.

Any two of these elements will have bit `i` set in their AND.

The number of such pairs is:

```text
C(set_count, 2)
```

which is:

```text
set_count * (set_count - 1) / 2
```

Each such pair contributes:

```text
2^i
```

to the final answer.

Therefore, the contribution of bit `i` is:

```text
(set_count * (set_count - 1) / 2) * 2^i
```

We add this contribution for every bit.

---

# Algorithm

1. Initialize `ans = 0`.
2. Iterate through every bit position from `0` to `31`.
3. For the current bit:

   * Count how many elements have this bit set.
4. Calculate the number of pairs having this bit set in both elements:

   ```text
   set_count * (set_count - 1) / 2
   ```
5. Multiply the number of pairs by the value of the bit:

   ```text
   1LL << i
   ```
6. Add this contribution to `ans`.
7. Return `ans`.

---

# Example Walkthrough

Consider:

```text
arr = [5, 10, 15]
```

Their binary representations are:

```text
5  = 0101
10 = 1010
15 = 1111
```

### Bit 0

Bit 0 is set in:

```text
5, 15
```

So:

```text
set_count = 2
```

Number of pairs:

```text
2 * 1 / 2 = 1
```

Contribution:

```text
1 × 1 = 1
```

### Bit 1

Bit 1 is set in:

```text
10, 15
```

Contribution:

```text
1 × 2 = 2
```

### Bit 2

Bit 2 is set in:

```text
5, 15
```

Contribution:

```text
1 × 4 = 4
```

### Bit 3

Bit 3 is set in:

```text
10, 15
```

Contribution:

```text
1 × 8 = 8
```

Total:

```text
1 + 2 + 4 + 8 = 15
```

Therefore, the answer is:

```text
15
```

---

# Why This Works

Bitwise AND sets a particular bit only when that bit is set in **both** elements.

So instead of explicitly calculating:

```text
arr[i] & arr[j]
```

for every pair, we independently calculate the contribution of every bit.

For each bit:

```text
Number of contributing pairs
        ×
Value of the bit
```

gives the total contribution of that bit to the final answer.

Adding the contributions of all bits gives the sum of the pairwise ANDs.

---

# Complexity Analysis

Let `n` be the number of elements in the array.

The maximum value of `arr[i]` is `10⁸`, so only a small number of bits are actually needed. The implementation checks 32 bit positions.

### Time Complexity

For every bit, we traverse the complete array:

```text
O(32 × n)
```

Since `32` is constant:

```text
Time Complexity: O(n)
```

### Space Complexity

Only a few variables are used:

```text
Space Complexity: O(1)
```

---

# C++ Implementation

```cpp
class Solution {
public:
    long long pairAndSum(vector<int> &arr) {
        int n = arr.size();

        long long ans = 0;

        for(int i = 0; i <= 31; i++) {
            long long set_count = 0;

            for(auto &it : arr) {
                if((it & (1LL << i)) != 0) {
                    set_count++;
                }
            }

            ans += ((set_count * (set_count - 1) / 2) * (1LL << i));
        }

        return ans;
    }
};
```

---

# Key Idea

The important observation is:

> **For a bit to appear in the AND of a pair, that bit must be set in both elements.**

So, if a bit is set in `c` elements, it contributes to:

```text
C(c, 2)
```

pairs.

The final answer is therefore obtained by summing the contribution of every bit independently.

---

## Platform

**GeeksforGeeks (GFG)**

**Problem:** Sum of Pairwise ANDs

**Difficulty:** Medium
