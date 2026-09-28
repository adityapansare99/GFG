# Range GCD Queries

**Difficulty:** Medium

## Problem Statement

Given an integer array `arr[]` and a 2D array `queries[][]` containing `q` queries, there are two types of queries:

* **Type 1:** `[0, l, r]` → Find the GCD of all elements in the range `[l, r]`.
* **Type 2:** `[1, index, value]` → Update `arr[index]` to `value`.

Return an array containing the answers to all Type 1 queries in the order they appear.

The array uses **0-based indexing**.

---

## Example 1

```text
Input:
arr[] = [2, 3, 4, 6, 8, 16]
queries[][] = [
    [0, 0, 2],
    [1, 3, 8],
    [0, 2, 5]
]

Output:
[1, 4]
```

### Explanation

Initially:

```text
[2, 3, 4, 6, 8, 16]
```

Query:

```text
[0, 0, 2]
```

GCD of:

```text
[2, 3, 4]
```

is:

```text
1
```

Next:

```text
[1, 3, 8]
```

updates index `3`:

```text
[2, 3, 4, 8, 8, 16]
```

Finally:

```text
[0, 2, 5]
```

GCD of:

```text
[4, 8, 8, 16]
```

is:

```text
4
```

Therefore:

```text
[1, 4]
```

---

## Example 2

```text
Input:
arr[] = [12, 18, 24, 30, 36]

queries[][] = [
    [0, 1, 3],
    [1, 2, 15],
    [0, 0, 2],
    [0, 2, 4]
]

Output:
[6, 3, 3]
```

### Explanation

Initially:

```text
[12, 18, 24, 30, 36]
```

For:

```text
[0, 1, 3]
```

we calculate:

```text
GCD(18, 24, 30) = 6
```

Then:

```text
[1, 2, 15]
```

updates index `2`:

```text
[12, 18, 15, 30, 36]
```

For:

```text
[0, 0, 2]
```

we get:

```text
GCD(12, 18, 15) = 3
```

For:

```text
[0, 2, 4]
```

we get:

```text
GCD(15, 30, 36) = 3
```

Final answer:

```text
[6, 3, 3]
```

---

# Approach

The problem contains two operations:

1. Range GCD query
2. Point update

A normal traversal of the range for every query would take `O(n)` per query. Since both `n` and `q` can be up to `10^5`, this can become too slow.

A **Segment Tree** can efficiently handle both operations.

The segment tree stores the **GCD of every segment** of the array.

For every internal node:

```text
seg[i] = GCD(seg[left child], seg[right child])
```

This allows us to combine smaller ranges to obtain the GCD of a larger range.

---

# Segment Tree Structure

For an array:

```text
[2, 3, 4, 6]
```

the segment tree conceptually stores:

```text
                 GCD(2,3,4,6)
                 /           \
             GCD(2,3)      GCD(4,6)
              /   \          /   \
             2     3        4     6
```

Each node represents a range of the array.

---

# 1. Build

The `build()` function constructs the segment tree recursively.

```cpp
void build(vector<int> &seg,vector<int> &arr,int l,int r,int i)
```

### Base Case

When:

```text
l == r
```

the node represents a single array element.

Therefore:

```cpp
seg[i]=arr[r];
```

### Recursive Case

The range is divided into two halves:

```text
[l, mid]
[mid+1, r]
```

The GCD of the two child nodes is stored in the current node:

```cpp
seg[i]=__gcd(seg[2*i+1],seg[2*i+2]);
```

### Complexity

```text
O(n)
```

---

# 2. Range GCD Query

The `search()` function finds the GCD in a given range `[left, right]`.

```cpp
int search(vector<int> &seg,int i,int l,int r,int left,int right)
```

There are three cases.

### Complete Overlap

If the current segment is completely inside the query range:

```cpp
if(left<=l && r<=right)
```

we directly return the stored GCD:

```cpp
return seg[i];
```

### No Overlap

If the current segment does not intersect the query:

```cpp
else if(left>r || right<l)
```

we return:

```cpp
return 0;
```

This works because:

```text
GCD(x, 0) = x
```

So `0` acts as the identity value for the GCD operation.

### Partial Overlap

Otherwise, the range is divided into two parts:

```cpp
int leftVal=search(...);
int rightVal=search(...);
```

and their GCD is calculated:

```cpp
return __gcd(leftVal,rightVal);
```

### Complexity

```text
O(log n)
```

---

# 3. Point Update

The `update()` function changes one element of the array.

```cpp
void update(vector<int> &seg,int i,int l,int r,int index,int val)
```

The segment tree is traversed until the leaf corresponding to `index` is reached.

At the leaf:

```cpp
seg[i]=val;
```

After updating the leaf, all affected parent nodes are recalculated:

```cpp
seg[i]=__gcd(seg[2*i+1],seg[2*i+2]);
```

Only the nodes along the path from the leaf to the root need to be updated.

### Complexity

```text
O(log n)
```

---

# Processing Queries

The `processQueries()` function first builds the segment tree:

```cpp
vector<int> seg(4*n);

build(seg,arr,0,n-1,0);
```

Then every query is processed.

For a Type 1 query:

```text
[0, l, r]
```

the range GCD is calculated using `search()`.

For a Type 2 query:

```text
[1, index, value]
```

the segment tree is updated using `update()`.

---

# Why Return 0 for No Overlap?

This is an important property of GCD.

Suppose the query has two parts:

```text
leftVal = 6
rightVal = 0
```

Then:

```text
GCD(6, 0) = 6
```

Therefore, returning `0` for a non-overlapping segment does not affect the final answer.

More generally:

```text
GCD(x, 0) = x
```

So `0` is the identity value for GCD.

---

# Complexity Analysis

Let:

```text
n = arr.size()
q = number of queries
```

### Building the Segment Tree

```text
O(n)
```

### Range GCD Query

```text
O(log n)
```

### Point Update

```text
O(log n)
```

### Total

For `q` queries:

```text
O(n + q log n)
```

### Space Complexity

The segment tree uses:

```text
O(4n)
```

space, which is:

```text
O(n)
```

---

# Complete Code

```cpp
class Solution {
    private:
    void build(vector<int> &seg,vector<int> &arr,int l,int r,int i){
        if(l==r){
            seg[i]=arr[r];
            
            return ;
        }
        
        int mid=(l+r)/2;
        build(seg,arr,l,mid,2*i+1);
        build(seg,arr,mid+1,r,2*i+2);
        
        seg[i]=__gcd(seg[2*i+1],seg[2*i+2]);
    }
    
    int search(vector<int> &seg,int i,int l,int r,int left,int right){
        if(left<=l && r<=right){
            return seg[i];
        }
        
        else if(left>r || right<l){
            return 0;
        }
        
        int mid=(l+r)/2;
        int leftVal=search(seg,2*i+1,l,mid,left,right);
        int rightVal=search(seg,2*i+2,mid+1,r,left,right);
        
        return __gcd(leftVal,rightVal);
    }
    
    void update(vector<int> &seg,int i,int l,int r,int index,int val){
        if(l==r){
            seg[i]=val;
            return ;
        }
        
        int mid=(l+r)/2;
        
        if(index<=mid){
            update(seg,2*i+1,l,mid,index,val);
        }
        
        else{
            update(seg,2*i+2,mid+1,r,index,val);
        }
        
        seg[i]=__gcd(seg[2*i+1],seg[2*i+2]);
    }
    
  public:
    vector<int> processQueries(vector<int>& arr, vector<vector<int>>& queries) {
        // code here
        int n=arr.size();
        vector<int> seg(4*n);
        
        build(seg,arr,0,n-1,0);
        
        vector<int> ans;
        
        for(auto &it:queries){
            if(it[0]==0){
                int l=it[1];
                int r=it[2];
                
                ans.push_back(search(seg,0,0,n-1,l,r));
            }
            
            else{
                int index=it[1];
                int value=it[2];
                
                update(seg,0,0,n-1,index,value);
            }
        }
        
        return ans;
    }
};
```

---

# Key Takeaways

* A **Segment Tree** is useful when both range queries and updates are required.
* Each node stores the GCD of its corresponding range.
* Range GCD queries take `O(log n)`.
* Point updates take `O(log n)`.
* `0` is used as the identity value for GCD because `GCD(x, 0) = x`.
* Building the tree takes `O(n)`.
* Overall complexity is:

```text
O(n + q log n)
```
