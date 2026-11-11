# Any Duplicate Within K Distance

## Problem Statement

Given an array of integers `arr[]` and an integer `k`, check whether there exist two distinct indices `i` and `j` such that:

- `arr[i] == arr[j]`
- The absolute difference between their indices is at most `k`, i.e., `|i - j| ≤ k`.

Return `true` if such a pair exists; otherwise, return `false`.

## Examples

**Example 1:**

- **Input:** `arr[] = [1, 5, 4, 5, 1], k = 3`
- **Output:** `true`
- **Explanation:** The element `5` occurs at indices 1 and 3. Their distance is `|3 - 1| = 2`, which is less than or equal to `k`.

**Example 2:**

- **Input:** `arr[] = [10, 2, 3, 4, 10, 5], k = 3`
- **Output:** `false`
- **Explanation:** The element `10` occurs at indices 0 and 4. Their distance is `|4 - 0| = 4`, which is greater than `k`. Hence, no duplicate exists within the given distance.

**Example 3:**

- **Input:** `arr[] = [5, 1, 3, 2, 4], k = 3`
- **Output:** `false`
- **Explanation:** All elements are distinct, so no duplicate exists.

## Constraints

- `2 ≤ arr.size() ≤ 10^5`
- `1 ≤ arr[i] ≤ 10^5`
- `1 ≤ k < arr.size()`

## Approach: Map (Last Seen Index)

We can solve this problem efficiently by maintaining the most recent index of every element using a map.

Instead of comparing every pair of indices, we store the last occurrence of each element and check the distance whenever that element appears again.

### Algorithm

1. Initialize a map `mp` to store each element and its most recent index.
2. Traverse the array from left to right.
3. For every element `arr[i]`:
   - Check whether the element already exists in the map.
   - If it exists, calculate the distance between the current index and its previously stored index.
   - If the distance is less than or equal to `k`, return `true`.
   - Otherwise, update its last seen index to the current index.
4. If the complete array is traversed without finding a valid pair, return `false`.

### Why Store the Last Seen Index?

For every element, only its most recent occurrence matters.

If the distance between the current index and the most recent occurrence is greater than `k`, all earlier occurrences are even farther away. Therefore, checking the most recent index is sufficient.

## C++ Code

```cpp
class Solution {\
  public:\
    bool checkWithinK(vector<int>& arr, int k) {\
        // code here\
        int n=arr.size();\
        map<int,int> mp;\
        \
        for(int i=0;i<n;i++){\
            if(mp.find(arr[i])!=mp.end()){\
                if(i-mp[arr[i]]<=k){\
                    return true;\
                }\
            }\
            \
            mp[arr[i]]=i;\
        }\
        \
        return false;\
    }\
};
```

## Dry Run

**Input:**

```text
arr = [1, 5, 4, 5, 1]
k = 3
```

| Index | Element | Previous Index | Distance | Result |
|---:|---:|---:|---:|---|
| 0 | 1 | Not found | - | Store 1 → 0 |
| 1 | 5 | Not found | - | Store 5 → 1 |
| 2 | 4 | Not found | - | Store 4 → 2 |
| 3 | 5 | 1 | 2 | 2 ≤ 3, return true |

**Output:**

```text
true
```

At index `3`, the element `5` has already appeared at index `1`. Their distance is `2`, which satisfies the given condition.

The function immediately returns `true`.

## Complexity Analysis

Let `n` be the number of elements in the array and `d` be the number of distinct elements stored in the map.

### Time Complexity: O(n log d)

- The array is traversed at most once, requiring `O(n)` iterations.
- Each map lookup and insertion/update takes `O(log d)` time.
- Therefore, the overall time complexity is **O(n log d)**.

### Space Complexity: O(d)

- The map stores the most recent index of each distinct element.
- In the worst case, all elements are distinct, resulting in `O(n)` space.

Therefore, the space complexity is **O(d)**, with **O(n)** as the worst case.

## Key Takeaways

- A map can efficiently maintain the last seen index of each element.
- Only the most recent occurrence needs to be checked.
- Left-to-right traversal allows us to calculate the distance without checking every pair.
- Returning immediately when a valid duplicate is found avoids unnecessary iterations.

## Conclusion

The solution uses a map to track the most recent occurrence of each element. Whenever a duplicate is encountered, its distance from the previous occurrence is checked against `k`.

This approach avoids the brute-force comparison of all pairs and solves the problem in **O(n log n)** time in the worst case.