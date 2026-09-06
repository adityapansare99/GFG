# Sum of Pairwise ANDs

## Problem Statement

Given an array `arr[]` of integers, find the sum of the bitwise AND of all pairs of elements where `i < j`.

For every pair `(i, j)`, calculate:

```text
arr[i] & arr[j]
```

and return the sum of all pairwise AND values.

---

## Example 1

### Input

```text
arr = [5, 10, 15]
```

### Output

```text
15
```

### Explanation

The possible pairs are:

```text
5 & 10  = 0
5 & 15  = 5
10 & 15 = 10
```

Therefore:

```text
0 + 5 + 10 = 15
```

---

## Example 2

### Input

```text
arr = [10, 20, 30, 40]
```

### Output

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

## Approach

A brute-force approach would calculate the AND for every pair of elements.

Since there can be `O(n²)` pairs and `n` can be as large as `10⁵`, this approach is too slow.

Instead, we process the numbers **bit by bit**.

The important observation is:

> A bit is set in the result of `a & b` only when that bit is set in both `a` and `b`.

Therefore, for every bit position, we count how many elements have that bit set.

---

## Algorithm

1. Initialize `ans = 0`.
2. Iterate through all bit positions from `0` to `31`.
3. For the current bit:

   * Count how many elements have the current bit set.
   * If `set_count` elements have the bit set, then the number of pairs having this bit set in both elements is:

     ```text
     set_count × (set_count - 1) / 2
     ```
4. Add the contribution of these pairs to `ans`:

   ```cpp
   ans += (set_count * (set_count - 1) / 2) * (1LL << i);
   ```
5. After processing all bits, return `ans`.

---

## Example Walkthrough

Consider:

```text
arr = [5, 10, 15]
```

Binary representation:

```text
5  = 0101
10 = 1010
15 = 1111
```

For each bit:

| Bit | Elements with Bit Set | Number of Elements |
| --: | --------------------- | -----------------: |
|   0 | 5, 15                 |                  2 |
|   1 | 10, 15                |                  2 |
|   2 | 5, 15                 |                  2 |
|   3 | 10, 15                |                  2 |

For each bit, there are:

```text
2 × 1 / 2 = 1
```

pair in which that bit is set in both elements.

The code adds the contribution of each bit using:

```cpp
(set_count * (set_count - 1) / 2) * (1LL << i)
```

The total is:

```text
1 + 2 + 4 + 8 = 15
```

---

## Why This Works

For each bit, we only need to know how many elements have that bit set.

If `set_count` elements have the same bit set, every pair among those elements will have that bit set in their bitwise AND.

Thus, we can calculate the answer bit by bit instead of explicitly checking every pair.

---

## Complexity Analysis

Let `n` be the number of elements in the array.

### Time Complexity

We check 32 bits, and for each bit we traverse the entire array:

```text
O(32 × n)
```

Since `32` is constant:

```text
O(n)
```

### Space Complexity

Only a few variables are used:

```text
O(1)
```

---

## C++ Implementation

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
            
            ans += (set_count * (set_count - 1) / 2) * (1LL << i);
        }
        
        return ans;
    }
};
```

---

## Key Takeaway

Instead of checking all possible pairs, the solution processes each bit independently:

```text
Count elements with the bit set
            ↓
Count possible pairs
            ↓
Add their contribution
            ↓
Repeat for every bit
```

This reduces the time complexity from **O(n²)** to **O(n)**.

---

## Platform

**GeeksforGeeks**

**Problem:** Sum of Pairwise ANDs

**Difficulty:** Medium
