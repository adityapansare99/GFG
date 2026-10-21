# Minimum Sum Subarray

**Platform:** GeeksforGeeks  
**Difficulty:** Medium  
**Accuracy:** 72.37%  
**Points:** 4

## Problem Statement

Given an integer array `arr[]`, find the minimum sum of a non-empty contiguous subarray.

A subarray must contain at least one element, so an empty subarray is not a valid answer.

### Examples

**Example 1**

```text
Input: arr = [3, -4, 2, -3, -1, 7, -5]
Output: -6
```

**Explanation:** The subarray `[-4, 2, -3, -1]` has sum `-6`, which is the minimum possible subarray sum.

**Example 2**

```text
Input: arr = [4, -6, 3, -2, 5, -8, 2]
Output: -8
```

**Explanation:** The single-element subarray `[-8]` has the minimum sum.

**Example 3**

```text
Input: arr = [2, 6, 8, 1, 4]
Output: 1
```

**Explanation:** All elements are positive, so the smallest non-empty subarray sum is the smallest element, `1`.

### Constraints

- `1 <= arr.size() <= 10^5`
- `-10^4 <= arr[i] <= 10^4`

---

## Approach: Modified Kadane's Algorithm

This solution uses a variation of Kadane's algorithm to find the **minimum-sum non-empty subarray** in linear time.

For the usual maximum-subarray problem, a positive running sum can help extend a candidate subarray. For the minimum-subarray problem, a positive running sum cannot improve the minimum, so we discard it by resetting the running sum to zero.

The code maintains three variables:

- `sum`: the running sum of the current candidate subarray.
- `ans`: the smallest running sum seen so far, initialized to `INT_MAX`.
- `mini`: the smallest individual array element, used to handle the case where all candidate running sums remain zero.

For each element:

1. Add the element to `sum`.
2. If `sum > 0`, reset it to `0`, because a positive prefix cannot help produce a smaller future subarray sum.
3. Update `ans` with the smallest value between `ans` and `sum`.
4. Update `mini` with the smallest element seen so far.

At the end, if `ans` is still `0`, return `mini`. This handles arrays where no negative running sum was recorded, such as an all-positive array. Otherwise, return `ans`.

### C++ Solution

```cpp
class Solution {
public:
    int minSubarraySum(vector<int> &arr) {
        int n = arr.size();

        int mini = INT_MAX;
        int ans = INT_MAX;
        int sum = 0;

        for (int i = 0; i < n; i++) {
            sum += arr[i];

            if (sum > 0) {
                sum = 0;
            }

            ans = min(ans, sum);
            mini = min(arr[i], mini);
        }

        if (ans == 0) {
            return mini;
        }

        return ans;
    }
};
```

## Algorithm

1. Initialize `mini`, `ans` to `INT_MAX` and `sum` to `0`.
2. Traverse every element in the array.
3. Add the current element to `sum`.
4. If `sum` becomes positive, reset it to `0`.
5. Update `ans` with the minimum of `ans` and `sum`.
6. Update `mini` with the minimum element encountered.
7. If `ans == 0`, return `mini`; otherwise, return `ans`.

## Dry Runs

### Example 1

Input:

```text
arr = [3, -4, 2, -3, -1, 7, -5]
```

The running sum is reset whenever it becomes positive.

| Element | Running sum after reset | Minimum recorded (`ans`) |
|---:|---:|---:|
| 3 | 0 | 0 |
| -4 | -4 | -4 |
| 2 | -2 | -4 |
| -3 | -5 | -5 |
| -1 | -6 | -6 |
| 7 | 0 | -6 |
| -5 | -5 | -6 |

The minimum sum found is `-6`, from the subarray `[-4, 2, -3, -1]`.

Output:

```text
-6
```

### Example 2

Input:

```text
arr = [4, -6, 3, -2, 5, -8, 2]
```

The algorithm finds the single-element subarray `[-8]`, with sum `-8`. No other subarray has a smaller sum.

Output:

```text
-8
```

### Example 3

Input:

```text
arr = [2, 6, 8, 1, 4]
```

Every element is positive. Each positive running sum is reset to `0`, so `ans` remains `0`. The fallback returns the smallest element, `1`, ensuring the answer is a non-empty subarray sum rather than the invalid empty-subarray sum `0`.

Output:

```text
1
```

## Correctness Explanation

The running sum tracks a candidate subarray. Whenever it becomes positive, keeping that positive sum cannot make any future extension smaller than starting a new candidate at the next element, so resetting it to zero is safe for finding a negative minimum. Every negative running sum is considered when updating `ans`, allowing the algorithm to retain the smallest candidate sum found.

If no negative running sum is recorded, the array has no subarray with a negative sum. Since the required subarray must be non-empty, the smallest single element is then the minimum possible sum, which is why the algorithm returns `mini` when `ans == 0`.

Therefore, the algorithm returns the minimum sum of a non-empty contiguous subarray.

## Complexity Analysis

- **Time Complexity: `O(n)`** — each array element is processed once.
- **Auxiliary Space Complexity: `O(1)`** — only a fixed number of variables are used.

Here, `n` is the number of elements in `arr`.

## Key Takeaway

This is a minimum-sum variation of Kadane's algorithm. The important difference from the maximum-subarray version is that a **positive running sum is discarded**. Tracking the smallest individual element also ensures the algorithm correctly handles arrays containing only positive values and respects the requirement that the subarray must be non-empty.
