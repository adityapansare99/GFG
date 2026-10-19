# Count Indices That Escape Array

**Platform:** GeeksforGeeks  
**Difficulty:** Medium  
**Topics:** Arrays, Graphs, DFS, Memoization, Cycle Detection

## 1. Problem Statement

Given an integer array `arr[]`, where `arr[i]` represents the exact number of steps to move from index `i`, determine how many indices eventually lead outside the array.

The movement rules are:

- A positive value moves to the right.
- A negative value moves to the left.
- A value of `0` means the index does not move and is considered bad.

An index is called **good** if repeatedly following the jumps eventually takes you outside the array. Otherwise, if the jumps result in an infinite loop or remain stuck at an index with value `0`, the index is considered bad.

Return the total number of good indices.

### Examples

#### Example 1

**Input:**

```text
arr = [2, 3, -1, 2, -2, 4, 1]
```

**Output:**

```text
3
```

**Explanation:**

Using 0-based indexing, the good indices are `3`, `5`, and `6`.

- Index `3` jumps to index `5`, then to index `9`, which is outside the array.
- Index `5` jumps directly to index `9`, which is outside the array.
- Index `6` jumps to index `7`, which is outside the array.

Indices `1`, `2`, and `4` form a cycle, while index `0` eventually enters that cycle.

Therefore, the answer is `3`.

#### Example 2

**Input:**

```text
arr = [1, 0, -3, 0, -5, 0]
```

**Output:**

```text
2
```

**Explanation:**

The good indices are `2` and `4`.

- Index `2` jumps to index `-1`, which is outside the array.
- Index `4` jumps to index `-1`, which is outside the array.

Indices `1`, `3`, and `5` have value `0`, so they cannot escape. Index `0` jumps to index `1`, which is stuck.

Therefore, the answer is `2`.

### Constraints

- `1 <= arr.size() <= 10^5`
- `-10^5 <= arr[i] <= 10^5`

## 2. Approach: DFS with Memoization and Cycle Detection

The solution uses **Depth-First Search (DFS)** to follow the jump sequence from each index.

Instead of repeatedly traversing the same paths, it stores the result for each index in a vector named `visi`.

The vector acts as both a visitation-state array and a memoization array.

### Key Idea

For an index `i`, the next index is:

\[
next=i+arr[i]
\]

There are three important situations:

1. **The next index is outside the array:** The current path escapes, so the index is good.
2. **The next index has already been processed:** Reuse its stored result.
3. **The next index is part of the current traversal:** A cycle has been detected, so the indices in that cycle cannot escape.

The implementation uses `-1e6` as the initial unvisited marker. Before recursively exploring the next index, it temporarily sets `visi[i] = i`. This lets the DFS recognize a revisit to an index that is still being explored.

If a recursive call reaches an already visited index, it returns that index's stored value. The result then propagates back through the recursive calls.

## 3. Algorithm

1. Initialize `visi` with `n` elements, all set to `-1e6`.
2. For each index `i`:
   - If `visi[i]` is still `-1e6`, call `dfs(visi, i, arr)`.
3. Inside `dfs`:
   - If `i` is outside the array, return `visi.size() + 1`.
   - If `visi[i]` has already been assigned, return its stored value.
   - Mark the current index by assigning `visi[i] = i`.
   - Recursively process the next index `i + arr[i]`.
   - Store the returned result in `visi[i]`.
   - Return the stored result.
4. Initialize `ans = 0`.
5. Count the indices for which `visi[i] == visi.size() + 1`.
6. Return `ans`.

## 4. C++ Implementation

The following code is your original implementation, preserved without modifications.

```cpp
class Solution {
    private:
    int dfs(vector<int> &visi,int i,vector<int> &arr){
        if(i<0 || i>=visi.size()){
            return visi.size()+1;
        }
        
        if(visi[i]!=-1e6){
            return visi[i];
        }
        
        visi[i]=i;
        
        int inx=dfs(visi,i+arr[i],arr);
        
        visi[i]=inx;
        
        return inx;
    }
  public:
    int goodIndices(vector<int> &arr) {
        // code here
        int n=arr.size();
        vector<int> visi(n,-1e6);
        
        for(int i=0;i<n;i++){
            if(visi[i]==-1e6){
                dfs(visi,i,arr);
            }
        }
        
        int ans=0;
        
        for(int i=0;i<n;i++){
            if(visi[i]==visi.size()+1){
                ans++;
            }
        }
        
        return ans;
    }
};
```

## 5. Detailed Code Explanation

### Step 1: Check whether the index is outside the array

```cpp
if(i<0 || i>=visi.size()){
    return visi.size()+1;
}
```

This is the base case of the DFS.

If `i` becomes negative or reaches an index greater than or equal to the array size, the jump sequence has escaped the array.

The function returns `visi.size() + 1` as a special marker representing an escaping path.

For example, if the array size is `6`, the marker is:

```text
visi.size() + 1 = 7
```

### Step 2: Check whether the index has already been visited

```cpp
if(visi[i]!=-1e6){
    return visi[i];
}
```

Initially, every element of `visi` contains `-1e6`.

If the current element is no longer equal to this marker, it has already been visited or assigned a result.

The function returns the stored value instead of exploring the same path again.

This is the memoization step.

### Step 3: Mark the current index

```cpp
visi[i]=i;
```

The current index is temporarily stored in `visi[i]`.

This assignment acts as a marker indicating that the index is currently being explored.

If DFS reaches the same index again before the current traversal finishes, the stored value can reveal a cycle.

### Step 4: Explore the next index

```cpp
int inx=dfs(visi,i+arr[i],arr);
```

The next index is calculated using:

\[
next=i+arr[i]
\]

The recursive call follows the jump from the current index.

For example, if:

```text
i = 2
arr[i] = -3
```

Then:

```text
next = 2 + (-3) = -1
```

The recursive call detects that `-1` is outside the array and returns the escape marker.

### Step 5: Store the result

```cpp
visi[i]=inx;
```

After the recursive call returns, its result is stored in `visi[i]`.

This allows later traversals to reuse the stored value without repeating the entire path.

### Step 6: Return the result

```cpp
return inx;
```

The DFS returns the result obtained from the next index.

### Step 7: Initialize the visitation vector

```cpp
int n=arr.size();
vector<int> visi(n,-1e6);
```

The array length is stored in `n`, and `visi` is initialized with the unvisited marker.

For example:

```text
arr  = [1, 0, -3]
visi = [-1000000, -1000000, -1000000]
```

### Step 8: Run DFS from unvisited indices

```cpp
for(int i=0;i<n;i++){
    if(visi[i]==-1e6){
        dfs(visi,i,arr);
    }
}
```

This loop attempts DFS from each index that has not yet been visited.

If an index has already received a result from an earlier traversal, it is skipped.

### Step 9: Count good indices

```cpp
int ans=0;

for(int i=0;i<n;i++){
    if(visi[i]==visi.size()+1){
        ans++;
    }
}
```

The code counts indices whose stored result equals the escape marker.

Finally:

```cpp
return ans;
```

returns the total number of good indices.

## 6. Dry Run

Consider Example 2:

```text
arr = [1, 0, -3, 0, -5, 0]
n = 6
```

The escape marker is:

```text
n + 1 = 7
```

### Starting at index 0

The jump sequence is:

```text
0 -> 1
```

Index `1` contains `0`, so it jumps back to itself:

```text
1 -> 1 -> 1 -> ...
```

This is a cycle. The DFS encounters the already visited index and returns its stored index value.

The result propagates back to index `0`, which is also classified as bad.

### Starting at index 2

The jump sequence is:

```text
2 -> -1
```

Index `-1` is outside the array, so DFS returns the escape marker `7`.

The result propagates back to index `2`.

### Starting at index 3

Index `3` contains `0`, so it remains at itself:

```text
3 -> 3 -> 3 -> ...
```

It is bad.

### Starting at index 4

The jump sequence is:

```text
4 -> -1
```

The path escapes the array, so index `4` is good.

### Starting at index 5

Index `5` contains `0`, so it is bad.

### Final classification

| Index | Jump sequence | Classification |
|---:|---|---|
| 0 | `0 -> 1 -> 1 -> ...` | Bad |
| 1 | `1 -> 1 -> ...` | Bad |
| 2 | `2 -> -1` | Good |
| 3 | `3 -> 3 -> ...` | Bad |
| 4 | `4 -> -1` | Good |
| 5 | `5 -> 5 -> ...` | Bad |

The good indices are `2` and `4`.

**Output:**

```text
2
```

## 7. Complexity Analysis

### Time Complexity: O(n) under a correct memoized DFS

In a standard memoized graph traversal, every vertex is processed a constant number of times, giving `O(n)` time.

However, the supplied implementation uses `visi[i] = i` both as a temporary marker and as a returned classification. It does not distinguish a node currently in the recursion stack from a node whose result has been finalized. As a result, the implementation does not reliably handle every cycle and is not guaranteed to compute the correct answer for all inputs.

Therefore, the `O(n)` claim describes the expected complexity of a correctly implemented memoized traversal, not a correctness guarantee for this exact code.

### Auxiliary Space Complexity: O(n)

The `visi` vector stores one value per index.

The recursive DFS can also use up to `O(n)` stack frames in the worst case.

Therefore, the auxiliary space complexity is:

\[
O(n)
\]

## 8. Important Concepts

### 1. Depth-First Search

DFS follows a jump sequence recursively until it reaches an outside index or a previously visited index.

### 2. Memoization

The `visi` vector stores results so that previously processed paths can be reused.

### 3. Cycle Detection

A cycle occurs when following jumps revisits an index in the current traversal.

A robust implementation normally uses separate states for unvisited, currently visiting, and fully processed indices.

### 4. Escape Marker

The value `visi.size() + 1` represents a path that leaves the array.

### 5. Functional Graph

Every array index has exactly one outgoing transition, defined by `i + arr[i]`. Such a structure is a functional graph, where each path eventually exits the valid range or enters a cycle.

## 9. Conclusion

The solution uses recursive DFS and a visitation vector to follow jump sequences, reuse previous results, and count indices whose paths escape the array.

The implementation is based on a useful graph-traversal idea, but its visitation marker conflates an index currently being explored with a finalized result. This can cause incorrect classifications for certain cycles. A three-state DFS or an iterative path-classification method is needed for a fully reliable solution.

