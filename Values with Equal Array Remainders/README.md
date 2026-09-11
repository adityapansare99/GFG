# Values with Equal Array Remainders

## Problem Statement

Given an integer array `arr[]`, count the number of positive integers `k` such that all elements of the array leave the same remainder when divided by `k`.

If there are infinitely many such values of `k`, return `-1`.

### Examples

#### Example 1

```text
Input: arr[] = [38, 6, 34]
Output: 3
```

Explanation:

The values of `k` for which all elements leave the same remainder are `1`, `2`, and `4`.

- For `k = 1`, all elements leave remainder `0`.
- For `k = 2`, all elements leave remainder `0`.
- For `k = 4`, all elements leave remainder `2`.

Hence, the answer is `3`.

#### Example 2

```text
Input: arr[] = [3, 2]
Output: 1
```

Explanation:

The only positive integer for which both elements leave the same remainder is `1`.

#### Example 3

```text
Input: arr[] = [5, 5, 5]
Output: -1
```

Explanation:

All elements are equal. Therefore, every positive integer `k` gives the same remainder for all elements. There are infinitely many such values, so the answer is `-1`.

---

## Approach

The key observation is based on the property of equal remainders.

Suppose two numbers `a` and `b` leave the same remainder when divided by `k`.

Then:

```text
a % k = b % k
```

Therefore:

```text
(a - b) % k = 0
```

This means that `k` must be a divisor of:

```text
|a - b|
```

So, for **all elements** to have the same remainder, `k` must divide the difference between every element and a fixed element, which we choose as `arr[0]`.

For every `i`:

```text
k divides |arr[i] - arr[0]|
```

Therefore, `k` must divide the GCD of all these differences:

```text
g = gcd(|arr[1] - arr[0]|,
        |arr[2] - arr[0]|,
        ...
        |arr[n-1] - arr[0]|)
```

Thus, the required values of `k` are exactly the **positive divisors of `g`**.

### Special Case: All Elements Are Equal

If every element is equal to `arr[0]`, then every difference is `0`.

In that case, every positive integer `k` produces the same remainder for all elements.

There are infinitely many valid values of `k`, so the function returns:

```text
-1
```

---

## Algorithm

1. Check whether all elements of the array are equal.
   - If yes, return `-1`.
2. Compute the GCD of:
   ```text
   |arr[i] - arr[0]|
   ```
   for all `i` from `1` to `n-1`.
3. The valid values of `k` are the positive divisors of this GCD.
4. Count the divisors of `g` by iterating from `1` to `sqrt(g)`.
5. For every divisor `i`:
   - Count `i`.
   - If `i` and `g / i` are different, count both.
6. Return the total number of divisors.

---

## Why Does Counting Divisors of GCD Work?

Consider:

```text
arr[] = [38, 6, 34]
```

Take `38` as the reference element.

The differences are:

```text
|6 - 38|  = 32
|34 - 38| = 4
```

Their GCD is:

```text
gcd(32, 4) = 4
```

Therefore, `k` must be a divisor of `4`.

The positive divisors of `4` are:

```text
1, 2, 4
```

Hence:

```text
Answer = 3
```

For these values:

```text
38 % 1 = 0,  6 % 1 = 0,  34 % 1 = 0

38 % 2 = 0,  6 % 2 = 0,  34 % 2 = 0

38 % 4 = 2,  6 % 4 = 2,  34 % 4 = 2
```

All elements have the same remainder.

---

## Correctness Explanation

Let `g` be:

```text
g = gcd(|arr[1] - arr[0]|, |arr[2] - arr[0]|, ..., |arr[n-1] - arr[0]|)
```

### Necessity

If a positive integer `k` makes all array elements have the same remainder, then:

```text
arr[i] % k = arr[0] % k
```

Therefore:

```text
(arr[i] - arr[0]) % k = 0
```

So `k` divides every difference `|arr[i] - arr[0]|`.

Hence, `k` must divide their GCD `g`.

### Sufficiency

If `k` divides `g`, then `k` divides every difference:

```text
|arr[i] - arr[0]|
```

Therefore:

```text
arr[i] ≡ arr[0] (mod k)
```

So every element has the same remainder when divided by `k`.

Thus, the valid values of `k` are exactly the positive divisors of `g`.

The code counts all such divisors, so it returns the correct answer.

---

## Complexity Analysis

Let `n` be the size of the array and `g` be the GCD of all differences.

### Time Complexity

Computing the GCD for all elements takes:

```text
O(n log V)
```

where `V` is the maximum value involved in the differences.

Counting the divisors takes:

```text
O(sqrt(g))
```

Therefore, the total time complexity is:

```text
O(n log V + sqrt(g))
```

### Space Complexity

The algorithm uses only a constant number of variables.

```text
O(1)
```

---

## Code

The following is the original solution code:

```cpp
class Solution {
  public:
    int sameMod(vector<int> &arr) {
        // code here
        int n=arr.size();

        bool check=false;

        for(int i=1;i<n;i++){
            if(arr[i]!=arr[0]){
                check=true;
                break;
            }
        }

        if(check==false){
            return -1;
        }

        int g=0;

        for(int i=1;i<n;i++){
            g=__gcd(g,abs(arr[i]-arr[0]));
        }

        int ans=0;

        for(int i=1;i*i<=g;i++){
            if(g%i==0){
                ans++;
                if(i*i!=g){
                    ans++;
                }
            }
        }

        return ans;
    }
};
```

---

## Key Takeaway

The main idea is:

```text
Same remainder
      ↓
k divides every difference
      ↓
k divides GCD of all differences
      ↓
Valid k = divisors of GCD
      ↓
Count divisors
```

The important mathematical observation is:

```text
a % k = b % k
        ⇓
k | (a - b)
```

So instead of checking every possible `k`, we reduce the problem to finding the GCD of the differences and counting its divisors.
