# At Least K Occurrences

## Problem Statement

Given an array `arr[]` and an integer `k`, find the first element that occurs at least `k` times in the array.

If multiple elements satisfy the condition, return the element whose `k-th` occurrence appears earliest in the array.

If no element occurs at least `k` times, return `-1`.

## Examples

**Example 1:**

- **Input:** `arr[] = [1, 7, 4, 3, 4, 8, 7], k = 2`
- **Output:** `4`
- **Explanation:** Both `7` and `4` occur twice. However, `4` reaches its second occurrence before `7`, so the answer is `4`.

**Example 2:**

- **Input:** `arr[] = [3, 1, 3, 4, 5, 1, 3, 3, 5, 4], k = 3`
- **Output:** `3`
- **Explanation:** The element `3` is the only element that occurs at least 3 times in the array.

**Example 3:**

- **Input:** `arr[] = [10, 8, 2], k = 10`
- **Output:** `-1`
- **Explanation:** No element occurs at least 10 times in the array.

## Constraints

- `1 ≤ arr.size() ≤ 10^6`
- `0 ≤ arr[i] ≤ 10^6`
- `1 ≤ k ≤ 10^3`

## Approach: Hashing / Frequency Counting

The problem can be solved by maintaining the frequency of each element while traversing the array from left to right.

A `map` is used to store the frequency of every element encountered so far.

### Algorithm

1. Initialize a map `mp` to store the frequency of each element.
2. Traverse the array from left to right.
3. For every element:
   - Increment its frequency in the map.
   - Check whether its frequency has reached at least `k`.
4. If the frequency becomes equal to or greater than `k`, immediately return that element.
5. If the complete array is traversed without finding such an element, return `-1`.

### C++ Code

```cpp
class Solution {\
  public:\
    int firstElementKTime(vector<int>& arr, int k) {\
        // code here\
        int n=arr.size();\
        map<int,int> mp;\
        \
        for(int i=0;i<n;i++){\
            mp[arr[i]]++;\
            \
            if(mp[arr[i]]>=k){\
                return arr[i];\
            }\
        }\
        \
        return -1;\
    }\
};
```

## Dry Run

**Input:**

```text
arr = [1, 7, 4, 3, 4, 8, 7]
k = 2
```

| Index | Element | Frequency | Condition |
|---|---:|---:|---|
| 0 | 1 | 1 | Not reached |
| 1 | 7 | 1 | Not reached |
| 2 | 4 | 1 | Not reached |
| 3 | 3 | 1 | Not reached |
| 4 | 4 | 2 | Reached k, return 4 |

**Output:**

```text
4
```

The traversal stops as soon as element `4` reaches its second occurrence. Although `7` also occurs twice, its second occurrence appears later.

## Complexity Analysis

Let `n` be the number of elements in the array and `d` be the number of distinct elements encountered.

### Time Complexity: O(n log d)

- The array is traversed from left to right, taking at most `O(n)` iterations.
- Each map insertion or frequency update takes `O(log d)` time.
- Therefore, the overall time complexity is **O(n log d)**.

### Space Complexity: O(d)

- The map stores the frequencies of distinct elements.
- In the worst case, all elements are distinct, so the map stores `n` entries.
- Therefore, the space complexity is **O(d)**, with **O(n)** as the worst case.

## Key Takeaways

- A frequency map is useful for counting occurrences of elements.
- Traversing from left to right preserves the order of occurrences.
- Returning immediately when the frequency reaches `k` guarantees that the element whose `k-th` occurrence appears earliest is selected.
- There is no need to traverse the remaining elements after finding the answer.

## Conclusion

The solution efficiently uses a map to track element frequencies during a single left-to-right traversal. By returning immediately when an element reaches the required frequency, it finds the correct answer without requiring a separate sorting or frequency-processing pass.