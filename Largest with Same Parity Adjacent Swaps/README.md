# Largest with Same Parity Adjacent Swaps

## Problem Statement

Given an array `arr[]`, you are allowed to swap two adjacent elements, `arr[i]` and `arr[i + 1]`, only if their sum is even.

Find the lexicographically largest array that can be obtained by performing this operation any number of times, including zero times.

An array `X` is lexicographically larger than another array `Y` if, at the first position where they differ, `X` has the larger element.

### Examples

**Example 1**

**Input:**
```text
arr[] = [1, 3, 5]
```

**Output:**
```text
[5, 3, 1]
```

**Explanation:**

All elements have odd parity, so any adjacent pair has an even sum and can be swapped. We can rearrange the elements to obtain the lexicographically largest array in descending order.

**Example 2**

**Input:**
```text
arr[] = [1, 3, 4, 2]
```

**Output:**
```text
[3, 1, 4, 2]
```

**Explanation:**

The elements `1` and `3` are both odd, while `4` and `2` are both even. Elements with the same parity can be swapped when they become adjacent, but an odd element cannot be swapped with an even element because their sum is odd. Therefore, the two parity groups remain in their original positions, and each group can be sorted in descending order.

### Constraints

- `1 <= arr.size() <= 10^5`
- `0 <= arr[i] <= 10^5`
- The array may contain duplicate elements.

---

## Approach: Parity-Based Segmentation and Sorting

### Key Observation

Two integers have an even sum if and only if they have the same parity.

- Even + Even = Even
- Odd + Odd = Even
- Even + Odd = Odd

Therefore, two adjacent elements can be swapped only when both are even or both are odd.

This means that elements with different parity cannot cross each other. The original sequence of odd and even positions determines the boundaries of the segments that can be rearranged independently.

### Algorithm

1. Create a copy of the input array named `ans` so that the original array remains unchanged.
2. Initialize `n` with the array size and `start = 0` to mark the beginning of the current segment.
3. Traverse the array using the index `i` from `0` to `n - 2`.
4. Compare the parity of the adjacent elements `arr[i]` and `arr[i + 1]`.
5. If their parities differ:
   - Sort the corresponding segment of `ans`, from `start` to `i`, in descending order.
   - Update `start` to `i + 1`, marking the beginning of the next segment.
6. After the traversal, sort the remaining segment from `start` to the end of `ans` in descending order.
7. Return `ans`.

### Why Sort in Descending Order?

The objective is to obtain the lexicographically largest array. Within each segment, all elements have the same parity and can be rearranged through valid adjacent swaps.

Placing the largest element first, followed by the next largest, maximizes the array lexicographically within that segment.

---

## C++ Solution

The following code is reproduced exactly as provided.

```cpp
class Solution {
  public:
    vector<int> lexicographicallyLargest(vector<int> &arr) {
        // code here
        vector<int> ans=arr;
        int n=arr.size();
        int start=0;
        
        for(int i=0;i<n-1;i++){
            if(arr[i]%2!=arr[i+1]%2){
                sort(ans.begin()+start,ans.begin()+i+1,greater<int>());
                start=i+1;
            }
        }
        
        sort(ans.begin()+start,ans.end(),greater<int>());
        
        return ans;
    }
};
```

---

## Dry Run

Consider the input:

```text
arr = [1, 3, 4, 2]
```

Initially:

```text
ans = [1, 3, 4, 2]
start = 0
n = 4
```

| Index `i` | Adjacent elements | Parity comparison | Action |
|---|---|---|---|
| 0 | 1, 3 | Same parity | Continue |
| 1 | 3, 4 | Different parity | Sort segment `[0, 1]` in descending order |
| 2 | 4, 2 | Same parity | Continue |

After detecting the parity boundary between `3` and `4`:

```text
Segment 1: [1, 3] -> [3, 1]
start = 2
```

After the loop, sort the remaining segment:

```text
Segment 2: [4, 2] -> [4, 2]
```

Final array:

```text
[3, 1, 4, 2]
```

**Output:**
```text
[3, 1, 4, 2]
```

---

## Correctness Explanation

The solution relies on the fact that a valid swap is possible only between two elements of the same parity.

**1. Parity order is preserved**

An odd element cannot cross an even element through valid swaps. Consequently, the sequence of parity groups remains unchanged.

**2. Each segment can be rearranged independently**

Within a maximal contiguous segment of elements having the same parity, every adjacent pair can be swapped. Thus, the elements of that segment can be rearranged into any order.

**3. Descending order maximizes each segment**

Sorting each segment in descending order places its largest element first, then its second-largest element, and so on. This produces the lexicographically largest arrangement for that segment.

**4. The complete array is lexicographically largest**

Since the parity boundaries cannot be crossed, the segments must remain in their original positions. Maximizing each segment independently therefore maximizes the entire array lexicographically.

Hence, the algorithm returns the lexicographically largest array obtainable using the permitted swaps.

---

## Complexity Analysis

Let `n` be the number of elements in the array.

### Time Complexity: O(n log n)

The algorithm traverses the array once, taking O(n) time. It also sorts each contiguous segment of elements having the same parity.

In the worst case, all elements have the same parity, so the entire array must be sorted.

Therefore, the overall time complexity is **O(n log n)**.

### Auxiliary Space Complexity: O(n)

The algorithm creates a copy of the input array named `ans`, which requires O(n) additional space.

Therefore, the auxiliary space complexity is **O(n)**.
---

## Edge Cases

1. **Single element:** The array contains no adjacent pair to examine. The result is the original array.
2. **All elements have the same parity:** The entire array is sorted in descending order.
3. **Alternating parity:** Each maximal same-parity segment may contain only one element, so the array may remain unchanged.
4. **Duplicate elements:** Equal values can be sorted without affecting the lexicographically largest result.
5. **Zero values:** Zero is even, so it can be swapped with other even elements but not with odd elements.

---

## Key Takeaways

- A valid adjacent swap requires both elements to have the same parity.
- Elements of different parity cannot cross each other.
- Each maximal contiguous same-parity segment can be sorted independently.
- Sorting each segment in descending order produces the lexicographically largest reachable array.
- The solution runs in `O(n log n)` time and uses `O(n)` auxiliary space.

## Topics

- Arrays
- Sorting
- Greedy Approach
- Parity
- Lexicographical Ordering
