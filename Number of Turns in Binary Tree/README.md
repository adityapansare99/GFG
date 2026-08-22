# Number of Turns in Binary Tree

## Problem Statement

Given the root of a binary tree and two node values `p` and `q`, find the number of **turns** required to travel from node `p` to node `q`.

A turn occurs whenever the direction changes:

```text
Left → Right
```

or:

```text
Right → Left
```

If the path between `p` and `q` does not contain any turn, return `-1`.

All node values are distinct.

### Example 1

```text
Input:
p = 5
q = 10
```

The path is:

```text
5 → 2 → 1 → 3 → 6 → 10
```

The directions are:

```text
5 → 2      Left
2 → 1      Left
1 → 3      Right
3 → 6      Left
6 → 10     Right
```

Direction changes occur at:

```text
2 → 1 → 3
3 → 6
6 → 10
```

Therefore:

```text
Answer = 4
```

### Example 2

```text
p = 1
q = 4
```

The path is:

```text
1 → 2 → 4
```

Both movements are in the same direction.

Therefore, there is no turn:

```text
Answer = -1
```

---

## Intuition

The path from `p` to `q` can be divided around their **Lowest Common Ancestor (LCA)**.

For example:

```text
        LCA
       /   \
      p     q
```

We find the LCA first.

Then:

```text
LCA → p
```

and:

```text
LCA → q
```

are two separate paths.

For each path, we need to count how many times the direction changes.

---

## Step 1: Find the LCA

We use the standard recursive LCA approach.

If the current node is:

```text
NULL
```

or is equal to `p` or `q`, return it.

Then recursively search in both subtrees.

If both left and right return a node, the current node is the LCA.

Otherwise, return whichever side contains one of the target nodes.

```text
              LCA
             /   \
            /     \
           p       q
```

This allows us to start counting turns from the correct point.

---

## Step 2: Count Turns From the LCA

The function:

```text id="solver"
solver(root, p, q, prev)
```

uses `prev` to represent the direction of the previous movement.

We use:

```text
prev = 0
```

for moving to the **left**, and:

```text
prev = 1
```

for moving to the **right**.

Suppose the previous movement was left:

```text
prev = 0
```

If we continue to the left:

```text
Left → Left
```

there is no turn.

So the additional cost is:

```text
0
```

But if we move to the right:

```text
Left → Right
```

there is a turn.

So the additional cost is:

```text
1
```

Similarly, if the previous direction was right:

```text
Right → Right = 0 turns
Right → Left  = 1 turn
```

This is handled by:

```text
if(!prev) {
    ans = min({
        ans,
        solver(root->left, p, q, 0),
        1 + solver(root->right, p, q, 1)
    });
}
else {
    ans = min({
        ans,
        1 + solver(root->left, p, q, 0),
        solver(root->right, p, q, 1)
    });
}
```

---

## Dry Run

Consider the path:

```text
5 → 2 → 1 → 3 → 6 → 10
```

The LCA of `5` and `10` is:

```text
1
```

So we process:

```text
        1
       / \
      2   3
     /     \
    5       6
             \
             10
```

### Left Side

Path from LCA toward `5`:

```text
1 → 2 → 5
```

Directions:

```text
Left → Left
```

No direction change.

So this side contributes:

```text
0
```

### Right Side

Path from LCA toward `10`:

```text
1 → 3 → 6 → 10
```

Directions:

```text
Right → Left → Right
```

Turns:

```text
Right → Left = 1
Left → Right = 1
```

So this side contributes:

```text
2
```

The complete path from `5` to `10` also includes the change from the left side to the right side at the LCA.

Therefore:

```text
Total turns = 0 + 2 + 2
            = 4
```

The implementation handles this connection between the two sides with the final adjustment.

---

## Why We Return `-1`

Suppose:

```text
p = 1
q = 4
```

Path:

```text
1 → 2 → 4
```

Both edges go in the same direction:

```text
Left → Left
```

Therefore:

```text
turns = 0
```

But the problem asks us to return `-1` when there are no turns.

So after calculating the answer:

```text
if(ans == 0)
    return -1;
```

---

## Code

```cpp
class Solution {
private:
    Node* LCS(Node* root, int p, int q) {
        if (root == NULL || root->data == p || root->data == q) {
            return root;
        }

        Node* left = LCS(root->left, p, q);
        Node* right = LCS(root->right, p, q);

        if (left && right) {
            return root;
        }
        else if (left) {
            return left;
        }
        else {
            return right;
        }
    }

    int solver(Node* root, int p, int q, int prev) {
        if (root == NULL) {
            return 1e9;
        }

        if (root->data == p || root->data == q) {
            return 0;
        }

        int ans = 1e9;

        if (!prev) {
            ans = min({
                ans,
                solver(root->left, p, q, 0),
                1 + solver(root->right, p, q, 1)
            });
        }
        else {
            ans = min({
                ans,
                1 + solver(root->left, p, q, 0),
                solver(root->right, p, q, 1)
            });
        }

        return ans;
    }

public:
    int numberOfTurns(Node* root, int p, int q) {
        Node* point = LCS(root, p, q);

        int left = solver(point->left, p, q, 0);
        int right = solver(point->right, p, q, 1);

        int ans = 0;

        if (left < 1e9) {
            ans += left;
        }

        if (right < 1e9) {
            ans += right;
        }

        ans++;

        if (point->data == p || point->data == q) {
            ans--;
        }

        if (ans == 0) {
            return -1;
        }

        return ans;
    }
};
```

---

## Complexity

Let `n` be the number of nodes in the binary tree.

### Time Complexity

Finding the LCA can visit every node:

```text
O(n)
```

The `solver` function may also traverse nodes in the relevant subtrees:

```text
O(n)
```

Therefore, the overall time complexity is:

```text
O(n)
```

### Space Complexity

The recursion depth can be as large as the height of the tree.

For a skewed tree:

```text
O(n)
```

For a balanced tree:

```text
O(log n)
```

Therefore, the worst-case space complexity is:

```text
O(n)
```

---

## Key Takeaway

The solution has two main parts:

```text
Find LCA of p and q
        ↓
Split path into two sides
        ↓
Count direction changes on each side
        ↓
Combine the two results
        ↓
If there are zero turns → return -1
```

The important idea is to keep track of the **previous direction**. A turn happens exactly when the current direction is different from the previous direction:

```text
Left → Right = 1 turn
Right → Left = 1 turn

Left → Left = 0 turns
Right → Right = 0 turns
```
