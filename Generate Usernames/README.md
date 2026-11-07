# Generate Usernames

**Platform:** GeeksforGeeks  
**Difficulty:** Easy  
**Topics:** Strings, Map, Hashing

## Problem Statement

Given an array of strings `arr[]`, where each string represents the first name of a user, generate a unique username for every entry while maintaining the original order.

The rules are:

1. Initially, all usernames present in the input array are considered reserved.
2. If a username has not been assigned to any previous user, keep it unchanged.
3. If the username is already used, append the smallest positive integer suffix that creates a username that is neither reserved nor previously assigned.
4. Return the array containing the generated usernames.

## Examples

### Example 1

**Input:**
```text
arr = ["aba", "ab", "aba", "aba", "ab"]
```

**Output:**
```text
["aba", "ab", "aba1", "aba2", "ab1"]
```

**Explanation:**

- The first occurrence of `"aba"` remains unchanged.
- The first occurrence of `"ab"` remains unchanged.
- The next `"aba"` becomes `"aba1"`.
- The next `"aba"` becomes `"aba2"` because `"aba1"` is already assigned.
- The next `"ab"` becomes `"ab1"`.

### Example 2

**Input:**
```text
arr = ["a", "a", "a1", "a"]
```

**Output:**
```text
["a", "a2", "a1", "a3"]
```

**Explanation:**

Initially, `"a"` and `"a1"` are reserved.

- The first `"a"` remains unchanged.
- The second `"a"` cannot use `"a1"` because it is reserved, so it becomes `"a2"`.
- The original `"a1"` remains unchanged.
- The last `"a"` becomes `"a3"`.

### Example 3

**Input:**
```text
arr = ["aba1", "aba", "aba"]
```

**Output:**
```text
["aba1", "aba", "aba2"]
```

**Explanation:**

Initially, `"aba1"` and `"aba"` are reserved.

The first occurrences remain unchanged. The next `"aba"` cannot use `"aba1"` because it is reserved, so the generated username becomes `"aba2"`.

## Approach: Map and Two-Pass Processing

The main idea is to first identify all original usernames and then generate unique usernames for duplicate entries.

### 1. First Pass – Identify Original Usernames

- Create a map `mp` to track usernames.
- Create a boolean array `covered`, initialized to `true`.
- Traverse the input array.
- Increase the frequency of each username in the map.
- If a username appears for the first time, mark its position as `false` in `covered`.

This ensures that the first occurrence of every original username is preserved.

It also ensures that all original usernames are reserved before generating any new username.

### 2. Second Pass – Generate Unique Usernames

- Traverse the array again.
- If `covered[i]` is `false`, skip that element because it is already a valid first occurrence.
- Otherwise, initialize a counter `c = 1`.
- Store the original username length in `size`.
- Generate candidates by appending increasing positive integers to the original username.
- Check whether each candidate exists in the map using `mp.count(temp)`.
- Continue until an unused username is found.
- Update the array and insert the generated username into the map.

Finally, return the modified array.

## C++ Solution

```cpp
class Solution {
public:
    vector<string> generateUsernames(vector<string> arr) {
        int n = arr.size();
        map<string, int> mp;
        vector<bool> covered(n, true);

        for (int i = 0; i < n; i++) {
            string temp = arr[i];

            mp[temp]++;

            if (mp[temp] == 1) {
                covered[i] = false;
            }
        }

        for (int i = 0; i < n; i++) {
            string temp = arr[i];

            if (!covered[i]) {
                continue;
            }

            int c = 1;
            int size = temp.size();

            while (mp.count(temp)) {
                temp = temp.substr(0, size);
                temp += to_string(c);
                c++;
            }

            arr[i] = temp;
            mp[temp]++;
        }

        return arr;
    }
};
```

## Dry Run

Consider the input:

```text
arr = ["a", "a", "a1", "a"]
```

**First Pass:**

Initially:

```text
mp = {}
covered = [true, true, true, true]
```

After processing all original usernames:

```text
mp = {
    "a"  : 3,
    "a1" : 1
}

covered = [false, true, false, true]
```

The first occurrence of `"a"` and the original `"a1"` are preserved.

**Second Pass:**

| Index | Original username | Generated username | Reason |
|---|---|---|---|
| 0 | a | a | First occurrence, unchanged |
| 1 | a | a2 | a1 is reserved |
| 2 | a1 | a1 | First occurrence, unchanged |
| 3 | a | a3 | a1 and a2 are already used |

Final output:

```text
["a", "a2", "a1", "a3"]
```

## Complexity Analysis

Let:
- `n` = number of usernames.
- `L` = maximum length of an original username.
- `k` = number of duplicate usernames.

**Time Complexity:**

- First pass: \(O(n \log n)\) map operations.
- Second pass: Each generated candidate requires a map lookup and string construction.
- In the worst case, a duplicate may require checking multiple suffixes.

A general upper bound is:

\[
O(n \log n + k(n+L)^2)
\]

This accounts for repeated map lookups and string construction in the worst case.

**Space Complexity:**

\[
O(n \cdot L + n)
\]

The map stores original and generated usernames, while the `covered` array uses \(O(n)\) space. The generated strings can also require additional storage.

## Key Takeaways

- Use a map to maintain all reserved and already assigned usernames.
- Process the input in two passes to ensure original usernames are reserved before generating duplicates.
- Preserve the first occurrence of every original username.
- For duplicate usernames, try suffixes starting from `1` and select the smallest available one.
- Update the map immediately after generating a username to prevent future duplicates.