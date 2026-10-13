# Adding Ones

**Platform:** GeeksforGeeks  
**Difficulty:** Easy  
**Topic:** Arrays, Sorting, Greedy Technique

## 1. Problem Statement

Consider an array `arr[]` of size `n`, initially containing all zeros. You are also given an array `updates[]` of `k` positive integers.

For each value `j` in `updates[]`, add `1` to every element `arr[i]` whose 1-based index satisfies:

\[
i\ge j
\]

Perform all the updates and modify the array accordingly.

### Examples

#### Example 1

**Input:**

```text
n = 3
updates[] = [1, 1, 2, 3]
```

**Output:**

```text
[2, 3, 4]
```

**Explanation:**

Initially:

```text
arr = [0, 0, 0]
```

After the first update `1`:

```text
arr = [1, 1, 1]
```

After the second update `1`:

```text
arr = [2, 2, 2]
```

After the update `2`:

```text
arr = [2, 3, 3]
```

After the update `3`:

```text
arr = [2, 3, 4]
```

Therefore, the final array is `[2, 3, 4]`.

#### Example 2

**Input:**

```text
n = 2
updates[] = [1, 1, 1]
```

**Output:**

```text
[3, 3]
```

**Explanation:**

Initially:

```text
arr = [0, 0]
```

Each update increments every element because the update index is `1`.

After three updates:

```text
arr = [3, 3]
```

### Constraints

- `1 <= n, updates.size() <= 10^5`
- `1 <= updates[i] <= n`

## 2. Approach: Sorting and Counting Updates

The solution uses sorting and processes the array from right to left.

The key observation is that an update at index `j` affects every element from index `j` to the end of the array.

Therefore, an element at 1-based index `i` is incremented once for every update satisfying:

\[
updates[t]\le i
\]

This means its final value equals the number of update indices less than or equal to its position.

The implementation sorts `updates` in ascending order and uses two pointers to determine the number of updates affecting each array position.

### Main Idea

- Sort the `updates` array.
- Start from the last position of the result array.
- Start from the last update, which is the largest update index.
- Convert each update from 1-based indexing to 0-based indexing using `updates[j] - 1`.
- If the current result position is at least that converted index, assign `j + 1` to the result.
- Otherwise, move to the preceding update.
- Continue until all relevant positions or updates have been processed.

Because the updates are sorted, the algorithm can count the number of updates affecting each position without applying every update individually.

## 3. Algorithm

1. Create a result vector `res` of size `n`, initialized to zero.
2. Sort `updates` in ascending order.
3. Initialize:
   - `i = n - 1`, the last index of the result array.
   - `j = updates.size() - 1`, the last index of the sorted updates array.
4. While `i >= 0` and `j >= 0`:
   - Calculate `val = updates[j] - 1`.
   - If `i >= val`, assign `j + 1` to `res[i]` and decrement `i`.
   - Otherwise, decrement `j`.
5. Return `res`.

## 4. C++ Implementation

The following is the original code, preserved exactly as provided.

```cpp
class Solution {
  public:
    vector<int> update(int n, vector<int>& updates) {
        // code here
        vector<int> res(n,0);
        sort(updates.begin(),updates.end());
        int i=n-1;
        int j=updates.size()-1;
        
        while(i>=0 && j>=0){
            int val=updates[j]-1;
            
            if(i>=val){
                res[i--]=j+1;
            }
            
            else{
                j--;
            }
        }
        
        return res;
    }
};
```

## 5. Detailed Code Explanation

### Step 1: Initialize the result array

```cpp
vector<int> res(n,0);
```

Creates a vector of size `n`, with every element initialized to zero.

For example, if `n = 3`:

```text
res = [0, 0, 0]
```

This vector stores the final values after all updates are accounted for.

### Step 2: Sort the updates

```cpp
sort(updates.begin(),updates.end());
```

Sorts all update indices in ascending order.

For example:

```text
Before: [1, 3, 1, 2]
After:  [1, 1, 2, 3]
```

Sorting makes it possible to determine how many updates affect each position by examining the update indices in order.

**Note:** This operation also modifies the input `updates` vector.

### Step 3: Initialize the pointers

```cpp
int i=n-1;
int j=updates.size()-1;
```

The pointer `i` starts at the last position of the result array, while `j` starts at the last position of the sorted update array.

For example, when `n = 3` and there are four updates:

```text
i = 2
j = 3
```

The algorithm processes the result array from right to left.

### Step 4: Process the positions

```cpp
while(i>=0 && j>=0){
```

The loop continues while both pointers remain within their valid ranges.

### Step 5: Convert the update index

```cpp
int val=updates[j]-1;
```

The problem provides update indices using 1-based indexing, but the result vector uses 0-based indexing.

Subtracting one converts the update index to the corresponding vector index.

For example:

```text
updates[j] = 3
val = 3 - 1 = 2
```

This update affects vector positions `2` and beyond.

### Step 6: Assign the number of applicable updates

```cpp
if(i>=val){
    res[i--]=j+1;
}
```

If the current result index `i` is at least `val`, the current position is affected by the update threshold represented by `updates[j]`.

Because `updates` is sorted, `j + 1` represents the number of updates whose indices are at most the current 1-based position, provided the pointer `j` has been moved to the appropriate update.

The expression `res[i--]` assigns the value to the current position and then decrements `i`.

### Step 7: Move to the preceding update

```cpp
else{
    j--;
}
```

If the current position is smaller than the current update threshold, that update cannot affect the position.

The algorithm moves to the preceding update, which has an equal or smaller index.

### Step 8: Return the result

```cpp
return res;
```

Returns the vector containing the calculated values.

## 6. Dry Run

Consider Example 1:

```text
n = 3
updates = [1, 1, 2, 3]
```

After sorting:

```text
updates = [1, 1, 2, 3]
res = [0, 0, 0]
```

Initial pointer values:

```text
i = 2
j = 3
```

| Iteration | `i` | `j` | `updates[j]` | `val` | Action | Result |
|---|---:|---:|---:|---:|---|---|
| 1 | 2 | 3 | 3 | 2 | `2 >= 2`, assign `j + 1 = 4` | `[0, 0, 4]` |
| 2 | 1 | 3 | 3 | 2 | `1 < 2`, decrement `j` | `[0, 0, 4]` |
| 3 | 1 | 2 | 2 | 1 | `1 >= 1`, assign `j + 1 = 3` | `[0, 3, 4]` |
| 4 | 0 | 2 | 2 | 1 | `0 < 1`, decrement `j` | `[0, 3, 4]` |
| 5 | 0 | 1 | 1 | 0 | `0 >= 0`, assign `j + 1 = 2` | `[2, 3, 4]` |

The loop ends when `i = -1`.

**Final output:**

```text
[2, 3, 4]
```

## 7. Complexity Analysis

### Time Complexity: `O(n + k log k)`

Let `k` be the number of updates.

- Creating the result vector takes `O(n)` time.
- Sorting `updates` takes `O(k log k)` time.
- The two-pointer loop takes `O(n + k)` time because each pointer only moves backward.

The overall time complexity is:

\[
O(n+k\log k)
\]

### Auxiliary Space Complexity: `O(n)`

The result vector `res` requires `O(n)` space.

The sorting algorithm may also use implementation-dependent auxiliary space. Excluding the result vector, the two-pointer portion uses `O(1)` additional space.

## 8. Important Concepts

### 1. Sorting

Sorting arranges update indices in ascending order so their effects can be counted efficiently.

### 2. Two-Pointer Technique

Two pointers move backward through the result positions and the sorted updates array.

### 3. Index Conversion

The expression `updates[j] - 1` converts a 1-based update index to a 0-based array index.

### 4. Counting Applicable Updates

An element at 1-based position `i` receives one increment for each update whose value is at most `i`.

Thus, its final value is:

\[
arr[i]=\#\{j:updates[j]\le i\}
\]

Here, the expression uses 1-based indexing for the mathematical position `i`.

## 9. Conclusion

The solution sorts the update indices and uses two pointers to calculate the number of updates affecting each position. This avoids applying each update across all affected elements individually.

The expected complexity is `O(n + k log k)` time and `O(n)` space for the result array.

