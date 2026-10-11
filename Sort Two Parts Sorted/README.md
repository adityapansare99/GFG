# Sort Two Parts Sorted

## Problem Statement

Given an integer array `arr[]` where the two parts around a break point are individually sorted, merge them into a single sorted array.

The break point can be anywhere in the array, including at the beginning or end.

### Examples

**Example 1**

**Input:**
```text
arr[] = [2, 3, 8, -1, 7, 10]
```

**Output:**
```text
[-1, 2, 3, 7, 8, 10]
```

**Explanation:**

The two individually sorted parts are `[2, 3, 8]` and `[-1, 7, 10]`. Merging these parts produces the overall sorted array `[-1, 2, 3, 7, 8, 10]`.

**Example 2**

**Input:**
```text
arr[] = [-4, 6, 9, -1, 3]
```

**Output:**
```text
[-4, -1, 3, 6, 9]
```

**Explanation:**

The two sorted parts are `[-4, 6, 9]` and `[-1, 3]`. Combining them in ascending order produces `[-4, -1, 3, 6, 9]`.

**Example 3**

**Input:**
```text
arr[] = [10, 20, 30]
```

**Output:**
```text
[10, 20, 30]
```

**Explanation:**

One part is empty, and the other part is the entire array. Since the array is already sorted, no changes are required.

## Constraints

- `1 <= arr.size() <= 10^6`
- `-10^5 <= arr[i] <= 10^5`

## Approach: Gap Method

The solution uses the **Gap Method**, which is similar to the technique used in Shell Sort.

Instead of creating separate arrays for the two sorted parts or using an additional array for merging, the algorithm compares elements at a certain distance (gap) from each other and swaps them when they are in the wrong order.

The gap gradually decreases until it becomes `1`. The final pass compares adjacent elements, helping ensure that the entire array is sorted.

### Algorithm

1. Calculate the size of the array and store it in `n`.
2. Initialize the gap using `n/2 + n%2`, which calculates the ceiling of `n/2`.
3. While the gap is greater than zero:
   - Initialize `left` to `0`.
   - Initialize `right` to `left + gap`.
   - Compare the elements at `arr[left]` and `arr[right]`.
   - If `arr[left] > arr[right]`, swap the two elements.
   - Increment both pointers to compare the next pair separated by the same gap.
4. After processing all pairs for the current gap:
   - If the gap is `1`, terminate the loop.
   - Otherwise, reduce the gap using `gap/2 + gap%2`.
5. The array is sorted in place, and no separate result array is required.

## C++ Implementation

The following is the original implementation, preserved without changes.

```cpp
class Solution {
  public:
    void mergeTwoParts(vector<int>& arr) {
        // code here
        int n=arr.size();
        int gap=n/2+n%2;
        
        while(gap>0){
            int left=0;
            int right=left+gap;
            
            while(right<n){
                if(arr[left]>arr[right]){
                    swap(arr[left],arr[right]);
                }
                
                left++;
                right++;
            }
            
            if(gap==1){
                break;
            }
            
            gap=gap/2+gap%2;
        }
    }
};
```

## Detailed Code Explanation

### 1. Calculate the array size

```cpp
int n=arr.size();
```

This statement stores the total number of elements in the array in `n`.

For example, if `arr = [2, 3, 8, -1, 7, 10]`, then `n = 6`.

### 2. Initialize the gap

```cpp
int gap=n/2+n%2;
```

This calculates the ceiling of half the array size.

The expression is equivalent to:

\[
gap=\left\lceil\frac{n}{2}\right\rceil
\]

Integer division is used, and `n%2` accounts for odd values of `n`.

For example:

- If `n = 6`, the initial gap is `3`.
- If `n = 5`, the initial gap is `3`.
- If `n = 1`, the initial gap is `1`.

### 3. Process elements while the gap is positive

```cpp
while(gap>0){
```

This loop performs multiple passes over the array. Each pass compares elements separated by the current gap.

The gap decreases after each pass until it reaches `1`.

### 4. Initialize the two pointers

```cpp
int left=0;
int right=left+gap;
```

The `left` pointer starts at index `0`. The `right` pointer starts at the index `gap` positions ahead.

For a gap of `3`, the first comparison is between indices `0` and `3`.

The pointers move together, maintaining the same distance between the compared elements.

### 5. Compare and swap elements

```cpp
while(right<n){
    if(arr[left]>arr[right]){
        swap(arr[left],arr[right]);
    }
    
    left++;
    right++;
}
```

The inner loop processes every pair of indices separated by the current gap.

If the left element is greater than the right element, the two elements are swapped.

Otherwise, they remain unchanged.

Both pointers are then incremented so that the next pair can be examined.

### 6. Stop after the final gap pass

```cpp
if(gap==1){
    break;
}
```

When the gap reaches `1`, the algorithm has performed its final pass over adjacent elements. After this pass, the loop terminates.

### 7. Reduce the gap

```cpp
gap=gap/2+gap%2;
```

This reduces the gap to the ceiling of half its previous value.

For example, the gap sequence for an array of size `6` is:

```text
3 -> 2 -> 1
```

The algorithm begins by comparing elements farther apart and progressively moves toward adjacent-element comparisons.

## Dry Run

Consider the first example:

```text
arr = [2, 3, 8, -1, 7, 10]
n = 6
```

### Pass 1: Gap = 3

The initial gap is:

\[
gap=\frac{6}{2}+\frac{6\bmod 2}{1}=3
\]

The algorithm compares elements three positions apart.

| Left index | Right index | Comparison | Array after comparison |
|---:|---:|---|---|
| 0 | 3 | `2 > -1` | `[-1, 3, 8, 2, 7, 10]` |
| 1 | 4 | `3 < 7` | `[-1, 3, 8, 2, 7, 10]` |
| 2 | 5 | `8 < 10` | `[-1, 3, 8, 2, 7, 10]` |

After this pass:

```text
[-1, 3, 8, 2, 7, 10]
```

The gap is reduced to `2`.

### Pass 2: Gap = 2

Now, the algorithm compares elements two positions apart.

| Left index | Right index | Comparison | Array after comparison |
|---:|---:|---|---|
| 0 | 2 | `-1 < 8` | `[-1, 3, 8, 2, 7, 10]` |
| 1 | 3 | `3 > 2` | `[-1, 2, 8, 3, 7, 10]` |
| 2 | 4 | `8 > 7` | `[-1, 2, 7, 3, 8, 10]` |
| 3 | 5 | `3 < 10` | `[-1, 2, 7, 3, 8, 10]` |

After this pass:

```text
[-1, 2, 7, 3, 8, 10]
```

The gap is reduced to `1`.

### Pass 3: Gap = 1

With a gap of `1`, adjacent elements are compared.

| Left index | Right index | Comparison | Array after comparison |
|---:|---:|---|---|
| 0 | 1 | `-1 < 2` | `[-1, 2, 7, 3, 8, 10]` |
| 1 | 2 | `2 < 7` | `[-1, 2, 7, 3, 8, 10]` |
| 2 | 3 | `7 > 3` | `[-1, 2, 3, 7, 8, 10]` |
| 3 | 4 | `7 < 8` | `[-1, 2, 3, 7, 8, 10]` |
| 4 | 5 | `8 < 10` | `[-1, 2, 3, 7, 8, 10]` |

The gap is `1`, so the algorithm terminates after completing this pass.

**Final sorted array:**

```text
[-1, 2, 3, 7, 8, 10]
```

## Complexity Analysis

### Time Complexity: O(n log n)

Each pass processes pairs of elements across the array, requiring at most `O(n)` comparisons.

The gap is approximately halved after each pass, resulting in `O(log n)` passes.

Therefore, the overall time complexity is:

\[
O(n)\times O(\log n)=O(n\log n)
\]

### Auxiliary Space Complexity: O(1)

The algorithm sorts the input array in place. It uses only a few integer variables, such as `n`, `gap`, `left`, and `right`.

It does not allocate another array or use recursion.

Therefore, the auxiliary space complexity is:

\[
\boxed{O(1)}
\]

## Key Takeaways

- The solution uses the Gap Method, similar to Shell Sort.
- It compares elements separated by a progressively smaller gap.
- The gap is reduced using `gap/2 + gap%2`.
- Elements are swapped only when they are in the wrong relative order.
- The array is modified in place, without an additional array.
- The implementation has `O(n log n)` time complexity and `O(1)` auxiliary space complexity.

## Conclusion

The `mergeTwoParts()` function sorts the array by repeatedly comparing and swapping elements at decreasing distances. Starting with a gap of approximately half the array size, it reduces the gap until adjacent elements are compared. This provides an in-place solution that avoids allocating extra storage for the merged result.
