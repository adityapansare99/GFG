# Common Nodes in Two BSTs

**Difficulty:** Medium

## Problem Statement

Given the roots `r1` and `r2` of two Binary Search Trees (BSTs), find all nodes that are present in both trees, i.e., the intersection nodes of the two BSTs.

Return the common node values in sorted order.

## Examples

**Example 1:**

- **Input:** `r1 = [5, 1, 10, 0, 4, 7, N, N, N, N, N, N, 9]`
- **Input:** `r2 = [10, 7, 20, 4, 9, N, N]`
- **Output:** `[4, 7, 9, 10]`
- **Explanation:** The values present in both BSTs are `4`, `7`, `9`, and `10`. Hence, the answer is `[4, 7, 9, 10]`.

**Example 2:**

- **Input:** `r1 = [10, 2, 11, 1, 3, N, N]`
- **Input:** `r2 = [2, 1, 3]`
- **Output:** `[1, 2, 3]`
- **Explanation:** The values `1`, `2`, and `3` are present in both BSTs. Hence, the answer is `[1, 2, 3]`.

## Constraints

- `1 ≤ size of binary trees ≤ 10^5`
- `0 ≤ Node.data ≤ 10^9`

---

# Approach 1: Inorder Traversal + Two Pointers

## Intuition

A Binary Search Tree has an important property: its inorder traversal produces the node values in sorted order.

We can use this property to convert both BSTs into sorted arrays and then find their common elements using the two-pointer technique.

The idea is similar to finding the intersection of two sorted arrays.

### Algorithm

**Step 1: Perform Inorder Traversal**

- Traverse the first BST using recursive inorder traversal.
- Store the values in `vec1`.
- Similarly, traverse the second BST and store its values in `vec2`.

Both vectors will contain elements in sorted order.

**Step 2: Apply Two Pointers**

Initialize two pointers:

- `i = 0` for the first vector.
- `j = 0` for the second vector.

Compare the elements at both pointers:

1. If `vec1[i] > vec2[j]`:
   - Increment `j` because the current element in the second vector is smaller.

2. If `vec1[i] < vec2[j]`:
   - Increment `i` because the current element in the first vector is smaller.

3. If both elements are equal:
   - Add the common value to the result.
   - Increment both pointers.

Continue until either vector is completely traversed.

### C++ Code

```cpp
/* Structure of a Binary Search Tree node
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
   void traversal(Node* root,vector<int> &ans){
       if(root==NULL){
           return ;
       }
       
       traversal(root->left,ans);
       ans.push_back(root->data);
       traversal(root->right,ans);
   }
 public:
   vector<int> findCommon(Node* r1, Node* r2) {
       // code here
       vector<int> vec1;
       traversal(r1,vec1);
       
       vector<int> vec2;
       traversal(r2,vec2);
       
       vector<int> res;
       
       int i=0;
       int j=0;
       
       while(i<vec1.size() && j<vec2.size()){
           if(vec1[i]>vec2[j]){
               j++;
           }
           
           else if(vec1[i]<vec2[j]){
               i++;
           }
           
           else{
               res.push_back(vec1[i]);
               i++;
               j++;
           }
       }
       
       return res;
   }
};
```

### Dry Run

**Input:**

```text
r1 = [5, 1, 10, 0, 4, 7, N, N, N, N, N, N, 9]
r2 = [10, 7, 20, 4, 9, N, N]
```

After inorder traversal:

```text
vec1 = [0, 1, 4, 5, 7, 9, 10]
vec2 = [4, 7, 9, 10, 20]
```

Now apply the two-pointer technique:

| vec1[i] | vec2[j] | Comparison | Action |
|---:|---:|---|---|
| 0 | 4 | 0 < 4 | Increment i |
| 1 | 4 | 1 < 4 | Increment i |
| 4 | 4 | Equal | Store 4, increment both |
| 5 | 7 | 5 < 7 | Increment i |
| 7 | 7 | Equal | Store 7, increment both |
| 9 | 9 | Equal | Store 9, increment both |
| 10 | 10 | Equal | Store 10, increment both |
| - | 20 | First vector exhausted | Stop |

**Output:**

```text
[4, 7, 9, 10]
```

### Complexity Analysis

Let:
- `n` = Number of nodes in the first BST.
- `m` = Number of nodes in the second BST.

**Time Complexity: O(n + m)**

- Inorder traversal of the first BST takes `O(n)`.
- Inorder traversal of the second BST takes `O(m)`.
- The two-pointer traversal takes `O(n + m)` because each pointer moves only forward.

Therefore, the overall time complexity is **O(n + m)**.

**Space Complexity: O(n + m)**

- `vec1` stores all nodes of the first BST.
- `vec2` stores all nodes of the second BST.
- The recursion stack requires additional space depending on the height of each tree.

The two vectors dominate the auxiliary space, giving **O(n + m)** space.

---

# Approach 2: Simultaneous Iterative Inorder Traversal Using Two Stacks

## Intuition

In the first approach, we create two separate sorted vectors by performing inorder traversals.

However, we can avoid storing all the node values in vectors.

Since inorder traversal already produces sorted values, we can traverse both BSTs simultaneously using two stacks.

Each stack maintains the path required for iterative inorder traversal.

This allows us to compare the next smallest unprocessed element from both BSTs directly.

### Algorithm

**Step 1: Initialize Two Stacks**

- `s1` stores nodes for the first BST.
- `s2` stores nodes for the second BST.

Also initialize an answer vector `ans`.

**Step 2: Perform Simultaneous Inorder Traversal**

1. Push all left-side nodes of the first BST into `s1`.
2. Push all left-side nodes of the second BST into `s2`.
3. If either stack becomes empty, stop because one BST has no more elements to compare.
4. Get the top nodes from both stacks:
   - `a = s1.top()`
   - `b = s2.top()`

**Step 3: Compare the Node Values**

There are three possible cases:

**Case 1: Both Values Are Equal**

If `a->data == b->data`:

- Both nodes are common.
- Add the value to `ans`.
- Pop both stacks.
- Move both tree pointers to their respective right children.

**Case 2: First Value Is Greater**

If `a->data > b->data`:

- The second BST currently has the smaller value.
- Pop the second stack.
- Move the second tree pointer to `b->right`.

**Case 3: Second Value Is Greater**

If `a->data < b->data`:

- The first BST currently has the smaller value.
- Pop the first stack.
- Move the first tree pointer to `a->right`.

Repeat until one stack becomes empty.

Since both trees are traversed in sorted order, the common values are automatically stored in sorted order.

### C++ Code

```cpp
/* Structure of a Binary Search Tree node
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
 public:
   vector<int> findCommon(Node* r1, Node* r2) {
       // code here
       stack<Node*> s1,s2;
       
       vector<int> ans;
       
       while(true){
           while(r1){
               s1.push(r1);
               r1=r1->left;
           }
           
           while(r2){
               s2.push(r2);
               r2=r2->left;
           }
           
           if(s1.empty() || s2.empty()){
               break;
           }
           
           Node* a=s1.top();
           Node* b=s2.top();
           
           if(a->data==b->data){
               s1.pop();
               s2.pop();
               
               ans.push_back(a->data);
               
               r1=a->right;
               r2=b->right;
           }
           
           else if(a->data>b->data){
               s2.pop();
               r2=b->right;
           }
           
           else{
               s1.pop();
               r1=a->right;
           }
       }
       
       return ans;
   }
};
```

### Dry Run

**Input:**

```text
r1 = [5, 1, 10, 0, 4, 7, N, N, N, N, N, N, 9]
r2 = [10, 7, 20, 4, 9, N, N]
```

The inorder sequences are conceptually:

```text
BST 1: [0, 1, 4, 5, 7, 9, 10]
BST 2: [4, 7, 9, 10, 20]
```

The iterative approach generates these values using stacks instead of storing the complete sequences.

| First BST | Second BST | Comparison | Action |
|---:|---:|---|---|
| 0 | 4 | 0 < 4 | Advance first BST |
| 1 | 4 | 1 < 4 | Advance first BST |
| 4 | 4 | Equal | Add 4 |
| 5 | 7 | 5 < 7 | Advance first BST |
| 7 | 7 | Equal | Add 7 |
| 9 | 9 | Equal | Add 9 |
| 10 | 10 | Equal | Add 10 |
| - | 20 | First BST exhausted | Stop |

**Output:**

```text
[4, 7, 9, 10]
```

### Complexity Analysis

Let:
- `n` = Number of nodes in the first BST.
- `m` = Number of nodes in the second BST.
- `h1` = Height of the first BST.
- `h2` = Height of the second BST.

**Time Complexity: O(n + m)**

- Every node of the first BST is pushed into and popped from its stack at most once.
- Every node of the second BST is also pushed and popped at most once.
- Each comparison and stack operation takes constant time.

Therefore, the overall time complexity is **O(n + m)**.

**Auxiliary Space Complexity: O(h1 + h2)**

- The first stack stores at most `O(h1)` nodes.
- The second stack stores at most `O(h2)` nodes.
- No additional vectors containing all BST values are required.

The result vector requires `O(k)` space, where `k` is the number of common nodes.

Therefore:
- **Auxiliary space:** `O(h1 + h2)`
- **Including output space:** `O(h1 + h2 + k)`

---

# Comparison of Both Approaches

| Parameter | Approach 1: Two Pointers | Approach 2: Two Stacks |
|---|---|---|
| Traversal | Recursive inorder | Iterative inorder |
| Intermediate storage | Two sorted vectors | Two stacks |
| Time Complexity | O(n + m) | O(n + m) |
| Auxiliary Space | O(n + m) | O(h1 + h2) |
| Output Order | Sorted | Sorted |
| Main Technique | Two pointers | Simultaneous traversal |

## Why Is the Second Approach Better?

Both approaches have the same time complexity, but the second approach avoids storing all the nodes of both BSTs in separate vectors.

Instead, it uses stacks to maintain the traversal state and compares the next available values directly.

For balanced BSTs, the stack space is approximately `O(log n + log m)`, whereas the vector-based approach requires `O(n + m)` auxiliary space.

Therefore, the second approach is more space-efficient, especially when the trees are balanced.

## Key Takeaways

- Inorder traversal of a BST produces values in sorted order.
- Two sorted sequences can be compared efficiently using two pointers.
- Simultaneous inorder traversal allows us to find common values without creating complete sorted arrays.
- Two stacks can simulate recursive inorder traversal iteratively.
- The iterative approach reduces auxiliary storage from `O(n + m)` to `O(h1 + h2)`.
- Both approaches naturally return the common values in sorted order.

## Conclusion

The problem can be solved using two different approaches.

The first approach converts both BSTs into sorted vectors and finds their intersection using two pointers.

The second approach performs simultaneous iterative inorder traversal using two stacks, avoiding the need to store all node values.

Both approaches take **O(n + m) time**, but the second approach is more space-efficient because it uses stacks based on tree heights rather than storing complete inorder traversals.