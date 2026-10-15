# Maximum Without 3 Consecutive Set Bits

## Problem Statement

Given a non-negative integer `n`, we can only change a set bit (`1`) to an unset bit (`0`). The task is to find the maximum possible value of `n` such that its binary representation does not contain three consecutive set bits (`111`), after performing zero or more allowed operations.

## Difficulty

- **Difficulty:** Medium
- **Accuracy:** 58.04%
- **Submissions:** 30K+
- **Points:** 4

## Examples

### Example 1

**Input:**
```text
n = 2
```

**Output:**
```text
2
```

**Explanation:**

The binary representation of `2` is `10`. It does not contain three consecutive set bits, so no changes are required.

### Example 2

**Input:**
```text
n = 7
```

**Output:**
```text
6
```

**Explanation:**

The binary representation of `7` is `111`, which contains three consecutive set bits. Changing the rightmost set bit to `0` gives:

```text
111 -> 110
```

The resulting binary representation is `110`, which represents `6`.

## Constraints

```text
0 <= n <= 10^9
```

## Approach

The solution scans the binary representation of `n` from the most significant bit to the least significant bit.

It maintains a counter `c` to track the number of consecutive set bits encountered during the traversal.

1. Initialize `c` to `0`.
2. Traverse the bits of `n` from position `31` down to position `0`.
3. For each bit:
   - If the bit is `1`, increment `c`.
   - If the bit is `0`, reset `c` to `0`.
4. Whenever `c` becomes `3`, a sequence of three consecutive set bits has been detected.
5. Use the bitwise expression `n = ((1 << i) ^ n)` to toggle the bit at position `i` from `1` to `0`.
6. Reset `c` to `0` and continue scanning.
7. Return the modified value of `n`.

The code uses bitwise operators to inspect and modify individual bits without converting the integer into a binary string.

## Algorithm

```text
1. Initialize c = 0.
2. Iterate i from 31 down to 0.
3. Check whether the bit at position i is set.
4. If set, increment c; otherwise, reset c to 0.
5. If c becomes 3:
   a. Toggle the bit at position i using XOR.
   b. Reset c to 0.
6. Return n.
```

## Bitwise Operations Used

| Operation | Purpose |
|---|---|
| `n >> i` | Shifts the bits of `n` right by `i` positions. |
| `& 1` | Extracts the bit at position `i`. |
| `1 << i` | Creates a value with only bit `i` set. |
| `^` (XOR) | Toggles the selected bit. |

For example, if `n = 7`, its binary representation is `111`. When the code detects three consecutive set bits, it toggles the bit at the current position using XOR, producing `110`, which represents `6`.

## Complexity Analysis

**Time Complexity:** `O(1)`

The algorithm iterates over a fixed number of 32 bit positions. Therefore, the number of operations is constant.

**Space Complexity:** `O(1)`

The algorithm uses only a constant number of additional variables, regardless of the input value.

## C++ Solution

The following code is preserved from the provided implementation.

```cpp
class Solution {
 public:
   int maxValue(int n) {
       // code here
       int ans=0;
       int c=0;
       
       for(int i=31;i>=0;i--){
           if(((n>>i)&1)==1){
               c++;
           }
           
           else{
               c=0;
           }
           
           if(c==3){
               n=((1<<i)^n);
               c=0;
           }
       }
       
       
       return n;
   }
};
```

## Key Concepts

- Binary representation of integers
- Bit manipulation
- Bitwise AND (`&`)
- Bitwise XOR (`^`)
- Bit shifting (`<<`, `>>`)
- Consecutive bit counting

## Conclusion

This solution uses bit manipulation to scan the binary representation of an integer and eliminate detected sequences of three consecutive set bits. It works in constant time and uses constant extra space because it processes a fixed number of bit positions.
