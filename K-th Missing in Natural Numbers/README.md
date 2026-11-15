# K-th Missing in Natural Numbers

## Problem Statement

Given an array `arr[]` of distinct positive integers and a positive integer `k`, consider an infinite sequence of natural numbers starting from `1`.

Remove all elements present in `arr[]` from this sequence.

Find the `k-th` smallest number in the remaining sequence.

**Note:** The solution must run in `O(1)` auxiliary space.

### Examples

**Example 1:**

- **Input:** `arr[] = [1, 9, 5, 2], k = 6`
- **Output:** `10`
- **Explanation:**

  After removing `[1, 2, 5, 9]` from the natural numbers, the remaining sequence is:

  `3, 4, 6, 7, 8, 10, 11, ...`

  The 6th missing number is `10`.

**Example 2:**

- **Input:** `arr[] = [1, 2, 3, 4], k = 1`
- **Output:** `5`
- **Explanation:**

  After removing `[1, 2, 3, 4]`, the remaining sequence is:

  `5, 6, 7, ...`

  The 1st missing number is `5`.

### Constraints

- `1 <= arr.size() <= 10^5`
- `1 <= arr[i], k <= 10^6`
- All elements of `arr` are distinct.

---

## Approach: Sorting and Updating K

The main idea is to sort the array and update `k` whenever an element is less than or equal to the current value of `k`.

### Key Observation

Initially, `k` represents the answer if no numbers are removed.

Whenever an element from the array is less than or equal to the current `k`, that element is one of the numbers that would otherwise have appeared in the remaining sequence.

Therefore, we need to increase `k` by `1` to account for that removed number.

Sorting the array ensures that we process the removed numbers in increasing order.

### Algorithm

1. Sort the array in ascending order.
2. Traverse the sorted array.
3. For each element:
   - If `arr[i] <= k`, increment `k` by `1`.
   - Otherwise, stop the traversal because all remaining elements are greater than the current `k`.
4. Return the updated value of `k`.

---

## C++ Solution

```cpp
class Solution {
public:
    int findKthSmall(vector<int>& arr, int k) {
        // code here
        sort(arr.begin(),arr.end());

        for(int i=0;i<arr.size();i++){
            if(arr[i]<=k){
                k++;
            }

            else{
                break;
            }
        }

        return k;
    }
};
```

---

## Dry Run

Consider the following input:

```text
arr = [1, 9, 5, 2]
k = 6
```

**Step 1: Sort the array**

```text
arr = [1, 2, 5, 9]
k = 6
```

**Step 2: Traverse the sorted array**

| Index | arr[i] | Current k | Condition | Updated k |
|---|---:|---:|---|---:|
| 0 | 1 | 6 | 1 <= 6 | 7 |
| 1 | 2 | 7 | 2 <= 7 | 8 |
| 2 | 5 | 8 | 5 <= 8 | 9 |
| 3 | 9 | 9 | 9 <= 9 | 10 |

**Step 3: Return the answer**

```text
Output = 10
```

The missing sequence is:

```text
3, 4, 6, 7, 8, 10, 11, ...
```

Therefore, the 6th missing number is `10`.

---

## Complexity Analysis

Let `n` be the number of elements in the array.

### Time Complexity: O(n log n)

- Sorting the array takes `O(n log n)` time.
- Traversing the sorted array takes `O(n)` time in the worst case.

Therefore, the overall time complexity is:

\[
\boxed{O(n\log n)}
\]

### Auxiliary Space Complexity: O(1)

- The algorithm uses only a fixed number of additional variables.
- No extra array or data structure is created.
- The sorting operation is performed directly on the input array.

The solution uses `O(1)` auxiliary space under the usual in-place sorting complexity convention.

---

## Key Takeaways

- Sorting helps process removed numbers in increasing order.
- Every removed number less than or equal to the current answer shifts the answer forward by one.
- Updating `k` dynamically avoids explicitly generating the natural number sequence.
- The approach satisfies the `O(1)` auxiliary-space requirement.

**Final Complexity:**
- **Time:** `O(n log n)`
- **Auxiliary Space:** `O(1)`