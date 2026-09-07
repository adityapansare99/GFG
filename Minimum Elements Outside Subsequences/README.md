# Minimum Elements Outside Subsequences

## Problem Statement

Given an array `arr[]` of size `n`, partition its elements into:

* A **strictly increasing subsequence**
* A **strictly decreasing subsequence**

Each element can belong to at most one of these subsequences. Some elements may remain unused.

The task is to find the **minimum number of elements that cannot be included** in either subsequence.

---

## Examples

### Example 1

**Input:**

```text
arr[] = [7, 8, 1, 2, 4, 6, 3, 5, 2, 1, 8, 7]
```

**Output:**

```text
2
```

**Explanation:**

One possible strictly increasing subsequence is:

```text
[1, 2, 4, 5, 8]
```

One possible strictly decreasing subsequence is:

```text
[7, 6, 3, 2, 1]
```

The remaining elements are:

```text
8, 7
```

Therefore, the minimum number of unused elements is:

```text
2
```

---

### Example 2

**Input:**

```text
arr[] = [1, 4, 2, 3, 3, 2, 4]
```

**Output:**

```text
0
```

**Explanation:**

One possible increasing subsequence is:

```text
[1, 2, 3, 4]
```

One possible decreasing subsequence is:

```text
[4, 3, 2]
```

All elements can be included in one of the two subsequences.

Therefore:

```text
Minimum unused elements = 0
```

---

## Approach

The solution uses **Dynamic Programming with Memoization**.

Instead of directly minimizing the number of unused elements, the algorithm first finds the **maximum number of elements that can be selected** into the two subsequences.

If the maximum number of selected elements is `x`, then:

```text
minimum unused elements = n - x
```

### State Representation

The recursive function is:

```cpp
solver(i, inc, dec, arr, dp)
```

where:

* `i` = current index being considered.
* `inc` = index of the last element selected in the increasing subsequence.
* `dec` = index of the last element selected in the decreasing subsequence.

The value `-1` means that the corresponding subsequence is currently empty.

For example:

```text
solver(i, 3, 5)
```

means:

* We are currently considering index `i`.
* Index `3` is the last element of the increasing subsequence.
* Index `5` is the last element of the decreasing subsequence.

---

## Choices at Each Element

For every element `arr[i]`, there are three possible choices.

### 1. Do Not Select the Element

The element can be left unused:

```cpp
int ans = solver(i + 1, inc, dec, arr, dp);
```

The last elements of both subsequences remain unchanged.

---

### 2. Add the Element to Increasing Subsequence

The element can be added if:

```cpp
inc == -1 || arr[inc] < arr[i]
```

This ensures that the increasing subsequence remains **strictly increasing**.

The transition is:

```cpp
ans = max(ans, 1 + solver(i + 1, i, dec, arr, dp));
```

The current index `i` becomes the new last element of the increasing subsequence.

---

### 3. Add the Element to Decreasing Subsequence

The element can be added if:

```cpp
dec == -1 || arr[dec] > arr[i]
```

This ensures that the decreasing subsequence remains **strictly decreasing**.

The transition is:

```cpp
ans = max(ans, 1 + solver(i + 1, inc, i, arr, dp));
```

The current index `i` becomes the new last element of the decreasing subsequence.

---

## Recurrence

For each index `i`:

```text
Maximum selected elements =
max(
    skip arr[i],
    add arr[i] to increasing subsequence,
    add arr[i] to decreasing subsequence
)
```

More formally:

```text
solver(i, inc, dec) =
max(
    solver(i+1, inc, dec),

    1 + solver(i+1, i, dec),   if arr[inc] < arr[i],

    1 + solver(i+1, inc, i),   if arr[dec] > arr[i]
)
```

For an empty subsequence, `inc` or `dec` is `-1`, so the element can always be selected as its first element.

---

## Base Case

When all elements have been considered:

```cpp
if(i == arr.size()){
    return 0;
}
```

There are no more elements to select, so the maximum number of additional elements is `0`.

---

## Memoization

The state is determined by three values:

```text
(i, inc, dec)
```

Therefore, a 3-dimensional DP array is used:

```cpp
vector<vector<vector<int>>> dp(
    n,
    vector<vector<int>>(n+2,
    vector<int>(n+2, -1))
);
```

Since `inc` and `dec` can be `-1`, the indices are shifted by `+1` when accessing `dp`:

```cpp
dp[i][inc+1][dec+1]
```

This allows `-1` to map to index `0`.

---

## Why `max()` Is Used

The recursive function calculates the **maximum number of elements that can be included** in the two subsequences.

Therefore, for every element, we choose the option that gives the largest number of selected elements:

```cpp
ans = max(ans, ...);
```

After finding this maximum number of selected elements, the answer is calculated as:

```cpp
n - solver(0, -1, -1, arr, dp)
```

Because:

```text
Total elements = Selected elements + Unused elements
```

Therefore:

```text
Unused elements = Total elements - Selected elements
```

---

## Algorithm

1. Let `n` be the size of the array.
2. Create a 3D DP table initialized with `-1`.
3. Start recursion from index `0`.
4. Initially, both subsequences are empty, so:

   ```text
   inc = -1
   dec = -1
   ```
5. For every element:

   * Skip it.
   * Try adding it to the increasing subsequence if valid.
   * Try adding it to the decreasing subsequence if valid.
6. Store already calculated states in the DP table.
7. Find the maximum number of elements that can be selected.
8. Return:

   ```text
   n - maximum selected elements
   ```

---

## Complexity Analysis

There are three state variables:

```text
i, inc, dec
```

Each can have up to `O(n)` possible values.

Therefore, the number of states is:

```text
O(n³)
```

Each state performs only constant-time transitions.

### Time Complexity

```text
O(n³)
```

### Space Complexity

The 3D DP table requires:

```text
O(n³)
```

The recursion stack requires:

```text
O(n)
```

Therefore, the overall auxiliary space is:

```text
O(n³)
```

---

## C++ Implementation

```cpp
class Solution {
    private:
    int solver(int i, int inc, int dec, vector<int> &arr,
               vector<vector<vector<int>>> &dp) {

        if(i == arr.size()) {
            return 0;
        }

        if(dp[i][inc + 1][dec + 1] != -1) {
            return dp[i][inc + 1][dec + 1];
        }

        // Do not select arr[i]
        int ans = solver(i + 1, inc, dec, arr, dp);

        // Add arr[i] to increasing subsequence
        if(inc == -1 || arr[inc] < arr[i]) {
            ans = max(ans,
                      1 + solver(i + 1, i, dec, arr, dp));
        }

        // Add arr[i] to decreasing subsequence
        if(dec == -1 || arr[dec] > arr[i]) {
            ans = max(ans,
                      1 + solver(i + 1, inc, i, arr, dp));
        }

        return dp[i][inc + 1][dec + 1] = ans;
    }

public:
    int minCount(vector<int>& arr) {

        int n = arr.size();

        vector<vector<vector<int>>> dp(
            n,
            vector<vector<int>>(n + 2,
            vector<int>(n + 2, -1))
        );

        return n - solver(0, -1, -1, arr, dp);
    }
};
```

---

## Key Idea

The main idea is to **maximize the number of elements included in two valid subsequences**.

At every position, an element can be:

```text
        arr[i]
          |
    +-----+-----+
    |     |     |
   Skip  Inc   Dec
```

The increasing subsequence requires:

```text
previous < current
```

The decreasing subsequence requires:

```text
previous > current
```

Finally:

```text
Minimum unused elements
        =
Total elements
        -
Maximum selected elements
```

Thus, the problem is solved using **3D Dynamic Programming + Recursion + Memoization**.
