# Check Level Anagrams in Binary Trees

## Problem Statement

Given the roots of two binary trees `root1` and `root2`, determine whether the nodes at every corresponding level of the two binary trees are **anagrams of each other**.

Two levels are considered anagrams if they contain the **same node values with the same frequencies**, regardless of their order.

In other words, for every corresponding level:

* Both levels must contain the same number of nodes.
* Every value appearing in one level must appear the same number of times in the other level.
* The order of the nodes does not matter.

Return `true` if all corresponding levels are anagrams; otherwise, return `false`.

---

## Example 1

### Input

```text
root1 = [1, 3, 2, N, N, 5, 4]
root2 = [1, 2, 3, 4, 5, N, N]
```

The trees can be represented as:

```text
Tree 1:

        1
       / \
      3   2
         / \
        5   4
```

```text
Tree 2:

        1
       / \
      2   3
     / \
    4   5
```

### Level Comparison

#### Level 0

```text
root1: [1]
root2: [1]
```

Both contain:

```text
1
```

So they are anagrams.

#### Level 1

```text
root1: [3, 2]
root2: [2, 3]
```

Both contain:

```text
2, 3
```

The order is different, but the values and frequencies are the same.

So they are anagrams.

#### Level 2

```text
root1: [5, 4]
root2: [4, 5]
```

Again, both contain the same values.

Therefore, every corresponding level is an anagram.

### Output

```text
true
```

---

# Example 2

### Input

```text
root1 = [1, 2, 3, 5, 4]
root2 = [1, 2, 4, 5, 3]
```

The first level is:

```text
root1: [1]
root2: [1]
```

These are anagrams.

The second level is:

```text
root1: [2, 3]
root2: [2, 4]
```

The values are different.

`3` appears in the first tree, while `4` appears in the second tree.

Therefore, the trees do not have anagram levels.

### Output

```text
false
```

---

# Approach

The solution uses **Breadth First Search (BFS)** to process both binary trees level by level.

The main data structure used is:

```cpp
map<int,multiset<int>> mp;
```

Here:

* The `map` key represents the **level number**.
* The `multiset` stores all node values present at that level.
* `multiset` is useful because it keeps duplicate values.

For example, if a level contains:

```text
[2, 3, 3, 5]
```

then its multiset contains:

```text
{2, 3, 3, 5}
```

The two occurrences of `3` are preserved.

This is important because anagrams require the **same frequencies**, not just the same distinct values.

---

# Why Use a Multiset?

Consider these two levels:

```text
Level 1: [2, 3, 3, 5]
Level 2: [2, 3, 5, 5]
```

Both levels contain the same distinct values:

```text
2, 3, 5
```

However, their frequencies are different.

First level:

```text
2 → 1
3 → 2
5 → 1
```

Second level:

```text
2 → 1
3 → 1
5 → 2
```

Therefore, they are **not anagrams**.

A normal `set` would lose duplicate values, but a `multiset` preserves them.

Hence, `multiset<int>` is suitable for this problem.

---

# Step 1: Store Levels of the First Tree

The first BFS traverses `root1` level by level.

```cpp
queue<Node*> q;
q.push(root1);
int level=0;
```

The queue contains nodes that still need to be processed.

For every level:

```cpp
int size=q.size();
```

The value of `size` represents the number of nodes currently present at that level.

Then exactly `size` nodes are processed.

For every node:

```cpp
auto top=q.front();
q.pop();
mp[level].insert(top->data);
```

The node value is inserted into the multiset corresponding to its level.

The children are then added to the queue:

```cpp
if(top->left){
    q.push(top->left);
}

if(top->right){
    q.push(top->right);
}
```

After processing the complete level:

```cpp
level++;
```

The first tree is therefore converted into a level-wise collection of values.

For example:

```text
Tree:

        1
       / \
      2   3
     / \   \
    4   5   6
```

The map conceptually contains:

```text
mp[0] = {1}
mp[1] = {2, 3}
mp[2] = {4, 5, 6}
```

---

# Step 2: Traverse the Second Tree

The second BFS processes `root2` in exactly the same level-by-level manner.

```cpp
queue<Node*> rq;
rq.push(root2);
level=0;
```

For each node in the current level:

```cpp
auto top=rq.front();
rq.pop();
```

The code checks whether the current value exists in the corresponding multiset:

```cpp
if(!mp[level].count(top->data)){
    return false;
}
```

If the value does not exist, then the current level cannot be an anagram.

Therefore, the answer is immediately:

```text
false
```

---

# Step 3: Remove the Matched Value

If the value exists, the code removes **one occurrence**:

```cpp
mp[level].erase(mp[level].find(top->data));
```

This is an important part of the solution.

Suppose:

```text
mp[level] = {2, 3, 3, 5}
```

and the current node has:

```text
3
```

Then:

```cpp
mp[level].find(3)
```

finds one occurrence of `3`.

The `erase()` operation removes only that occurrence.

The multiset becomes:

```text
{2, 3, 5}
```

If another `3` is encountered, it can still be matched.

This ensures that **frequency is correctly checked**.

---

# Step 4: Process Children of the Second Tree

After matching the current node, its children are inserted into the queue:

```cpp
if(top->left){
    rq.push(top->left);
}

if(top->right){
    rq.push(top->right);
}
```

The next level is then processed.

---

# Step 5: Check Remaining Values

After the entire second tree has been processed, the code checks whether any values from the first tree remain unmatched.

```cpp
for(auto &it:mp){
    if(it.second.size()>0){
        return false;
    }
}
```

If any multiset still contains values, it means that `root1` had additional values that were not present in the corresponding levels of `root2`.

Therefore, the trees are not level anagrams.

If all multisets are empty:

```text
true
```

is returned.

---

# Complete Algorithm

```text
1. Create a map where each level stores a multiset of node values.

2. Perform BFS on root1.

3. For every level of root1:
   - Process all nodes belonging to that level.
   - Insert every node value into mp[level].
   - Push the children into the queue.

4. Perform BFS on root2.

5. For every node in each level:
   - Check whether its value exists in mp[level].
   - If it does not exist, return false.
   - If it exists, erase one occurrence from the multiset.
   - Push its children into the queue.

6. After processing root2:
   - Check every multiset in mp.
   - If any value remains, return false.

7. Otherwise, return true.
```

---

# Dry Run

Consider:

```text
Tree 1:

        1
       / \
      3   2
     / \
    5   4
```

and:

```text
Tree 2:

        1
       / \
      2   3
     / \
    4   5
```

## First Tree

After BFS:

```text
mp[0] = {1}
mp[1] = {2, 3}
mp[2] = {4, 5}
```

---

## Second Tree

### Level 0

Current value:

```text
1
```

Check:

```text
mp[0] = {1}
```

`1` exists.

Remove it:

```text
mp[0] = {}
```

---

### Level 1

Current values:

```text
2, 3
```

Initially:

```text
mp[1] = {2, 3}
```

Process `2`:

```text
mp[1] = {3}
```

Process `3`:

```text
mp[1] = {}
```

---

### Level 2

Current values:

```text
4, 5
```

Initially:

```text
mp[2] = {4, 5}
```

Process `4`:

```text
mp[2] = {5}
```

Process `5`:

```text
mp[2] = {}
```

Finally, all multisets are empty.

Therefore:

```text
true
```

is returned.

---

# Handling Duplicate Values

Duplicate values are handled correctly because the solution uses `multiset`.

For example:

```text
Tree 1 level: [2, 3, 3, 5]
Tree 2 level: [3, 2, 5, 3]
```

The first tree stores:

```text
{2, 3, 3, 5}
```

The second tree removes:

```text
3 → {2, 3, 5}
2 → {3, 5}
5 → {3}
3 → {}
```

All values are successfully matched.

Therefore, the levels are anagrams.

---

# Handling Different Frequencies

Consider:

```text
Tree 1 level: [2, 3, 3]
Tree 2 level: [2, 3, 4]
```

Initially:

```text
mp[level] = {2, 3, 3}
```

The values `2` and `3` can be matched.

When `4` is encountered:

```cpp
mp[level].count(4)
```

returns `0`.

Therefore:

```cpp
return false;
```

This correctly identifies that the levels are not anagrams.

---

# Handling Different Tree Heights

The final check:

```cpp
for(auto &it:mp){
    if(it.second.size()>0){
        return false;
    }
}
```

ensures that extra nodes in `root1` are detected.

For example:

```text
Tree 1:

    1
   /
  2
 /
3
```

while:

```text
Tree 2:

    1
   /
  2
```

After processing `root2`, the value `3` remains in the corresponding multiset.

Therefore, the function returns:

```text
false
```

Similarly, if `root2` contains an additional node at a level that does not exist in `root1`, the lookup:

```cpp
mp[level].count(top->data)
```

will fail and the function returns `false`.

---

# Why BFS Is Used

Breadth First Search is naturally suited for this problem because BFS visits a binary tree **level by level**.

For example:

```text
        1
       / \
      2   3
     / \ / \
    4  5 6  7
```

BFS processes:

```text
Level 0 → 1
Level 1 → 2, 3
Level 2 → 4, 5, 6, 7
```

This directly corresponds to the requirement of comparing corresponding levels.

The variable:

```cpp
int size=q.size();
```

is used to determine exactly how many nodes belong to the current level.

---

# Correctness

The algorithm returns `true` if and only if every corresponding level of the two trees contains the same values with the same frequencies.

### Case 1: A value is missing in the second tree

During the second BFS:

```cpp
if(!mp[level].count(top->data)){
    return false;
}
```

If a value from `root2` does not exist in the corresponding level of `root1`, the function immediately returns `false`.

Therefore, different values are correctly detected.

### Case 2: A value occurs too many times in the second tree

Every matched value removes exactly one occurrence:

```cpp
mp[level].erase(mp[level].find(top->data));
```

If the second tree contains more occurrences than the first tree, eventually `count()` becomes zero and the function returns `false`.

Therefore, frequency differences are correctly detected.

### Case 3: The first tree contains unmatched values

After processing the second tree, the remaining multisets are checked.

If any multiset is non-empty:

```cpp
it.second.size()>0
```

then some values from `root1` were not matched.

The function returns `false`.

### Case 4: Every value is matched

If every node from both trees can be matched at the same level and all multisets become empty, then every corresponding level contains exactly the same values with exactly the same frequencies.

Therefore, the function returns `true`.

---

# Complexity Analysis

Let `N` be the number of nodes in the first tree and `M` be the number of nodes in the second tree.

The constraints allow up to `10^5` nodes.

## First BFS

Every node of `root1` is processed once.

For every node, its value is inserted into a `multiset`.

Insertion into a `multiset` takes:

```text
O(log K)
```

where `K` is the number of elements currently stored at that level.

In the worst case:

```text
O(N log N)
```

---

## Second BFS

Every node of `root2` is processed once.

For each node:

* `count()` on the multiset takes logarithmic time.
* `find()` takes logarithmic time.
* `erase()` using the iterator takes constant time after finding the element.

Therefore, the second traversal is:

```text
O(M log M)
```

in the worst case.

---

## Overall Time Complexity

Combining both traversals:

```text
O(N log N + M log M)
```

If both trees contain approximately `N` nodes:

```text
O(N log N)
```

---

## Space Complexity

The map stores all values from `root1`.

The BFS queue can contain nodes from one level of the tree.

Therefore, the auxiliary space is:

```text
O(N)
```

in the worst case.

---

# Complexity Summary

| Operation        |               Complexity |
| ---------------- | -----------------------: |
| BFS on `root1`   |             `O(N log N)` |
| BFS on `root2`   |             `O(M log M)` |
| Final map check  |                   `O(N)` |
| **Overall Time** | **O(N log N + M log M)** |
| **Space**        |                 **O(N)** |

For two trees of comparable size:

```text
Time:  O(N log N)
Space: O(N)
```

---

# Important C++ Detail: `multiset::erase`

The code uses:

```cpp
mp[level].erase(mp[level].find(top->data));
```

This removes **only one occurrence** of `top->data`.

For example:

```text
multiset = {2, 3, 3, 5}
```

If:

```cpp
find(3)
```

returns an iterator to one `3`, then:

```cpp
erase(iterator)
```

removes only that particular occurrence:

```text
{2, 3, 5}
```

It does **not** remove all occurrences of `3`.

This behavior is important for correctly comparing frequencies.

If the code instead used:

```cpp
mp[level].erase(3);
```

then all occurrences of `3` would be removed, which would not correctly handle duplicate values.

---

# Key Takeaways

* BFS is used because the problem requires **level-by-level comparison**.
* A `map` associates each level with its collection of node values.
* A `multiset` preserves duplicate values and their frequencies.
* The first tree is stored level by level.
* The second tree is checked against the stored values.
* `find()` followed by `erase(iterator)` removes exactly one matching occurrence.
* Different values, different frequencies, and different tree heights are correctly detected.
* The solution runs in `O(N log N)` time for trees of comparable size.
* The extra space used is `O(N)`.

---

# Original Code

The code below is kept **exactly as provided**, without modification or optimization.

```cpp
/* Structure of binary tree Node
class Node {
    public:
    int data;
    Node *left, *right;
    Node(int x) {
        data = x;
        left = right = nullptr;
    }
};
*/

class Solution {
  public:
    bool areAnagrams(Node* root1, Node* root2) {
        // code here
        map<int,multiset<int>> mp;
        
        queue<Node*> q;
        q.push(root1);
        int level=0;
        
        
        while(!q.empty()){
            vector<int> temp;
            int size=q.size();
            
            for(int i=0;i<size;i++){
                auto top=q.front();
                q.pop();
                mp[level].insert(top->data);
                
                if(top->left){
                    q.push(top->left);
                }
                
                if(top->right){
                    q.push(top->right);
                }
            }
            
            level++;
        }
        
        queue<Node*> rq;
        rq.push(root2);
        level=0;
        
        while(!rq.empty()){
            vector<int> temp;
            int size=rq.size();
            
            for(int i=0;i<size;i++){
                auto top=rq.front();
                rq.pop();
                if(!mp[level].count(top->data)){
                    return false;
                }
                
                mp[level].erase(mp[level].find(top->data));
                
                if(top->left){
                    rq.push(top->left);
                }
                
                if(top->right){
                    rq.push(top->right);
                }
            }
            
            level++;
        }
        
        for(auto &it:mp){
            if(it.second.size()>0){
                return false;
            }
        }
        
        return true;
    }
};
```

---

# Conclusion

The solution compares the two binary trees **level by level** using BFS. The values of each level in the first tree are stored in a `multiset`, allowing both ordering and duplicate frequencies to be handled correctly.

The second tree is then traversed level by level, matching and removing each value from the corresponding multiset. If every value is matched and no values remain unmatched, the two trees have anagrammatic levels and the function returns `true`.
