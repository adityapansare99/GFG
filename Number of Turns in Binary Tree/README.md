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

If the path between the two nodes does not contain any turn, return `-1`.

All node values are distinct.

### Example 1

```text
p = 5
q = 10
```

For the tree:

```text
             1
           /   \
          2     3
         / \   / \
        4   5 6   7
       /       / \
      8       9  10
```

The path from `5` to `10` is:

```text
5 → 2 → 1 → 3 → 6 → 10
```

The directions are:

```text
5 → 2     Left
2 → 1     Left
1 → 3     Right
3 → 6     Left
6 → 10    Right
```

Turns occur at:

```text
2, 1, 3, 6
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

Both movements are to the left:

```text
Left → Left
```

There is no turn.

Therefore:

```text
Answer = -1
```

---

## Intuition

The path between two nodes can be understood using their **Lowest Common Ancestor (LCA)**.

For example:

```text
             LCA
            /   \
           /     \
          p       q
```

The complete path is:

```text
p → LCA → q
```

So first, we find the LCA of `p` and `q`.

Then we calculate the turns on:

```text
LCA → p
```

and:

```text
LCA → q
```

Finally, we account for the connection between the two sides at the LCA.

---

## Step 1: Find the LCA

The `LCS()` function finds the lowest common ancestor.

If the current node is:

```text
NULL
```

or its value is `p` or `q`, we return that node.

Then we search both subtrees.

If both sides contain one of the target nodes:

```text
left != NULL
right != NULL
```

then the current node is the LCA.

Otherwise, we return the side containing the target.

```cpp
Node* left = LCS(root->left, p, q);
Node* right = LCS(root->right, p, q);

if (left && right) {
    return root;
}
```

---

## Step 2: Count Turns

The important part of the solution is the `solver()` function.

```text
solver(root, p, q, prev)
```

Here `prev` represents the direction of the **previous movement**.

We use:

```text
prev = 0 → previous direction was Left
prev = 1 → previous direction was Right
```

Suppose the previous direction was left.

### Previous direction = Left

If we move left again:

```text
Left → Left
```

there is no turn.

So the cost is:

```text
0
```

If we move right:

```text
Left → Right
```

there is a turn.

So the cost is:

```text
1
```

This is handled by:

```cpp
if (!prev) {
    ans = min({
        ans,
        solver(root->left, p, q, 0),
        1 + solver(root->right, p, q, 1)
    });
}
```

---

### Previous direction = Right

If we move right again:

```text
Right → Right
```

there is no turn.

If we move left:

```text
Right → Left
```

there is one turn.

Therefore:

```cpp
else {
    ans = min({
        ans,
        1 + solver(root->left, p, q, 0),
        solver(root->right, p, q, 1)
    });
}
```

---

## Why `prev` Is Important

Consider:

```text
5 → 2 → 1 → 3 → 6 → 10
```

The directions are:

```text
Left
Left
Right
Left
Right
```

Now look at the changes:

```text
Left → Left    = 0
Left → Right   = 1
Right → Left   = 1
Left → Right   = 1
```

However, because we start counting from the LCA, the first movement from the LCA needs a direction assigned to it.

For the left subtree, we start with:

```text
prev = 0
```

because the first edge from the LCA toward the left subtree is a left movement.

For the right subtree, we start with:

```text
prev = 1
```

because the first edge from the LCA toward the right subtree is a right movement.

This allows the `solver()` function to correctly count turns inside each side.

---

## Dry Run

Consider:

```text
p = 5
q = 10
```

The LCA is:

```text
1
```

The path is:

```text
5 → 2 → 1 → 3 → 6 → 10
```

### Left Side

From the LCA:

```text
1 → 2 → 5
```

The initial direction is left:

```text
prev = 0
```

At node `2`, we move to the right child `5`.

Therefore:

```text
Left → Right
```

This is a turn.

So:

```text
left = 1
```

---

### Right Side

From the LCA:

```text
1 → 3 → 6 → 10
```

The initial direction is right:

```text
prev = 1
```

At node `3`, we move left to `6`:

```text
Right → Left
```

This gives one turn.

Then at node `6`, we move right to `10`:

```text
Left → Right
```

This gives another turn.

Therefore:

```text
right = 2
```

---

### Turn at the LCA

The two sides are connected through:

```text
5 → 2 → 1 → 3 → 6 → 10
```

The movement enters the LCA from the left and leaves the LCA through the right.

Therefore:

```text
Left → Right
```

is another turn.

So:

```text
ans = left + right + 1
    = 1 + 2 + 1
    = 4
```

Therefore:

```text
Answer = 4
```

---

## Special Case: LCA Is One of the Nodes

Suppose:

```text
p = 1
q = 4
```

The LCA is `1` itself.

The path is:

```text
1 → 2 → 4
```

Both movements are left:

```text
Left → Left
```

There is no turn.

In this case, we should **not add the extra turn at the LCA**.

Your code handles this using:

```cpp
if (point->data == p || point->data == q) {
    ans--;
}
```

So:

```text
ans = 0
```

and finally:

```cpp
if (ans == 0) {
    return -1;
}
```

Therefore:

```text
Answer = -1
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

Let `N` be the number of nodes in the binary tree.

### Time Complexity

Finding the LCA may visit every node:

```text
O(N)
```

The `solver()` traversal also visits nodes along the relevant subtrees:

```text
O(N)
```

Therefore:

```text
Time Complexity: O(N)
```

### Space Complexity

The solution uses recursion.

The maximum recursion depth is equal to the height of the tree.

Therefore:

```text
Space Complexity: O(H)
```

where `H` is the height of the tree.

For a skewed tree:

```text
H = N
```

so the worst case is:

```text
O(N)
```

For a balanced tree:

```text
H = O(log N)
```

---

## Key Takeaway

The solution can be summarized as:

```text
Find LCA of p and q
        ↓
Find turns from LCA toward p
        ↓
Find turns from LCA toward q
        ↓
If LCA is neither p nor q
add one turn for crossing from one side to the other
        ↓
If total turns = 0
return -1
```

The most important idea is keeping track of the previous direction:

```text
Left → Left   = 0
Left → Right  = 1

Right → Right = 0
Right → Left  = 1
```

This lets us count exactly where the path changes direction.
