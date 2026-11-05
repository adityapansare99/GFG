# Minimum Days

## Problem Statement

Given a string `s` of length `n` containing only lowercase English letters and a permutation array `p[]` containing integers from `0` to `n - 1`.

On the `(i + 1)`th day, the character at index `p[i]` in the string is replaced with `'?'`.

We need to find the **minimum number of days** required so that no two adjacent characters are equal, unless at least one of them is `'?'`.

Formally, for every index `i`:

```text
If s[i] != '?' and s[i+1] != '?',
then s[i] != s[i+1].
```

Return the minimum number of days required to satisfy this condition.

---

## Examples

### Example 1

```text
Input:
s = "aabb"
p = [2, 1, 3, 0]

Output:
2
```

Explanation:

Initially:

```text
aabb
```

**Day 1:** Replace the character at index `2`.

```text
aa?b
```

The first two characters are still equal.

**Day 2:** Replace the character at index `1`.

```text
a??b
```

Now no two adjacent non-question-mark characters are equal.

Therefore:

```text
Answer = 2
```

### Example 2

```text
Input:
s = "abca"
p = [3, 0, 2, 1]

Output:
0
```

The original string already satisfies the required condition.

Therefore, no replacements are needed.

---

## Intuition

The main observation is that **only adjacent equal characters matter**.

If two adjacent characters are different, we do not need to do anything for that pair.

If two adjacent characters are equal, at least one of their positions must be replaced with `'?'`.

For every position, we need to know on which day it will be replaced.

Instead of simulating every day, we can calculate the replacement day of every index and directly determine the answer.

### Step 1: Store the Replacement Day of Every Index

We create an unordered map:

```cpp
unordered_map<int, int> mp;
```

For every position in `p`, we store:

```cpp
mp[p[i]] = i;
```

Here:

- `p[i]` represents the index that will be replaced.
- `i` represents the zero-based day index.

Since the actual day starts from `1`, the actual replacement day is:

```text
mp[index] + 1
```

For example:

```text
p = [2, 1, 3, 0]
```

The mapping becomes:

```text
Index       Replacement Day
  0               4
  1               2
  2               1
  3               3
```

Therefore:

```text
mp[0] = 3
mp[1] = 1
mp[2] = 0
mp[3] = 2
```

### Step 2: Find Adjacent Equal Characters

We traverse the original string and check every adjacent pair:

```cpp
for(int i = 0; i < n - 1; i++)
```

If:

```cpp
s[i] == s[i + 1]
```

then this pair needs at least one replacement.

For example:

```text
s = "aabb"
```

Adjacent pairs:

```text
Index 0, 1 → a, a  (Equal)
Index 1, 2 → a, b  (Different)
Index 2, 3 → b, b  (Equal)
```

Only the pairs `(0,1)` and `(2,3)` need to be considered.

### Step 3: Calculate the Required Day for Each Pair

For an equal adjacent pair `(i, i+1)`, we have two possible replacement days:

```cpp
int day1 = mp[i];
int day2 = mp[i + 1];
```

We only need to replace one of these two positions to make the pair valid.

Therefore, the earliest day on which this pair becomes valid is:

```cpp
min(day1, day2) + 1
```

We take the minimum because replacing either one of the two characters is sufficient.

### Step 4: Find the Maximum Required Day

Every equal adjacent pair must become valid.

Therefore, we need to consider the pair that takes the longest time to become valid.

Your code maintains:

```cpp
ans = max(ans, min(day1, day2));
```

Since `day1` and `day2` are zero-based day indices, we add `1` at the end.

The final formula is:

```text
Answer = Maximum over all equal adjacent pairs
         of (minimum replacement index + 1)
```

If no equal adjacent pair exists, the answer is `0`.

---

## Dry Run

Consider:

```text
s = "aabb"
p = [2, 1, 3, 0]
```

### Step 1: Build the Map

Initially:

```text
mp = {}
```

Iterating through `p`:

| i | p[i] | Mapping |
|---|---|---|
| 0 | 2 | mp[2] = 0 |
| 1 | 1 | mp[1] = 1 |
| 2 | 3 | mp[3] = 2 |
| 3 | 0 | mp[0] = 3 |

Final mapping:

```text
mp[0] = 3
mp[1] = 1
mp[2] = 0
mp[3] = 2
```

Initialize:

```text
ans = INT_MIN
```

### Step 2: Traverse the String

Original string:

```text
a a b b
0 1 2 3
```

**Iteration 1: i = 0**

Check:

```text
s[0] == s[1]
a == a
```

Both characters are equal.

Find their replacement indices:

```text
day1 = mp[0] = 3
day2 = mp[1] = 1
```

The earliest replacement is:

```text
min(3, 1) = 1
```

Update:

```text
ans = max(INT_MIN, 1)
ans = 1
```

Actual day required:

```text
1 + 1 = 2
```

**Iteration 2: i = 1**

Check:

```text
s[1] == s[2]
a == b
```

They are different.

No update is required.

```text
ans = 1
```

**Iteration 3: i = 2**

Check:

```text
s[2] == s[3]
b == b
```

Both characters are equal.

Find their replacement indices:

```text
day1 = mp[2] = 0
day2 = mp[3] = 2
```

The earliest replacement is:

```text
min(0, 2) = 0
```

Update:

```text
ans = max(1, 0)
ans = 1
```

Actual day required:

```text
0 + 1 = 1
```

### Step 3: Calculate Final Answer

After processing all adjacent pairs:

```text
ans = 1
```

Since `ans` stores zero-based day indices, return:

```cpp
return ans + 1;
```

Therefore:

```text
Answer = 1 + 1 = 2
```

---

## Special Case: No Equal Adjacent Characters

Consider:

```text
s = "abca"
```

Adjacent comparisons:

```text
a != b
b != c
c != a
```

No replacement is required.

Therefore, `ans` remains:

```text
INT_MIN
```

Your code handles this case:

```cpp
if(ans == INT_MIN) {
    return 0;
}
```

So the answer is:

```text
0
```

---

## Code

```cpp
class Solution {
public:
    int getMinimumDays(string &s, vector<int> &p) {
        int n = s.size();

        unordered_map<int, int> mp;

        for(int i = 0; i < n; i++) {
            mp[p[i]] = i;
        }

        int ans = INT_MIN;

        for(int i = 0; i < n - 1; i++) {
            if(s[i] == s[i + 1]) {
                int day1 = mp[i];
                int day2 = mp[i + 1];

                ans = max(ans, min(day2, day1));
            }
        }

        if(ans == INT_MIN) {
            return 0;
        }

        return ans + 1;
    }
};
```

---

## Complexity Analysis

Let `n` be the length of the string.

### Time Complexity

**1. Building the map**

We traverse the permutation array once and store the replacement day for every index.

```text
O(n)
```

**2. Checking adjacent characters**

We traverse the string once and check all adjacent pairs.

For each equal pair, we perform constant-time average map lookups and comparisons.

```text
O(n) average
```

Therefore:

```text
Total Time Complexity: O(n)
```

Note: The unordered map operations take average `O(1)` time, with a theoretical worst case of `O(n)` per operation.

### Space Complexity

The unordered map stores the replacement day for all `n` indices.

```text
Space Complexity: O(n)
```

---

## Key Takeaway

The main idea is to avoid simulating every replacement day.

Instead:

```text
Build index → replacement day mapping
             |
             v
Check every adjacent pair
             |
             v
Are both characters equal?
       /             \
     No               Yes
     |                 |
   Ignore       Find replacement days
                       |
                       v
               Take the minimum day
                       |
                       v
               Update maximum answer
                       |
                       v
               Add 1 for 1-based days
```

The most important observation is:

**For every adjacent equal pair, only one of its two positions needs to be replaced. Therefore, the pair becomes valid on the earlier of their two replacement days.**

Since every equal adjacent pair must become valid, the overall answer is the maximum of these earliest replacement days.
