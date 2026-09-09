# Max Digit Sum Number in 1 to n

**Difficulty:** Easy
**Language:** C++

## Problem

Given a number `n`, find a number in the range `[1, n]` such that its **digit sum is maximum**.

If multiple numbers have the same maximum digit sum, return the **largest** number among them.

### Example 1

```text
Input:
n = 48

Output:
48
```

Explanation:

```text
48 → 4 + 8 = 12
39 → 3 + 9 = 12
```

Both `48` and `39` have the maximum digit sum `12`.

Since `48 > 39`, the answer is `48`.

### Example 2

```text
Input:
n = 90

Output:
89
```

Explanation:

```text
90 → 9 + 0 = 9
89 → 8 + 9 = 17
```

Therefore, `89` has the maximum digit sum.

---

# Approach: Recursion / Backtracking

The solution constructs the number digit by digit using recursion.

First, `n` is converted into a string:

```cpp
string str = to_string(n);
```

This allows every digit of `n` to be processed separately.

The recursion keeps track of:

* `i` → current digit position
* `n` → number of digits
* `str` → string representation of the original number
* `currSum` → digit sum of the number constructed so far
* `val` → number constructed so far
* `choose` → whether the constructed number has already become smaller than `n`

---

# Meaning of `choose`

## `choose = 0`

This means the number constructed so far is still equal to the corresponding prefix of `n`.

Therefore, there are two possibilities.

### 1. Keep the current digit

The current digit is taken exactly as it appears in `n`.

```cpp
solver(i+1,n,str,currSum+temp,val*10+temp,0);
```

The number can still remain equal to `n`.

### 2. Decrease the current digit

The current digit is decreased by `1`.

```cpp
solver(i+1,n,str,currSum+temp-1,val*10+temp-1,1);
```

Now the constructed number is smaller than `n`.

Therefore:

```text
choose = 1
```

---

# `choose = 1`

Once the number becomes smaller than `n`, all remaining digits can be chosen as `9`.

```cpp
solver(i+1,n,str,currSum+9,val*10+9,choose);
```

This maximizes the digit sum of the remaining positions.

For example, if:

```text
n = 5834
```

and we reduce the third digit:

```text
5834
  ↓
5829
```

Once the `3` is changed to `2`, the number is already smaller than `5834`, so the remaining digit can be `9`.

---

# Base Case

When all digits have been processed:

```cpp
if(i==n)
```

we have constructed a complete candidate number.

The candidate is compared with the current best answer.

### Larger digit sum

```cpp
if(currSum>mx){
    ans=val;
    mx=currSum;
}
```

If the current digit sum is larger, the candidate becomes the new answer.

### Same digit sum

```cpp
else if(currSum==mx){
    ans=max(ans,val);
}
```

If two numbers have the same digit sum, the larger number is selected as required by the problem.

---

# Code

The following is the original implementation:

```cpp
class Solution {
    private:
    int ans;
    int mx;
    
    void solver(int i,int n,string &str,int currSum,int val,int choose){
        if(i==n){
            if(currSum>mx){
                ans=val;
                mx=currSum;
            }
            
            else if(currSum==mx){
                ans=max(ans,val);
            }
            
            return;
        }
        
        if(choose){
            solver(i+1,n,str,currSum+9,val*10+9,choose);
        }
        
        else{
            int temp=str[i]-'0';
            solver(i+1,n,str,currSum+temp,val*10+temp,0);
            solver(i+1,n,str,currSum+temp-1,val*10+temp-1,1);
        }
    }
  public:
    int findMax(int n) {
        // code Here
        mx=0;
        ans=0;
        
        string str=to_string(n);
        
        solver(0,str.size(),str,0,0,0);
        
        return ans;
    }
};
```

---

# Dry Run

Consider:

```text
n = 48
```

The string representation is:

```text
str = "48"
```

Initially:

```text
i = 0
currSum = 0
val = 0
choose = 0
```

At the first digit `4`, the recursion creates two possibilities.

### Keep `4`

The number starts with:

```text
4_
```

At the second digit `8`, the recursion can keep `8`:

```text
48
```

Digit sum:

```text
4 + 8 = 12
```

Or decrease `8`:

```text
47
```

Digit sum:

```text
4 + 7 = 11
```

### Decrease `4`

The number becomes:

```text
3_
```

Since it is already smaller than `48`, the remaining digit is chosen as `9`:

```text
39
```

Digit sum:

```text
3 + 9 = 12
```

The two candidates with maximum digit sum are:

```text
48 → 12
39 → 12
```

The tie-breaking condition chooses:

```text
48
```

because `48 > 39`.

---

# Why the Approach Works

While the constructed prefix is equal to `n`, we can either:

1. Keep the current digit.
2. Decrease the current digit.

If we decrease a digit, the resulting number becomes smaller than `n`.

After that, choosing `9` for every remaining digit gives the maximum possible digit sum for those remaining positions.

The recursion therefore explores the relevant possibilities and keeps track of the candidate with:

1. Maximum digit sum.
2. Maximum numerical value when the digit sums are equal.

---

# Time Complexity

Let `d` be the number of digits in `n`.

At first glance, the recursion appears to have two choices at every level. However, the second branch sets:

```text
choose = 1
```

Once `choose` becomes `1`, there is only **one recursive call** for every remaining digit.

Therefore, the recursion does not form a complete binary tree of `2^d` nodes.

The possible branches correspond to the position at which the number first becomes smaller than `n`.

For each such position, the remaining digits are processed linearly.

The total number of recursive calls is bounded by:

```text
1 + 2 + 3 + ... + d
```

which is:

```text
O(d²)
```

Therefore:

```text
Time Complexity:  O(d²)
Space Complexity: O(d)
```

Since:

```text
n <= 10^9
```

the number of digits is at most `10`, so the recursion is very small in practice.

---

# Space Complexity

The maximum recursion depth is equal to the number of digits in `n`.

Therefore:

```text
Space Complexity: O(d)
```

The recursion stack is the main additional space used by the solution.

---

# Important Note

The provided implementation is kept **exactly as given above**.

In particular, this line:

```cpp
solver(i+1,n,str,currSum+temp-1,val*10+temp-1,1);
```

assumes that `temp` can be decreased by `1`.

For a digit equal to `0`, this produces `-1`, which is not a valid decimal digit. Thus, there is an edge case in the original implementation for numbers containing `0` at a position where this branch is taken.

The code has intentionally **not been modified**, as this README documents the submitted implementation exactly.

---

# Key Takeaway

The main idea of the solution is:

```text
While equal to n:
    → Keep the current digit
    → Or decrease it by 1

Once smaller than n:
    → Put 9 in all remaining positions
```

The `choose` flag indicates whether the number has already become smaller than `n`.

Finally:

```text
Maximum digit sum → preferred
Equal digit sum   → larger number preferred
```

### Complexity

```text
Time:  O(d²)
Space: O(d)
```

where `d` is the number of digits in `n`.
