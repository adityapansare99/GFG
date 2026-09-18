# Minimum Absolute Difference In BST

## Problem

Given the root of a Binary Search Tree (BST) containing `n` nodes, find the **minimum absolute difference** between the values of any two different nodes in the tree.

Return the minimum absolute difference.

---

## Example 1

```text
Input:
root = [50, 30, 70, 20, N, 60, 80]

Output:
10
```

The values in sorted order are:

```text
20, 30, 50, 60, 70, 80
```

The minimum difference is:

```text
30 - 20 = 10
```

---

## Example 2

```text
Input:
root = [60, 30, 90, 10]

Output:
20
```

The values in sorted order are:

```text
10, 30, 60, 90
```

The minimum difference is:

```text
30 - 10 = 20
```

---

# Approach 1: Inorder Traversal with Previous Value

## Idea

A Binary Search Tree has an important property:

> Inorder traversal of a BST produces values in sorted order.

For example:

```text
        50
       /  \
     30    70
    /     /  \
   20    60   80
```

Inorder traversal gives:

```text
20 → 30 → 50 → 60 → 70 → 80
```

Since the values are sorted, the minimum difference must occur between two adjacent values.

Therefore, we keep only the previous visited value instead of storing all values.

## How It Works

During inorder traversal:

```text
Left → Root → Right
```

we compare the current node with the previous node:

```text
root->data - prev
```

Then update:

```text
prev = root->data
```

The minimum difference is stored in `ans`.

## Code

```cpp
/* Binary Tree Node Structure
class Node {
public:
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
}; 
*/

class Solution {
    private:
    int ans;
    void solver(Node* root,int &prev){
        if(root==NULL){
            return ;
        }

        solver(root->left,prev);

        if(prev!=-1)
        ans=min(ans,root->data-prev);

        prev=root->data;

        solver(root->right,prev);
    }
  public:
    int absDiff(Node *root) {
        // code here
        int prev=-1;
        ans=INT_MAX;
        solver(root,prev);

        return ans;
    }
};
```

## Complexity

Every node is visited once.

```text
Time Complexity: O(n)
Space Complexity: O(h)
```

where `h` is the height of the BST.

For a balanced BST, `h = O(log n)`.  
For a skewed BST, `h = O(n)`.

---

# Approach 2: Inorder Traversal + Vector

## Idea

The second solution also uses inorder traversal.

All node values are stored in a vector:

```text
BST
 ↓
Inorder Traversal
 ↓
Vector of values
 ↓
Sort
 ↓
Compare adjacent values
```

Inorder traversal of a BST already produces sorted values, but the code explicitly sorts the vector.

## Step 1: Store Inorder Values

The recursive function visits:

```text
Left → Root → Right
```

and pushes every node value into the vector.

For example:

```text
20, 30, 50, 60, 70, 80
```

## Step 2: Sort the Vector

The code performs:

```cpp
sort(ans.begin(),ans.end());
```

so that the values are sorted.

## Step 3: Compare Adjacent Values

For every adjacent pair:

```cpp
res=min(res,ans[i]-ans[i-1]);
```

we update the minimum difference.

Because the values are sorted, comparing adjacent values is sufficient.

## Code

```cpp
/* Binary Tree Node Structure
class Node {
public:
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
}; 
*/

class Solution {
    private:
    void solver(Node* root,vector<int> &ans){
        if(root==NULL){
            return ;
        }

        solver(root->left,ans);
        ans.push_back(root->data);
        solver(root->right,ans);
    }
  public:
    int absDiff(Node *root) {
        // code here
        vector<int> ans;

        solver(root,ans);

        sort(ans.begin(),ans.end());

        int res=INT_MAX;

        for(int i=1;i<ans.size();i++){
            res=min(res,ans[i]-ans[i-1]);
        }

        return res;
    }
};
```

## Complexity

Inorder traversal takes:

```text
O(n)
```

Sorting takes:

```text
O(n log n)
```

The final traversal takes:

```text
O(n)
```

Therefore:

```text
Time Complexity: O(n log n)
Space Complexity: O(n)
```

The vector stores all `n` node values.

---

# Comparison

| Feature | Approach 1 | Approach 2 |
|---|---|---|
| Technique | Inorder + Previous Value | Inorder + Vector |
| Uses BST Property | Yes | Yes |
| Stores All Values | No | Yes |
| Sorting | No | Yes |
| Time | `O(n)` | `O(n log n)` |
| Extra Space | `O(h)` | `O(n + h)` |

---

# Why Only Adjacent Values Matter

Suppose the values are sorted:

```text
10, 20, 35, 50
```

The adjacent differences are:

```text
20 - 10 = 10
35 - 20 = 15
50 - 35 = 15
```

Any non-adjacent difference will be greater than or equal to the differences between values lying between them.

Therefore, the minimum difference must occur between adjacent values.

---

# Key Observation

The most important property is:

```text
BST
 ↓
Inorder Traversal
 ↓
Sorted Values
 ↓
Compare Adjacent Values
 ↓
Minimum Absolute Difference
```

This allows the first solution to avoid storing the complete inorder traversal.

---

# Edge Cases

### Two Nodes

If the tree contains only two nodes, their difference is the answer.

### Duplicate Values

If duplicate values exist, the minimum difference can be `0`.

For example:

```text
10, 10, 20
```

gives:

```text
10 - 10 = 0
```

---

# Key Takeaway

The two solutions use the same fundamental BST property but implement it differently.

### Approach 1

Uses the previous inorder value directly:

```text
O(n) time
O(h) space
```

### Approach 2

Stores all values and sorts them:

```text
O(n log n) time
O(n + h) space
```

The first approach is able to find the minimum difference in linear time because inorder traversal of a BST is already sorted.
