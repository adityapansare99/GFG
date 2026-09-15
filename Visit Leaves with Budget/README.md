# Visit Leaves with Budget

**Difficulty:** Easy
**Problem:** Visit Leaves with Budget

---

## Problem Statement

Given a binary tree and an integer `k`, where the root is at **level 1**, the cost of visiting a leaf node is equal to the level of that leaf node.

You can visit any number of leaf nodes, but the total cost of visiting them must not exceed `k`.

Return the maximum number of leaf nodes that can be visited within the given budget.

---

## Examples

### Example 1

```text
Input:
root[] = [10, 8, 2, 3, N, 3, 6, N, N, N, 4]
k = 8

Output:
2
```

The leaf nodes have costs:

```text
Leaf 3 -> level 3 -> cost 3
Leaf 4 -> level 4 -> cost 4
Leaf 6 -> level 3 -> cost 3
```

The two cheapest leaves cost:

```text
3 + 3 = 6
```

Therefore, the maximum number of leaves that can be visited is:

```text
2
```

---

### Example 2

```text
Input:
root[] = [1, 2, 3, 4, 5, 6, 7]
k = 5

Output:
1
```

All four leaf nodes are at level `3`.

Therefore, every leaf costs `3`.

```text
3 <= 5
3 + 3 > 5
```

So only one leaf can be visited.

---

### Example 3

```text
Input:
root[] = [1]
k = 1

Output:
1
```

The root itself is a leaf and is at level `1`.

Therefore:

```text
cost = 1
```

Since:

```text
1 <= k
```

we can visit the root.

---

# Approach

The main idea is to use **BFS (Breadth First Search)**.

The important observation is:

> The cost of a leaf is its level, and BFS visits the tree level by level.

Therefore, leaf nodes are automatically processed in increasing order of their cost.

For example:

```text
          1                 Level 1
        /   \
       2     3              Level 2
      / \     \
     4   5     6            Level 3
```

The leaf costs are:

```text
4 -> 3
5 -> 3
6 -> 3
```

BFS encounters them level by level, so we don't need to separately collect and sort their costs.

---

# Why Greedy Works

We want to maximize the **number of leaves**, not the total value of the leaves.

Therefore, we should always choose the cheapest available leaf.

Since:

```text
cost = level
```

a leaf at a smaller level is always cheaper than a leaf at a larger level.

BFS processes:

```text
Level 1
Level 2
Level 3
Level 4
...
```

So when we encounter a leaf, all possible leaves with smaller levels have already been processed.

This means the BFS traversal itself provides the required greedy ordering.

---

# Step-by-Step Logic

## 1. Start BFS from the Root

The root is at level:

```text
level = 1
```

We push the root into the queue.

```cpp
queue<Node*> q;
q.push(root);
int level=1;
```

---

## 2. Handle the Root Separately

The root can itself be a leaf.

For example:

```text
    1
```

Here:

```text
root->left == NULL
root->right == NULL
```

Its cost is `1`.

So we check whether the current budget can afford it.

```text
if(level <= k)
```

If yes:

```text
ans++
k -= level
```

---

# 3. Process the Tree Level by Level

The queue contains all nodes of the current level.

```cpp
int size=q.size();
level++;
```

`size` tells us how many nodes belong to the current level.

We process exactly those nodes before moving to the next level.

---

# 4. Check Every Child

For every node, we add its children to the queue.

For example:

```cpp
if(top->left!=NULL){
    q.push(top->left);
}
```

and:

```cpp
if(top->right!=NULL){
    q.push(top->right);
}
```

---

# 5. Detect Leaf Nodes

A node is a leaf when:

```text
left == NULL
right == NULL
```

The code checks this for every newly discovered child.

For example:

```cpp
if(top->left->left==NULL && top->left->right==NULL && level<=k)
```

If the child is a leaf and its cost can be paid:

```text
ans++
k -= level
```

The same logic is applied to the right child.

---

# Why We Can Immediately Take the Leaf

Suppose the current level is `3`.

Every leaf at this level costs:

```text
3
```

Any leaf at a future level will cost:

```text
4, 5, 6, ...
```

Therefore, if we can afford the current leaf, taking it is always better for maximizing the number of leaves.

For example, suppose:

```text
k = 7
```

and future leaf costs are:

```text
3, 3, 4
```

We should take:

```text
3 + 3 = 6
```

giving us `2` leaves.

Taking the future leaf of cost `4` first would leave:

```text
7 - 4 = 3
```

and still only allow one more leaf, giving the same or worse result.

Thus, processing leaves from smaller levels to larger levels gives the greedy solution.

---

# Early Termination

The code contains:

```cpp
if(level>k){
    return ans;
}
```

This is an important optimization.

If the current level becomes greater than the remaining budget, then every leaf at this level or any future level will cost at least:

```text
level > k
```

So no future leaf can be selected.

Therefore, we can immediately return the current answer.

---

# Example Walkthrough

Consider:

```text
        1
       / \
      2   3
     / \ / \
    4  5 6  7
```

and:

```text
k = 5
```

The leaf nodes are:

```text
4 -> level 3
5 -> level 3
6 -> level 3
7 -> level 3
```

BFS reaches level `3`.

First leaf:

```text
k = 5
cost = 3

take it
ans = 1
k = 2
```

Next leaf:

```text
cost = 3
k = 2
```

Cannot afford it.

The remaining leaves also cost `3`, so none can be selected.

Therefore:

```text
answer = 1
```

---

# Why Sorting Is Not Required

A common solution would be:

1. Find all leaf levels.
2. Store their costs.
3. Sort the costs.
4. Select the cheapest ones.

For example:

```text
Leaf costs:
5 3 4 3 6

After sorting:
3 3 4 5 6
```

But BFS already gives us the leaf levels in sorted order:

```text
Level 3 leaves
Level 4 leaves
Level 5 leaves
...
```

Therefore, your solution effectively performs the sorting automatically through the tree traversal.

This saves the extra sorting step.

---

# Code

The following is the exact code used for this solution:

```cpp
/* Binary Tree Node Structure
class Node {
  public:
    int data;
    Node *left;
    Node *right;

    Node(int x) {
        data = x;
        left = nullptr;
        right = nullptr;
    }
};
*/

class Solution {
  public:
    int getCount(Node *root, int k) {
        // code here
        queue<Node*> q;
        q.push(root);
        int level=1;
        
        int ans=0;
        
        if(root->left==NULL && root->right==NULL){
            if(level<=k){
                ans++;
                k-=level;
            }
            
            else{
                return ans;
            }
        }
        
        
        while(!q.empty()){
            int size=q.size();
            level++;
            
            for(int i=0;i<size;i++){
                auto top=q.front();
                q.pop();
                
                if(top->left!=NULL){
                    q.push(top->left);
                    
                    if(top->left->left==NULL && top->left->right==NULL && level<=k){
                        ans++;
                        k-=level;
                    }
                }
                
                if(top->right!=NULL){
                    q.push(top->right);
                    
                    if(top->right->left==NULL && top->right->right==NULL && level<=k){
                        ans++;
                        k-=level;
                    }
                }
            }
            
            if(level>k){
                return ans;
            }
        }
        
        
        return ans;
    }
};
```

---

# Correctness

The algorithm is correct because:

1. BFS visits nodes level by level.
2. The cost of a leaf is exactly its level.
3. Therefore, leaves are encountered in non-decreasing order of cost.
4. To maximize the number of leaves within a budget, the cheapest leaves should always be selected first.
5. Whenever a leaf can be afforded, we select it and reduce the remaining budget.
6. Once the current level exceeds the remaining budget, no leaf at the current or any future level can be selected.

Hence, the algorithm returns the maximum possible number of leaf nodes that can be visited.

---

# Complexity Analysis

Let `n` be the number of nodes in the binary tree.

### Time Complexity

Every node is inserted into and removed from the queue at most once.

Therefore:

```text
Time Complexity: O(n)
```

There is no sorting operation.

---

### Space Complexity

The queue stores nodes belonging to the current/future levels.

In the worst case, a level can contain `O(n)` nodes.

Therefore:

```text
Space Complexity: O(n)
```

---

# Final Complexity

```text
Time  : O(n)
Space : O(n)
```

With:

```text
n <= 10^5
```

this approach is efficient enough.

---

# Key Insight

The most important observation in this solution is:

```text
Cost of leaf = Level of leaf
```

and:

```text
BFS processes levels in increasing order
```

Therefore:

```text
BFS order = increasing leaf cost
```

So we can directly apply the greedy strategy without collecting and sorting leaf costs.

The overall idea is:

```text
Binary Tree
     |
     v
   B
```
