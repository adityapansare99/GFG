# Repeated Pattern Check

## Problem Statement

Given a string `s` consisting of only two characters, `'x'` and `'y'`, verify whether the string can be formed by concatenating substrings that follow the pattern:

\[
x^n y^n
\]

Each valid substring must contain an equal number of consecutive `'x'` characters followed by an equal number of consecutive `'y'` characters.

The string may contain multiple such substrings concatenated together.

### Examples

**Example 1:**

- **Input:** `s = "xxyyxy"`
- **Output:** `true`
- **Explanation:**

  The string can be divided into:

  ```text
  "xxyy" + "xy"
  ```

  - `"xxyy"` contains 2 consecutive `'x'` characters followed by 2 consecutive `'y'` characters.
  - `"xy"` contains 1 `'x'` followed by 1 `'y'`.

  Both substrings follow the required pattern.

**Example 2:**

- **Input:** `s = "xyx"`
- **Output:** `false`
- **Explanation:**

  The string starts with a valid substring `"xy"`, but the remaining `'x'` cannot form a valid substring because it is not followed by a matching `'y'`.

### Constraints

- `1 <= s.size() <= 10^5`
- `s` consists only of the characters `'x'` and `'y'`.

---

## Approach: Single Traversal Using a Counter

We can solve this problem efficiently using a single traversal and a counter.

The idea is to maintain a balance between the number of `'x'` and `'y'` characters in the current substring.

### Key Observation

Every valid substring must follow this structure:

\[
x^n y^n
\]

This means:

- Every `'x'` increases the counter by `1`.
- Every `'y'` decreases the counter by `1`.
- After processing a complete valid substring, the counter must become `0`.

If the counter is not `0` after processing the consecutive `'y'` characters, the current substring is invalid.

### Algorithm

1. Initialize:
   - `c = 0` to maintain the balance.
   - `i = 0` to traverse the string.
2. While `i` is less than the string length:
   - First, process all consecutive `'x'` characters:
     - Increment `c` for every `'x'`.
     - Move `i` forward.
   - Next, process all consecutive `'y'` characters:
     - Decrement `c` for every `'y'`.
     - Move `i` forward.
3. After processing both groups, check the counter:
   - If `c != 0`, return `false`.
   - Otherwise, continue processing the next substring.
4. If the entire string is processed successfully, return `true`.

---

## C++ Solution

```cpp
class Solution {
public:
    bool findPattern(string& s) {
        // code here
        int n=s.size();
        int c=0;
        int i=0;
        while(i<n){
            while(i<n && s[i]=='x'){
                c++;
                i++;
            }

            while(i<n && s[i]=='y'){
                c--;
                i++;
            }

            if(c!=0){
                return false;
            }
        }

        return c==0;
    }
};
```

---

## Dry Run

Consider the following input:

```text
s = "xxyyxy"
```

Initially:

```text
c = 0
i = 0
```

### First Substring: `"xxyy"`

| Character | Operation | Counter |
|---|---|---:|
| `x` | Increment | 1 |
| `x` | Increment | 2 |
| `y` | Decrement | 1 |
| `y` | Decrement | 0 |

The counter becomes `0`, so the first substring is valid.

### Second Substring: `"xy"`

| Character | Operation | Counter |
|---|---|---:|
| `x` | Increment | 1 |
| `y` | Decrement | 0 |

Again, the counter becomes `0`, so the second substring is valid.

### Final Result

All substrings follow the required pattern.

```text
Output = true
```

---

## Complexity Analysis

Let `n` be the length of the string.

### Time Complexity: O(n)

- The outer `while` loop processes the string.
- The inner loops process consecutive `'x'` and `'y'` characters.
- Every character is visited exactly once.
- No character is processed again.

Therefore:

\[
\boxed{O(n)}
\]

### Auxiliary Space Complexity: O(1)

- Only three variables (`n`, `c`, and `i`) are used.
- No additional data structure is required.

Therefore:

\[
\boxed{O(1)}
\]

---

## Key Takeaways

- A counter can efficiently track the balance between two character groups.
- Every valid substring must contain equal numbers of consecutive `'x'` and `'y'` characters.
- Processing the two groups separately ensures that the required order `x` followed by `y` is maintained.
- Checking the counter after each pair of groups validates every substring independently.
- The solution processes the string in a single traversal without using extra space.

**Final Complexity:**
- **Time:** `O(n)`
- **Auxiliary Space:** `O(1)`