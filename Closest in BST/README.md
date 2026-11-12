# Closest in BST

**Difficulty:** Medium

## Problem Statement

Given the root of a Binary Search Tree (BST) and an integer `k`, find the minimum absolute difference between `k` and the value of any node in the BST.

The required result is:

`min(|node->data - k|)` for all nodes in the BST.

## Examples

**Example 1:**

- **Input:** `root = [10, 2, 11, 1, 5, N, N, N, N, 3, 6, N, 4], k = 13`
- **Output:** `2`
- **Explanation:** The node with value `11` is closest to `k = 13`. The minimum absolute difference is `|11 - 13| = 2`.

**Example 2:**

- **Input:** `root = [8, 1, 9, N, 4, N, 10, 3], k = 9`
- **Output:** `0`
- **Explanation:** The node with value `9` is exactly equal to `k = 9`. Therefore, the minimum absolute difference is `0`.

## Constraints

- `1 ≤ size of binary tree, k ≤ 10^5`
- `0 ≤ Node.data ≤ 10^5`

## Approach: BST Traversal with Recursive Search

A Binary Search Tree has the following property:

- All values in the left subtree are smaller than the current node.
- All values in the right subtree are greater than the current node.

We can use this property to avoid traversing the entire tree.

At every node, calculate the absolute difference between the current node's value and `k`, and update the minimum difference.

Then decide which subtree can contain a closer value:

- If `root->data > k`, search only the left subtree because smaller values are closer to `k`.
- If `root->data < k`, search only the right subtree because larger values are closer to `k`.
- If `root->data == k`, the minimum possible difference is `0`, so the search can stop.

This approach follows only one path from the root toward a potential closest value.

### Algorithm

1. Initialize `ans` with a large value (`1e9`).
2. Call the recursive function `solver()` with the root, target `k`, and reference variable `ans`.
3. If the current node is `NULL`, return.
4. Calculate the absolute difference between the current node's value and `k`.
5. Update `ans` with the minimum difference.
6. If the current node's value is greater than `k`, recursively search the left subtree.
7. Otherwise, recursively search the right subtree.
8. Return the final minimum difference.

## C++ Code

```cpp
/*
Structure of a Binary Search Tree node
class Node {
  public:
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};
*/

class Solution {
   private:
   void solver(Node* root,int k,int &ans){
       if(root==NULL){
           return ;
       }
       
       ans=min(ans,abs(root->data-k));
       
       if(root->data>k){
           solver(root->left,k,ans);
       }
       
       else{
           solver(root->right,k,ans);
       }
   }
 public:
   int minDiff(Node *root, int k) {
       // code here
       int ans=1e9;
       
       solver(root,k,ans);
       
       return ans;
   }
};
```

## Dry Run

**Input:**

```text
root = [10, 2, 11, 1, 5, N, N, N, N, 3, 6, N, 4]
k = 13
```

Consider the nodes visited during the BST search:

| Current Node | Absolute Difference | Updated Minimum | Next Subtree |
|---:|---:|---:|---|
| 10 | \|10 - 13\| = 3 | 3 | Right |
| 11 | \|11 - 13\| = 2 | 2 | Right |
| NULL | - | 2 | Stop |

The search visits only the nodes along the right-side path because their values are relevant to finding a closer value.

**Output:**

```text
2
```

## Complexity Analysis

Let `h` be the height of the Binary Search Tree.

### Time Complexity: O(h)

- At each node, we perform a constant number of operations.
- Due to the BST property, we recursively visit only one subtree.
- Therefore, the number of visited nodes is bounded by the height of the tree.

**Best case:** `O(1)` when the root itself contains the target value.

**Balanced BST:** `O(log n)`

**Worst case:** `O(n)` when the BST is skewed.

### Space Complexity: O(h)

- The recursive function uses the call stack.
- At most `h` recursive calls can be active at a time.

**Balanced BST:** `O(log n)`

**Worst case:** `O(n)` for a skewed BST.

## Key Takeaways

- BST properties help eliminate unnecessary subtree traversal.
- When the current node is greater than the target, only the left subtree needs to be searched.
- When the current node is smaller than the target, only the right subtree needs to be searched.
- Maintaining the minimum absolute difference allows us to track the closest value.
- A balanced BST provides efficient `O(log n)` search.

## Conclusion

The solution uses the Binary Search Tree property to search only the relevant subtree at each step. By updating the minimum absolute difference at every visited node, it finds the closest value to `k` efficiently.

The solution takes **O(h) time and O(h) auxiliary space**, where `h` is the height of the BST.