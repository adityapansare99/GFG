# Minimum Time with 2 Scanners

**Difficulty:** Easy  
**Accuracy:** 19.53%  
**Points:** 2  
**Topic:** Binary Search, Optimization

## Problem Statement

Geek has **n** documents that need to be scanned using two scanners. Scanner 1 takes **s1** units of time to scan one document, while scanner 2 takes **s2** units of time to scan one document.

Both scanners can operate simultaneously, and each scanner can scan only one document at a time. A scanner can start scanning its next document immediately after finishing the current one.

Find the minimum time required to scan all **n** documents.

## Examples

### Example 1

**Input:**
```text
n = 2, s1 = 2, s2 = 4
```

**Output:**
```text
4
```

**Explanation:**

We can either scan both documents using scanner 1, which takes 2 × 2 = 4 units of time, or scan one document using each scanner simultaneously, which takes max(2, 4) = 4 units of time.

Both approaches require 4 units of time.

### Example 2

**Input:**
```text
n = 2, s1 = 1, s2 = 3
```

**Output:**
```text
2
```

**Explanation:**

The optimal approach is to scan both documents using scanner 1, which takes 2 × 1 = 2 units of time.

## Constraints

```text
1 ≤ n, s1, s2 ≤ 10^6
1 ≤ s1 * n, s2 * n ≤ 10^9
```

## Approach: Binary Search

The problem can be solved efficiently using **Binary Search on the number of documents assigned to a scanner**.

Since both scanners operate simultaneously, the total time required depends on the scanner that finishes last.

Instead of checking every possible distribution of documents, we use binary search to find the optimal distribution.

### Key Idea

Let:

- `mini` = Minimum of `s1` and `s2` (faster scanner).
- `maxi` = Maximum of `s1` and `s2` (slower scanner).
- `mid` = Number of documents assigned to the slower scanner.
- `rem` = Remaining documents assigned to the faster scanner.

The time taken by each scanner is:

```text
mint = mini * rem
maxt = maxi * mid
```

Since both scanners work simultaneously:

```text
Total Time = max(mint, maxt)
```

Our objective is to minimize this maximum time.

### Binary Search Logic

1. Initialize the search range from `low = 0` to `high = n`.
2. Calculate `mid` as the number of documents assigned to the slower scanner.
3. Calculate `rem = n - mid` for the faster scanner.
4. Calculate the scanning time for both scanners.
5. Update the minimum answer using `max(mint, maxt)`.
6. If `mint > maxt`, increase `mid` to assign more documents to the slower scanner.
7. Otherwise, decrease `mid` to assign fewer documents to the slower scanner.
8. Continue until the search space is exhausted.

The binary search works because `mint` decreases as `mid` increases, while `maxt` increases. Their maximum reaches its minimum near the point where the two times are balanced.

## C++ Solution

```cpp
class Solution {
  public:
    int minTime(int n, int s1, int s2) {
        // code here
        int maxi=max(s1,s2);
        int mini=min(s1,s2);
        
        int low=0;
        int high=n;
        
        long long ans=1e18;
        
        while(low<=high){
            int mid=(low+high)/2;
            
            int rem=n-mid;
            
            long long mint=mini*rem;
            long long maxt=maxi*mid;
            
            if(ans>=max(mint,maxt)){
                ans=max(mint,maxt);
            }
            
            if(mint>maxt){
                low=mid+1;
            }
            
            else{
                high=mid-1;
            }
        }
        
        return ans;
    }
};
```

## Dry Run

Consider:

```text
n = 5
s1 = 2
s2 = 3
```

**Initialization:**

```text
mini = 2
maxi = 3
low = 0
high = 5
ans = 1e18
```

### Binary Search Iterations

| Iteration | low | high | mid | rem | mint | maxt | ans |
|---|---|---|---|---|---|---|---|
| 1 | 0 | 5 | 2 | 3 | 6 | 6 | 6 |
| 2 | 0 | 1 | 0 | 5 | 10 | 0 | 6 |
| 3 | 1 | 1 | 1 | 4 | 8 | 3 | 6 |

**Final Answer:**
```text
6
```

**Explanation:**

- Faster scanner processes 3 documents in `3 × 2 = 6` units.
- Slower scanner processes 2 documents in `2 × 3 = 6` units.
- Both scanners operate simultaneously.

Therefore:

```text
Minimum Time = max(6, 6) = 6
```

## Complexity Analysis

### Time Complexity: O(log n)

- The binary search operates over the range `[0, n]`.
- In each iteration, the search space is reduced by approximately half.
- Each iteration performs constant-time calculations.

Therefore, the overall time complexity is:

**O(log n)**

### Space Complexity: O(1)

- Only a fixed number of variables are used.
- No additional arrays, vectors, or other data structures are required.

Therefore, the overall space complexity is:

**O(1)**

## Key Takeaways

- Binary search can be used to optimize the distribution of tasks between two parallel workers.
- When two scanners operate simultaneously, the total completion time is determined by the slower finishing scanner.
- The optimal distribution is found near the point where both scanners require approximately equal time.
- Binary search reduces the number of distributions examined from O(n) to O(log n).

---

**Platform:** GeeksforGeeks  
**Problem:** Minimum Time with 2 Scanners  
**Status:** Solved  
**Approach:** Binary Search  
**Time Complexity:** O(log n)  
**Space Complexity:** O(1)