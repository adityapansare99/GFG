# Transform String

## Problem Statement

Given two strings `s1` and `s2`, find the **minimum number of operations** required to transform `s1` into `s2`.

The only allowed operation is:

> Select a character from `s1` and insert it at the beginning of `s1`.

If the transformation is not possible, return `-1`.

### Example

```text id="8p0x9j"
Input:
s1 = "abcd"
s2 = "cdab"

Output:
2
```

One possible transformation is:

```text id="1eq8z4"
abcd
```

Move `b` to the front:

```text id="p3m3e4"
bacd
```

Move `a` to the front:

```text id="7jgd5m"
abcd
```

The above sequence does not produce `cdab`, so instead we need to select characters from the original ordering appropriately.

The important observation is that characters moved to the front change the ordering of the remaining characters.

---

## Intuition

There are two important observations.

### 1. Character frequencies must be equal

The operation only moves characters.

It never:

* adds a character
* removes a character

Therefore, `s1` and `s2` must contain exactly the same number of every character.

We use a map to count the frequencies.

For every character in `s1`:

```text id="xj8d5a"
mp[s1[i]]++
```

For every character in `s2`:

```text id="tqj6x9"
mp[s2[i]]--
```

If anything remains in the map, the transformation is impossible.

Therefore:

```text id="6y3y4v"
return -1
```

---

## 2. Find the longest matching suffix

The operation always moves a selected character to the **front**.

This means that characters that are already in their correct relative positions at the end do not need to be moved.

So we compare both strings from the **right side**.

We use:

```text id="l8j3k0"
i = s1.size() - 1
j = s2.size() - 1
```

If:

```text id="v8y0qy"
s1[i] == s2[j]
```

the character can stay where it is, so we move both pointers backward.

Otherwise, `s1[i]` must be moved to the front:

```text id="z4i8m8"
ans++
i--
```

The number of characters that need to be moved is the minimum number of operations.

---

## Dry Run

Consider:

```text id="0h44z9"
s1 = "abc"
s2 = "cab"
```

First check frequencies.

```text id="p5sv8x"
s1: a = 1, b = 1, c = 1
s2: a = 1, b = 1, c = 1
```

So transformation is possible.

Now compare from the right.

```text id="h8h2tm"
s1 = a b c
         ↑ i

s2 = c a b
         ↑ j
```

Compare:

```text id="8zv6z5"
c != b
```

So `c` needs to be moved to the front.

```text id="1e6gsh"
ans = 1
i--
```

Now:

```text id="y9o5j8"
s1: a b
       ↑ i

s2: c a b
       ↑ j
```

Compare:

```text id="7p7z5u"
b == b
```

Keep it.

Move both pointers.

```text id="u0v0jw"
i--
j--
```

Now:

```text id="4a0a5v"
s1: a
      ↑ i

s2: c a b
      ↑ j
```

Compare:

```text id="jjq3z6"
a == a
```

Keep it.

Therefore:

```text id="q9y8wh"
ans = 1
```

The minimum number of operations is:

```text id="3z7g76"
1
```

Indeed:

```text id="5b6j5d"
abc
↓ move c to front
cab
```

---

## Another Example

Consider:

```text id="w6p0tg"
s1 = "abcd"
s2 = "cdab"
```

Compare from the end:

```text id="m3z4c2"
d != b
```

Move `d`:

```text id="1f0m8f"
ans = 1
```

Next:

```text id="0p2xyr"
c != a
```

Move `c`:

```text id="b9s9k7"
ans = 2
```

Now:

```text id="zyh9v7"
b == b
```

and:

```text id="4z8v9y"
a == a
```

So:

```text id="b6h6ms"
Answer = 2
```

Transformation:

```text id="v6y4uo"
abcd
↓ move d
dabc
↓ move c
cdab
```

---

## Code

```cpp id="s8m8cy"
class Solution {
public:
    int transform(string &s1, string &s2) {
        map<char, int> mp;

        for (int i = 0; i < s1.size(); i++) {
            mp[s1[i]]++;
        }

        for (int i = 0; i < s2.size(); i++) {
            mp[s2[i]]--;

            if (mp[s2[i]] == 0) {
                mp.erase(s2[i]);
            }
        }

        if (mp.size() != 0) {
            return -1;
        }

        int i = s1.size() - 1;
        int j = s2.size() - 1;

        int ans = 0;

        while (i >= 0 && j >= 0) {
            if (s1[i] == s2[j]) {
                i--;
                j--;
            }
            else {
                ans++;
                i--;
            }
        }

        return ans;
    }
};
```

---

## Complexity

Let `n` be the length of the strings.

### Time Complexity

Counting characters in `s1`:

```text id="v1k1ne"
O(n log 26)
```

Counting characters in `s2`:

```text id="5qf1vh"
O(n log 26)
```

Since the character set is constant, this is effectively:

```text id="t6zj9g"
O(n)
```

The two-pointer traversal also takes:

```text id="fl0h94"
O(n)
```

Therefore:

```text id="kq6x0p"
Time Complexity: O(n)
```

### Space Complexity

The map stores at most the number of distinct characters.

For a standard character set, this is constant:

```text id="1q6y3v"
O(1)
```

---

## Key Takeaway

The main idea is:

```text id="d9x8uo"
Check character frequencies
        ↓
If frequencies differ → return -1
        ↓
Compare s1 and s2 from the end
        ↓
Matching characters can stay
        ↓
Non-matching characters must be moved
        ↓
Count those characters
        ↓
Answer = number of required moves
```

The key observation is that moving characters to the **front** allows us to preserve a suffix of the original string. Therefore, we find the longest suffix that already matches `s2` and move all remaining characters to the front.
