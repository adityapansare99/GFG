# Longest Subsequence with Adjacent Diff as 1

## Problem Statement

Given an array `arr[]` with `n` elements, find the length of the longest subsequence such that the absolute difference between every pair of adjacent elements is exactly `1`.

### Example 1

**Input:**

```text
arr[] = [10, 9, 4, 5, 4, 8, 6]
```

**Output:**

```text
3
```

**Explanation:**

Possible longest subsequences include:

```text
[10, 9, 8]
[4, 5, 4]
[4, 5, 6]
```

Therefore, the answer is `3`.

### Example 2

**Input:**

```text
arr[] = [1, 2, 3, 2, 3, 7, 2, 1]
```

**Output:**

```text
7
```

**Explanation:**

One longest valid subsequence is:

```text
[1, 2, 3, 2, 3, 2, 1]
```

Therefore, the answer is `7`.

---

## Approach

This solution uses **Dynamic Programming with a map**.

We process the array from **right to left**.

For every element `curr`, we need to find whether we can append a valid subsequence starting with:

* `curr + 1`
* `curr - 1`

because the absolute difference between adjacent elements must be `1`.

The map `mp` stores:

```text
mp[value] = longest valid subsequence length starting from that value
```

while processing the elements seen so far from the right side.

For the current element:

```cpp
int val = 1;
```

A single element itself forms a subsequence of length `1`.

Then we check:

```cpp
if(mp.find(next)!=mp.end()){
    val=max(val,mp[next]+1);
}
```

and

```cpp
if(mp.find(prev)!=mp.end()){
    val=max(val,mp[prev]+1);
}
```

If either `curr + 1` or `curr - 1` exists in the map, we can extend that subsequence by including the current element.

Finally:

```cpp
mp[curr] = val;
ans = max(ans, val);
```

stores the best length for the current value and updates the overall answer.

---

## Algorithm

1. Initialize `ans = 0`.
2. Create a map `mp` to store the longest valid subsequence length for each value.
3. Traverse the array from right to left.
4. For each element `curr`:

   * Set `val = 1`.
   * Check whether `curr + 1` exists in the map.
   * Check whether `curr - 1` exists in the map.
   * Extend the best subsequence found by `1`.
5. Store `val` in `mp[curr]`.
6. Update `ans` with the maximum subsequence length found.
7. Return `ans`.

---

## Complexity Analysis

Let `n` be the number of elements in the array.

### Time Complexity

Each element performs a constant number of map operations.

Since `map` in C++ is implemented as a balanced binary search tree, each operation takes `O(log n)` time.

Therefore:

```text
Time Complexity: O(n log n)
```

### Space Complexity

The map can store up to `n` distinct values.

```text
Space Complexity: O(n)
```

---

## C++ Implementation

```cpp
class Solution {
  public:
    int longestSubseq(vector<int>& arr) {
        int n = arr.size();
        map<int, int> mp;
        int ans = 0;
        
        for(int i = n - 1; i >= 0; i--) {
            int curr = arr[i];
            int next = curr + 1;
            int prev = curr - 1;
            
            int val = 1;
            
            if(mp.find(next) != mp.end()) {
                val = max(val, mp[next] + 1);
            }
            
            if(mp.find(prev) != mp.end()) {
                val = max(val, mp[prev] + 1);
            }
            
            mp[curr] = val;
            ans = max(ans, val);
        }
        
        return ans;
    }
};
```

---

## Key Idea

For every element `curr`, the next element in the subsequence must be either:

```text
curr - 1
```

or

```text
curr + 1
```

By processing the array from right to left and storing the best subsequence length for each value, we can efficiently determine the longest valid subsequence without explicitly generating all possible subsequences.

---

## Platform

**GeeksforGeeks (GFG)**

**Problem:** Longest Subsequence with Adjacent Diff as 1

**Difficulty:** Medium
