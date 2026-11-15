# Sum of All Digit Subsequences

## Problem Statement

Given a string `s` consisting of digits, find the sum of all digits across all non-empty subsequences of `s`.

Since the answer can be very large, return it modulo `10^9 + 7`.

### Examples

**Example 1:**

- **Input:** `s = "123"`
- **Output:** `24`
- **Explanation:**

  The non-empty subsequences are:

  `[1]`, `[2]`, `[3]`, `[1, 2]`, `[1, 3]`, `[2, 3]`, `[1, 2, 3]`

  Sum of all digits across these subsequences:

  `1 + 2 + 3 + (1 + 2) + (1 + 3) + (2 + 3) + (1 + 2 + 3) = 24`

**Example 2:**

- **Input:** `s = "405"`
- **Output:** `36`
- **Explanation:**

  The non-empty subsequences are:

  `[4]`, `[0]`, `[5]`, `[4, 0]`, `[4, 5]`, `[0, 5]`, `[4, 0, 5]`

  Sum of all digits across these subsequences is `36`.

### Constraints

- `1 <= s.size() <= 10^5`
- `s` consists only of digits from `1` to `9`.

---

## Approach: Mathematical Observation

Generating all subsequences is not efficient because a string of length `n` can have `2^n - 1` non-empty subsequences.

Instead, we can solve this problem using a mathematical observation.

### Key Observation

Consider a digit at index `i`.

For every subsequence containing this digit, each of the remaining `n - 1` digits can either:

1. Be included in the subsequence.
2. Be excluded from the subsequence.

Therefore, the number of subsequences containing a particular digit is:

\[
2^{n-1}
\]

This means **every digit contributes exactly `2^(n-1)` times** to the final answer.

If the sum of all digits in the original string is:

\[
S = \sum_{i=0}^{n-1} (s[i] - '0')
\]

Then the required answer is:

\[
\boxed{Answer = S \times 2^{n-1} \pmod{10^9+7}}
\]

---

## Algorithm

1. Initialize `n` with the length of the string.
2. Initialize `mod = 10^9 + 7`.
3. Calculate the sum of all digits in the string.
4. Calculate `2^(n-1)` using an iterative loop.
5. Multiply the digit sum by the calculated power of 2.
6. Return the result modulo `10^9 + 7`.

---

## C++ Solution

```cpp
class Solution {
public:
    int subsequenceSum(string &s) {
        // code here
        int n=s.size();
        int mod=1e9+7;
        long long sum=0;

        for(int i=0;i<n;i++){
            sum=((s[i]-'0')+sum)%mod;
        }

        long long pow2=1;

        for(int i=0;i<n-1;i++){
            pow2=(pow2*2)%mod;
        }


        return (sum*pow2)%mod;
    }
};
```

---

## Dry Run

Consider:

```text
s = "123"
```

**Step 1: Calculate the sum of digits**

\[
S = 1 + 2 + 3 = 6
\]

**Step 2: Calculate the number of subsequences containing each digit**

The string has `n = 3` digits.

\[
2^{n-1} = 2^{3-1} = 2^2 = 4
\]

Each digit appears in exactly 4 subsequences.

**Step 3: Calculate the final answer**

\[
Answer = 6 \times 4
\]

\[
\boxed{Answer = 24}
\]

**Output:**

```text
24
```

---

## Complexity Analysis

Let `n` be the length of the input string.

### Time Complexity: O(n)

- Calculating the sum of all digits takes `O(n)` time.
- Calculating `2^(n-1)` using the loop takes `O(n)` time.
- Multiplication and modulo operations take constant time.

Therefore:

\[
\boxed{O(n)}
\]

### Space Complexity: O(1)

Only a fixed number of variables are used, regardless of the input size.

\[
\boxed{O(1)}
\]

---

## Key Takeaways

- A string of length `n` has `2^n - 1` non-empty subsequences.
- Every individual digit appears in exactly `2^(n-1)` subsequences.
- Instead of generating all subsequences, we can calculate the answer mathematically.
- Modular arithmetic prevents the result from exceeding the required range.
- The solution efficiently handles strings of length up to `10^5`.

**Final Complexity:**
- **Time:** `O(n)`
- **Auxiliary Space:** `O(1)`