# Count Group Occurrences

**Platform:** GeeksforGeeks  
**Difficulty:** Easy  
**Accuracy:** 27.88%  
**Points:** 2  
**Topics:** String, Hashing, Map, Traversal

## Problem Statement

Given a string `s` and an integer `k`, count the number of distinct characters that appear in exactly `k` groups in the string.

A group is defined as one or more consecutive occurrences of the same character.

For example, in the string `"aaabbcca"`, the groups are:

```text
"aaa", "bb", "cc", "a"
```

Here, the character `a` appears in two groups, while `b` and `c` each appear in one group.

## Examples

### Example 1

**Input:**
```text
s = "abc", k = 1
```

**Output:**
```text
3
```

**Explanation:**

The characters `a`, `b` and `c` each appear in exactly one group. Therefore, the answer is 3.

### Example 2

**Input:**
```text
s = "geeksforgeeks", k = 2
```

**Output:**
```text
4
```

**Explanation:**

The characters `g`, `e`, `k` and `s` each appear in exactly two groups. Therefore, the answer is 4.

### Example 3

**Input:**
```text
s = "aaaaa", k = 2
```

**Output:**
```text
0
```

**Explanation:**

The character `a` appears in only one group. Therefore, no character appears in exactly two groups.

## Constraints

```text
1 <= s.size() <= 10^5
1 <= k <= 10^3
s consists only of lowercase English alphabets
```

---

## Approach: Map + Consecutive Character Traversal

### Intuition

The main idea is to count the number of groups in which each distinct character appears instead of counting its total frequency.

Consecutive occurrences of the same character are considered a single group.

For example:

```text
s = "aaabbcca"
```

The groups are:

```text
aaa
bb
cc
a
```

The group counts are:

| Character | Groups |
|---|---:|
| a | 2 |
| b | 1 |
| c | 1 |

If `k = 2`, only the character `a` satisfies the condition.

### Algorithm

1. Initialize a map `mp` to store the number of groups for each character.
2. Traverse the string using a loop.
3. For every character:
   - Increment its group count in the map.
   - Use a `while` loop to skip all consecutive occurrences of the same character.
4. After processing the complete string, traverse the map.
5. Check whether the group count of each character is equal to `k`.
6. If the condition is satisfied, increment the answer.
7. Return the final answer.

### Important Observation

The following logic is the key part of the solution:

```cpp
mp[s[i]]++;

while(i<n && s[i]==s[i+1]){
    i++;
}
```

- `mp[s[i]]++` counts the current group.
- The `while` loop skips consecutive occurrences of the same character.
- When the loop finishes, the outer loop continues from the next different character.

This ensures that every group is counted exactly once.

## C++ Solution

```cpp
class Solution {
  public:
    int getCount(string &s, int k) {
        // code here
        int n=s.size();
        map<char,int> mp;
        
        for(int i=0;i<n;i++){
            mp[s[i]]++;
            
            while(i<n && s[i]==s[i+1]){
                i++;
            }
        }
        
        int ans=0;
        
        for(auto &it:mp){
            if(it.second==k){
                ans++;
            }
        }
        
        return ans;
    }
};
```

## Dry Run

Consider:

```text
s = "aaabbcca"
k = 2
```

### Step 1: Traverse the String

| Iteration | Current Character | Group Identified | Map Update |
|---|---|---|---|
| 1 | a | aaa | a = 1 |
| 2 | b | bb | b = 1 |
| 3 | c | cc | c = 1 |
| 4 | a | a | a = 2 |

The consecutive character traversal skips repeated characters within the same group.

### Step 2: Final Map

```text
a -> 2
b -> 1
c -> 1
```

### Step 3: Count Characters

We need characters appearing in exactly `k = 2` groups.

- `a` → 2 groups → Valid
- `b` → 1 group → Invalid
- `c` → 1 group → Invalid

### Final Output

```text
1
```

## Complexity Analysis

Let `n` be the length of the string and `d` be the number of distinct characters.

### Time Complexity: O(n + d log d)

- The first loop traverses the string.
- The `while` loop skips consecutive occurrences, so every character is processed only once.
- Inserting or updating elements in `map` takes O(log d) time.
- The final map traversal takes O(d) time.

Therefore, the overall time complexity is:

**O(n log d + d)**

Since the string contains only lowercase English alphabets, `d <= 26`. Hence, the practical time complexity is:

**O(n)**

### Space Complexity: O(d)

- The map stores the group count for each distinct character.
- At most 26 lowercase English characters can be stored.

Therefore, the auxiliary space complexity is:

**O(1)** for the given character set.

## Key Takeaways

- A group represents consecutive occurrences of the same character.
- Group counting is different from frequency counting.
- A `while` loop can efficiently skip consecutive duplicate characters.
- A map maintains the number of groups for each distinct character.
- Since the input contains only lowercase English alphabets, the auxiliary space remains constant.

---

**Problem:** Count Group Occurrences  
**Platform:** GeeksforGeeks  
**Status:** Solved  
**Approach:** Map + String Traversal  
**Time Complexity:** O(n) for the given character set  
**Space Complexity:** O(1) for the given character set