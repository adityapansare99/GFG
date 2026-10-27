# Maximum Weight Transformation of String

## Problem Statement

Given a string `s` consisting only of the characters `A` and `B`, you
can toggle any character. A toggle changes `A` to `B` or `B` to `A`.

The weight of a string is calculated using the following rules:

-   An alternating adjacent pair (`AB` or `BA`) contributes **4** to the
    weight.
-   Each character can belong to at most one pair, so the pairs must not
    overlap.
-   Every character that does not belong to any pair contributes **1**
    to the weight.
-   Each toggle performed decreases the total weight by **1**.

Therefore:

**Weight = Weight of alternating adjacent pairs + Weight of unpaired
characters − Number of toggles**

The task is to find the maximum possible weight obtainable by choosing
pairs and toggling characters optimally.

## Examples

### Example 1

**Input**

``` text
s = "AA"
```

**Output**

``` text
3
```

**Explanation**

The possible transformed strings include `AA`, `AB`, `BA`, and `BB`.
Transforming `AA` into `AB` or `BA` requires one toggle. The alternating
pair contributes `4`, and the toggle decreases the weight by `1`, giving
`4 − 1 = 3`. Leaving the two characters unpaired gives a weight of `2`,
so the maximum is `3`.

### Example 2

**Input**

``` text
s = "ABB"
```

**Output**

``` text
5
```

**Explanation**

The original string already contains the alternating pair `AB`,
contributing `4`. The remaining `B` is unpaired and contributes `1`. No
toggles are required, so the total weight is `4 + 1 = 5`.

## Constraints

-   `1 ≤ s.size() ≤ 10^5`
-   `s` consists only of the characters `A` and `B`.

## Key Observation

At each index `i`, there are two choices:

1.  **Leave the current character unpaired.** It contributes `1`, and
    the next decision starts at `i + 1`.
2.  **Use the current character together with the next character as a
    pair.** This consumes two characters, so the next decision starts at
    `i + 2`.

The value of choosing a pair depends on the two original characters:

-   If `s[i] != s[i + 1]`, the pair is already alternating. It
    contributes `4` and requires no toggle.
-   If `s[i] == s[i + 1]`, one of the two characters can be toggled to
    make the pair alternating. The pair contributes `4`, but the toggle
    costs `1`, so its net contribution is `3`.

Thus, the recurrence for the best weight starting at index `i` is:

\[ dp\[i\] = `\max`{=tex}`\left`{=tex}(1 + dp\[i+1\], pairValue +
dp\[i+2\]`\right`{=tex}) \]

where `pairValue` is `4` when the adjacent characters differ and `3`
when they are equal. The pair option is available only when `i + 1` is
within the string.

The base case is that the best additional weight after the end of the
string is `0`.

------------------------------------------------------------------------

## Solution 1: Recursive Dynamic Programming with Memoization

### Code (unchanged)

``` cpp
class Solution {
    private:
    int solver(string &str,int i,vector<int> &dp){
        if(i>=str.size()){
            return 0;
        }

        if(dp[i]!=-1){
            return dp[i];
        }

        int ans=0;

        ans=max(ans,1+solver(str,i+1,dp));


        if(i<str.size()-1){
            if(str[i]!=str[i+1]){
                ans=max(ans,4+solver(str,i+2,dp));
            }

            else{
                ans=max(ans,3+solver(str,i+2,dp));
            }
        }

        return dp[i]=ans;
    }
  public:
    int getMaxWeight(string &s) {
        // code here
        vector<int> dp(s.size(),-1);

        return solver(s,0,dp);
    }
};
```

### Explanation

-   `solver(str, i, dp)` calculates the maximum weight obtainable from
    the suffix of the string beginning at index `i`.
-   If `i >= str.size()`, there are no characters left, so the function
    returns `0`.
-   `dp[i]` stores the answer for index `i`. If it is not `-1`, the
    answer has already been calculated and can be returned immediately.
-   `ans=max(ans,1+solver(str,i+1,dp));` considers leaving the current
    character unpaired. It adds `1` and continues from the next index.
-   When a next character exists, the code considers pairing the current
    character with it:
    -   Different characters: add `4`, then continue from `i + 2`.
    -   Equal characters: add `3`, accounting for the one toggle needed
        to make the pair alternating, then continue from `i + 2`.
-   `return dp[i]=ans;` stores and returns the best result for the
    current index.
-   `getMaxWeight` initializes the memoization array and starts the
    recursion at index `0`.

### Complexity

-   **Time:** `O(n)`, because each index's answer is calculated at most
    once.
-   **Space:** `O(n)` for the memoization array and up to `O(n)`
    recursion-stack space.

**Note:** For a string close to the maximum constraint, recursive depth
can become large. The iterative versions avoid recursion-stack overhead.

------------------------------------------------------------------------

## Solution 2: Bottom-Up Dynamic Programming (Tabulation)

### Code (unchanged)

``` cpp
class Solution {
  public:
    int getMaxWeight(string &s) {
        // code here
        vector<int> dp(s.size()+1,0);

        for(int i=s.size()-1;i>=0;i--){
            int ans=0;

            ans=max(ans,1+dp[i+1]);


            if(i<s.size()-1){
                if(s[i]!=s[i+1]){
                    ans=max(ans,4+dp[i+2]);
                }

                else{
                    ans=max(ans,3+dp[i+2]);
                }
            }

            dp[i]=ans;
        }

        return dp[0];
    }
};
```

### Explanation

This version evaluates the same recurrence iteratively, starting from
the end of the string and moving toward the beginning.

-   `vector<int> dp(s.size()+1,0);` creates a DP array initialized to
    zero. `dp[i]` represents the maximum weight obtainable from index
    `i` onward. The extra position represents the empty suffix after the
    last character.
-   The loop runs from `s.size()-1` down to `0`, ensuring the values
    needed for the current index have already been computed.
-   `1+dp[i+1]` represents leaving the current character unpaired.
-   If a next character exists, the code compares the pair option:
    -   `4+dp[i+2]` when the two characters differ.
    -   `3+dp[i+2]` when the two characters are equal.
-   `dp[i]=ans;` stores the best result for the current suffix.
-   `return dp[0];` returns the answer for the entire string.

### Complexity

-   **Time:** `O(n)`, because the loop visits every index once.
-   **Space:** `O(n)` for the DP array.

------------------------------------------------------------------------

## Solution 3: Space-Optimized Dynamic Programming

### Code (unchanged)

``` cpp
class Solution {
  public:
    int getMaxWeight(string &s) {
        // code here
        int far=0;
        int next=0;

        for(int i=s.size()-1;i>=0;i--){
            int ans=0;

            ans=max(ans,1+next);


            if(i<s.size()-1){
                if(s[i]!=s[i+1]){
                    ans=max(ans,4+far);
                }

                else{
                    ans=max(ans,3+far);
                }
            }

            far=next;
            next=ans;
        }

        return next;
    }
};
```

### Explanation

The tabulation solution only needs two future DP values at a time:

-   `dp[i+1]`, for leaving the current character unpaired.
-   `dp[i+2]`, for pairing the current character with the next one.

Therefore, the full DP array can be replaced with two variables.

-   `next` represents the DP value for the suffix starting at `i + 1`.
-   `far` represents the DP value for the suffix starting at `i + 2`.
-   `ans` calculates the best weight for the current index using the
    same choices as the previous solutions.
-   `far=next;` shifts the stored values one position backward after the
    current answer has been calculated.
-   `next=ans;` saves the current DP result so it can be used in the
    next iteration.
-   When the loop finishes, `next` contains the maximum weight for the
    complete string, so the function returns it.

The initial values `far=0` and `next=0` represent empty suffixes beyond
the end of the string. The condition `i<s.size()-1` ensures that the
pair option is considered only when a next character exists.

### Complexity

-   **Time:** `O(n)`, because each character is processed once.
-   **Auxiliary space:** `O(1)`, because only a fixed number of integer
    variables are used.

------------------------------------------------------------------------

## Dry Run: `s = "ABB"`

The best decision at each position is shown below. Here, `dp[i]` means
the best weight obtainable from index `i` onward.

  ---------------------------------------------------------------------------
       Index `i` Character(s)     Leave current    Pair option   Best `dp[i]`
                 considered          character:                
                                  `1 + dp[i+1]`                
  -------------- -------------- --------------- -------------- --------------
               2 `B`                `1 + 0 = 1`  Not available            `1`

               1 `BB`               `1 + 1 = 2`    `3 + 0 = 3`            `3`

               0 `AB`               `1 + 3 = 4`    `4 + 1 = 5`            `5`
  ---------------------------------------------------------------------------

At index `1`, the pair `BB` can be changed to an alternating pair with
one toggle, giving a net contribution of `3`. At index `0`, the pair
`AB` already alternates and contributes `4`; the last `B` contributes
`1`. The maximum is therefore **5**.

## Comparison of the Three Implementations

  -----------------------------------------------------------------------
  Feature           Memoization       Tabulation        Space optimized
  ----------------- ----------------- ----------------- -----------------
  Technique         Top-down DP       Bottom-up DP      Bottom-up DP

  Time complexity   `O(n)`            `O(n)`            `O(n)`

  Auxiliary space   `O(n)` plus       `O(n)`            `O(1)`
                    recursion stack                     

  Recursion         Yes               No                No

  Main advantage    Follows the       Iterative and     Uses constant
                    recurrence        easy to trace     extra space
                    naturally                           
  -----------------------------------------------------------------------

## Edge Cases

-   **Single character:** For `s = "A"` or `s = "B"`, no pair is
    possible, so the answer is `1`.
-   **Two equal characters:** For `s = "AA"`, pairing them after one
    toggle gives `3`, which is better than leaving both unpaired for a
    total of `2`.
-   **Two different characters:** For `s = "AB"`, the existing
    alternating pair contributes `4` without a toggle.
-   **All characters equal:** Every selected pair costs one toggle, so
    each such pair has a net contribution of `3`; a remaining unpaired
    character contributes `1`.
-   **Long strings:** The iterative and space-optimized implementations
    avoid recursive-stack growth.

## How to Run

The code is written in C++ and uses standard library components such as
`string`, `vector`, and `max`. Include the required standard headers and
use `std` or the appropriate `std::` prefixes in a standalone program.
On an online judge that provides the required headers and expects a
`Solution` class, submit the relevant implementation in the format
required by that platform.

The three `Solution` classes are **alternative implementations**. Use
only one of them in a single source file, because defining the same
class multiple times causes a redefinition error.

## Conclusion

All three implementations use the same dynamic programming recurrence.
At each index, the algorithm compares leaving one character unpaired
with using the current character and the next character as a pair. A
pre-existing alternating pair contributes `4`, while an equal-character
pair contributes a net `3` after accounting for one toggle. The memoized
and tabulated versions use `O(n)` auxiliary space, while the
space-optimized version achieves `O(1)` auxiliary space without changing
the recurrence.
