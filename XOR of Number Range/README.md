# XOR of Number Range

## Problem Statement

Given two integers `l` and `r`, find the bitwise XOR of all integers in the range `[l, r]`, including both endpoints.

### Examples

**Example 1:**

- **Input:** `l = 4, r = 8`
- **Output:** `8`
- **Explanation:**

  XOR of all integers from 4 to 8:

  ```text
  4 ^ 5 ^ 6 ^ 7 ^ 8 = 8
  ```

**Example 2:**

- **Input:** `l = 2, r = 4`
- **Output:** `5`
- **Explanation:**

  ```text
  2 ^ 3 ^ 4 = 5
  ```

**Example 3:**

- **Input:** `l = 5, r = 9`
- **Output:** `5`
- **Explanation:**

  ```text
  5 ^ 6 ^ 7 ^ 8 ^ 9 = 5
  ```

### Constraints

- `1 <= l <= r <= 10^9`

---

## Approach: Prefix XOR Using Bitwise Properties

Instead of calculating the XOR of every number between `l` and `r`, we can use a mathematical observation about the XOR of numbers from `0` to `n`.

### 1. XOR Pattern from 0 to n

Define the prefix XOR function as:

**X(n) = 0 ^ 1 ^ 2 ^ ... ^ n**

The result follows a repeating pattern based on the remainder when `n` is divided by `4`.

| Remainder (`n % 4`) | XOR from 0 to n |
|:---:|:---:|
| 0 | `n` |
| 1 | `1` |
| 2 | `n + 1` |
| 3 | `0` |

This pattern occurs because XOR has two important properties:

- `a ^ a = 0`
- `a ^ 0 = a`

Also, XOR is associative and commutative, so identical values cancel each other.

### 2. XOR of a Range

We need the XOR of all numbers from `l` to `r`.

Using the prefix XOR function:

```text
X(r) = 0 ^ 1 ^ 2 ^ ... ^ r

X(l - 1) = 0 ^ 1 ^ 2 ^ ... ^ (l - 1)
```

When we XOR these two results, all numbers before `l` cancel out.

Therefore, the required answer is:

```text
Range XOR = X(r) ^ X(l - 1)
```

This allows us to calculate the answer in constant time.

---

## Algorithm

### Helper Function: `xorVal(n)`

1. Check the remainder of `n % 4`.
2. If the remainder is `0`, return `n`.
3. If the remainder is `1`, return `1`.
4. If the remainder is `2`, return `n + 1`.
5. Otherwise, return `0`.

### Main Function: `findXOR(l, r)`

1. Calculate the prefix XOR up to `r`.
2. Calculate the prefix XOR up to `l - 1`.
3. XOR both results.
4. Return the final answer.

---

## C++ Solution

```cpp
class Solution {
    int xorVal(int n){
        if(n%4==0){
            return n;
        }

        else if(n%4==1){
            return 1;
        }

        else if(n%4==2){
            return n+1;
        }

        else{
            return 0;
        }
    }
public:
    int findXOR(int l, int r) {
        // code here
        return xorVal(r)^xorVal(l-1);
    }
};
```

---

## Dry Run

Consider the following input:

```text
l = 4
r = 8
```

### Step 1: Calculate XOR from 0 to r

Here, `r = 8`.

Since:

```text
8 % 4 = 0
```

According to the XOR pattern:

```text
xorVal(8) = 8
```

### Step 2: Calculate XOR from 0 to l - 1

Here, `l - 1 = 3`.

Since:

```text
3 % 4 = 3
```

According to the XOR pattern:

```text
xorVal(3) = 0
```

### Step 3: Calculate Range XOR

```text
Answer = xorVal(8) ^ xorVal(3)
       = 8 ^ 0
       = 8
```

### Final Output

```text
8
```

---

## Complexity Analysis

### Time Complexity: O(1)

- The helper function performs a constant number of conditional checks.
- The main function makes two helper function calls and one XOR operation.
- No loop or recursion is used.

Therefore, the overall time complexity is **O(1)**.

### Auxiliary Space Complexity: O(1)

- Only a fixed number of variables are used.
- No additional data structures are required.

Therefore, the auxiliary space complexity is **O(1)**.

---

## Key Takeaways

- XOR of a number with itself is `0`.
- XOR with `0` leaves the number unchanged.
- Prefix XOR from `0` to `n` follows a repeating pattern based on `n % 4`.
- Range XOR can be calculated using two prefix XOR values.
- This mathematical approach avoids iterating through the entire range.

**Final Complexity:**
- **Time:** `O(1)`
- **Auxiliary Space:** `O(1)`