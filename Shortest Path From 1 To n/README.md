# Shortest Path From 1 To n

**Platform:** GeeksforGeeks  
**Difficulty:** Easy  
**Topics:** Graphs, Greedy Algorithm, Mathematics

## 1. Problem Statement

Consider a directed graph whose vertices are numbered from `1` to `n`.

There is a directed edge from vertex `i` to vertex `j` if and only if either:

- `j = i + 1`
- `j = 3 * i`

The task is to find the minimum number of edges required to reach vertex `n` from vertex `1`.

### Examples

#### Example 1

**Input:**

```text
n = 4
```

**Output:**

```text
2
```

**Explanation:**

One possible shortest path is:

```text
1 -> 3 -> 4
```

The path contains two edges, so the minimum number of edges is `2`.

#### Example 2

**Input:**

```text
n = 9
```

**Output:**

```text
2
```

**Explanation:**

The shortest path is:

```text
1 -> 3 -> 9
```

The path contains two edges.

#### Example 3

**Input:**

```text
n = 15
```

**Output:**

```text
4
```

**Explanation:**

One shortest path is:

```text
1 -> 3 -> 4 -> 5 -> 15
```

The path contains four edges.

### Constraints

```text
1 <= n <= 10^8
```

## 2. Approach: Reverse Greedy Traversal

The solution works backward from the destination vertex `n` until it reaches vertex `1`.

In the original graph, from a vertex `i`, we can move to:

- `i + 1`
- `3 * i`

To reverse these operations, we can:

- Divide by `3` when the current vertex is divisible by `3`.
- Subtract `1` otherwise.

Each reverse operation corresponds to one edge in the original path, so we increment `ans` after every operation.

### Why work backward?

Moving forward requires deciding whether to increment the current vertex or multiply it by three.

Working backward gives a simple way to undo these operations:

- If `n` is divisible by `3`, dividing by `3` reverses a multiplication by `3`.
- Otherwise, subtracting `1` reverses an increment by `1`.

This leads to a concise greedy implementation.

## 3. Algorithm

1. Initialize `ans = 0`.
2. While `n > 1`:
   - If `n % 3 == 0`, divide `n` by `3`.
   - Otherwise, decrement `n` by `1`.
   - Increment `ans`.
3. Return `ans`.

## 4. C++ Implementation

The following is your original code, preserved exactly as provided.

```cpp
class Solution {
  public:
    int minimumStep(int n) {
        // code here
        int ans=0;
        
        while(n>1){
            if(n%3==0){
                n/=3;
            }
            
            else{
                n--;
            }
            
            ans++;
        }
        
        return ans;
    }
};
```

## 5. Detailed Code Explanation

### Step 1: Initialize the answer

```cpp
int ans=0;
```

The variable `ans` counts the number of reverse operations performed.

Each reverse operation represents one edge in the corresponding forward path.

### Step 2: Continue until reaching vertex 1

```cpp
while(n>1){
```

The loop runs until `n` becomes `1`, the starting vertex.

When `n == 1`, no more operations are required.

### Step 3: Check divisibility by 3

```cpp
if(n%3==0){
    n/=3;
}
```

If the current value is divisible by `3`, the code divides it by `3`.

For example:

```text
n = 9
n = 9 / 3 = 3
```

This reverses a multiplication-by-three edge in the forward direction.

### Step 4: Otherwise, decrement the value

```cpp
else{
    n--;
}
```

If the current value is not divisible by `3`, the code decrements it by one.

For example:

```text
n = 4
n = 4 - 1 = 3
```

This reverses an increment-by-one edge.

### Step 5: Count the operation

```cpp
ans++;
```

Every division or decrement represents one reverse edge, so the operation count is incremented.

### Step 6: Return the answer

```cpp
return ans;
```

Once `n` reaches `1`, the function returns the total number of operations performed.

## 6. Dry Run

Consider Example 1:

```text
n = 4
ans = 0
```

| Iteration | Current `n` | Operation | New `n` | `ans` |
|---|---:|---|---:|---:|
| 1 | 4 | `n--` | 3 | 1 |
| 2 | 3 | `n /= 3` | 1 | 2 |

The loop terminates because `n == 1`.

**Final output:**

```text
2
```

The corresponding forward path is:

```text
1 -> 3 -> 4
```

## 7. Dry Run for Example 2

Consider:

```text
n = 9
ans = 0
```

| Iteration | Current `n` | Operation | New `n` | `ans` |
|---|---:|---|---:|---:|
| 1 | 9 | `n /= 3` | 3 | 1 |
| 2 | 3 | `n /= 3` | 1 | 2 |

The loop terminates.

**Final output:**

```text
2
```

The corresponding forward path is:

```text
1 -> 3 -> 9
```

## 8. Complexity Analysis

### Time Complexity: O(log n) for this implementation's loop count in typical paths, but O(n) worst case

Every iteration either divides `n` by `3` or decrements it by `1`.

Division reduces the value quickly, but the algorithm may perform many decrements before reaching a multiple of `3`.

For example, when `n = 3k + 2`, the code decrements once to `3k + 1`, then again to `3k`, before dividing.

The total number of operations is therefore not always logarithmic. The worst case is **O(n)**.

### Auxiliary Space Complexity: O(1)

The algorithm uses only two integer variables, `n` and `ans`, and does not allocate any additional data structures.

Therefore, the auxiliary space complexity is:

\[
O(1)
\]

## 9. Important Concepts

### 1. Directed Graph

An edge represents a valid move from one vertex to another. Since the edges are directed, reversing a path requires undoing the forward operations.

### 2. Reverse Traversal

The algorithm starts at the destination and reverses the allowed operations until it reaches the starting vertex.

### 3. Greedy Choice

At each step, the code prefers division by `3` whenever possible; otherwise, it decrements the current value.

### 4. Operation Counting

Every reverse operation corresponds to one edge, so counting the operations gives the length of the path generated by this procedure.

## 10. Conclusion

The implementation uses a reverse greedy strategy to reach vertex `1` from vertex `n`. It repeatedly divides by `3` when possible and decrements otherwise, counting each operation.

The code is simple and uses constant auxiliary space. However, this greedy choice is **not guaranteed to find the shortest path for every input**. For example, when `n = 6`, the code takes three reverse steps (`6 -> 2 -> 1` would require decrementing after division, but the actual code takes `6 -> 2 -> 1`, giving two steps); more generally, the greedy strategy should be validated against all constraints before assuming optimality. A shortest-path or dynamic-programming solution can be used if correctness for every `n` is required.
