# Minimum Moves to Sort Permutation

## Problem Statement

Given an array `arr[]` containing every integer from `1` to `n` exactly once, sort the array in ascending order.

In one operation, you can:

* Pick any element and move it to the **beginning**, or
* Pick any element and move it to the **end**.

Return the **minimum number of operations** required to sort the array.

### Example 1

```text
Input:
arr = [2,1,3]

Output:
1
```

Move `1` to the beginning:

```text
[2,1,3]
     ↓
[1,2,3]
```

Therefore:

```text
Answer = 1
```

### Example 2

```text
Input:
arr = [4,3,1,2]

Output:
2
```

One possible sequence is:

```text
[4,3,1,2]
```

Move `3` to the end:

```text
[4,1,2,3]
```

Move `4` to the end:

```text
[1,2,3,4]
```

Therefore:

```text
Answer = 2
```

---

## Intuition

The important observation is that some elements can remain in their original positions relative to each other.

If we decide **not to move** an element, the elements that remain must eventually appear as a consecutive increasing sequence:

```text
x, x+1, x+2, ...
```

Why?

The final sorted array must be:

```text
1,2,3,4,...,n
```

The only elements that can stay untouched are a consecutive range of values that are already in the correct relative order.

All other elements can be moved either to the beginning or to the end.

Therefore:

```text
minimum moves
= n - maximum number of elements that can remain
```

---

## Finding the Longest Valid Sequence

We create a `pos` array:

```text
pos[x] = position of value x in arr
```

For example:

```text
arr = [4,3,1,2]
```

Positions are:

```text
value:  1  2  3  4
pos:    2  3  1  0
```

Now consider consecutive values:

```text
1,2,3,4
```

For `1` and `2`:

```text
pos[1] < pos[2]
2 < 3
```

So `1` and `2` are already in the correct relative order.

For `2` and `3`:

```text
pos[2] < pos[3]
3 < 1
```

This is false.

Therefore, the current consecutive sequence ends.

We reset:

```text
curr = 1
```

Then check `3` and `4`:

```text
pos[3] < pos[4]
1 < 0
```

Again false.

The longest valid sequence has length `2`:

```text
1,2
```

Therefore:

```text
minimum moves = n - 2
              = 4 - 2
              = 2
```

---

## Why Does This Work?

Suppose we have:

```text
arr = [1,2,5,3,4]
```

The positions are:

```text
pos[1] = 0
pos[2] = 1
pos[3] = 3
pos[4] = 4
pos[5] = 2
```

The sequence:

```text
1,2,3,4
```

has increasing positions:

```text
0 < 1 < 3 < 4
```

So these four values already appear in the correct relative order.

Only `5` needs to be moved.

Move `5` to the end:

```text
[1,2,5,3,4]
        ↓
[1,2,3,4,5]
```

Therefore:

```text
Answer = 1
```

---

## Dry Run

Consider:

```text
arr = [4,3,1,2]
```

### Step 1: Build Position Array

```text
pos[1] = 2
pos[2] = 3
pos[3] = 1
pos[4] = 0
```

So:

```text
value:  1  2  3  4
position:
        2  3  1  0
```

Initially:

```text
maxi = 1
curr = 1
```

### Check `1` and `2`

```text
pos[1] < pos[2]
2 < 3
```

True.

Therefore:

```text
curr = 2
maxi = 2
```

Current sequence:

```text
1,2
```

### Check `2` and `3`

```text
pos[2] < pos[3]
3 < 1
```

False.

Reset:

```text
curr = 1
```

### Check `3` and `4`

```text
pos[3] < pos[4]
1 < 0
```

False.

Again:

```text
curr = 1
```

The longest sequence has length:

```text
maxi = 2
```

Finally:

```text
answer = n - maxi
       = 4 - 2
       = 2
```

---

## Code

```cpp
class Solution {
public:
    int minMoves(vector<int>& arr) {
        int n = arr.size();

        vector<int> pos(n + 1, 0);

        for (int i = 0; i < n; i++) {
            pos[arr[i]] = i;
        }

        int maxi = 1;
        int curr = 1;

        for (int i = 1; i < n; i++) {
            if (pos[i] < pos[i + 1]) {
                curr++;
            }
            else {
                curr = 1;
            }

            maxi = max(maxi, curr);
        }

        return n - maxi;
    }
};
```

---

## Complexity

Let `n` be the size of `arr`.

### Time Complexity

Building the position array:

```text
O(n)
```

Finding the longest increasing sequence of consecutive values:

```text
O(n)
```

Therefore:

```text
Time Complexity: O(n)
```

### Space Complexity

The `pos` array contains `n + 1` elements:

```text
Space Complexity: O(n)
```

---

## Key Takeaway

The main idea is:

```text
Build position of every value
        ↓
Check consecutive values:
1 → 2 → 3 → ... → n
        ↓
If pos[i] < pos[i+1]
they are already in correct relative order
        ↓
Find the longest consecutive sequence
        ↓
Keep those elements
        ↓
Move all remaining elements
        ↓
Answer = n - longest sequence length
```

The key observation is that we do **not** need to actually perform the moves. We only need to determine the maximum number of elements that can remain untouched.

Therefore:

```text
Minimum moves = n - maximum elements that can stay
```
