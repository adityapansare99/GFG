# Max Product Subsequence of Size K

## Problem Statement

Given an array `arr[]` of integers and an integer `k`, find a subsequence of size `k` whose product is maximum among all possible subsequences of size `k`.

Return the maximum product that can be obtained.

### Constraints

* `arr.size() <= 30`
* `-10 <= arr[i] <= 10`
* `1 <= k <= arr.size()`

---

## Examples

### Example 1

```text
Input: arr[] = [1, 2, 0, 3], k = 2
Output: 6
```

The subsequence `{2, 3}` gives the maximum product:

```text
2 * 3 = 6
```

### Example 2

```text
Input: arr[] = [1, 2, -1, -3, -6, 4], k = 4
Output: 144
```

The subsequence `{2, -3, -6, 4}` gives:

```text
2 * (-3) * (-6) * 4 = 144
```

---

# Approach

The solution first **sorts the array** and then greedily selects elements.

The important observation is that when selecting elements for a maximum product, it is useful to consider elements in **pairs**.

After sorting:

```text
arr[0] <= arr[1] <= ... <= arr[n-1]
```

For every pair, we consider two important possibilities:

* The two smallest remaining elements:

  ```text
  arr[i] * arr[i+1]
  ```
* The two largest remaining elements:

  ```text
  arr[j] * arr[j-1]
  ```

The two smallest elements are important because they may both be negative.

For example:

```text
[-6, -3, 1, 2, 4]

(-6) * (-3) = 18
2 * 4 = 8
```

So selecting the two negative numbers is better.

Therefore, the algorithm compares the product of the two smallest and two largest remaining elements and chooses the pair with the larger product.

---

# Handling Odd K

The pair-selection process works with two elements at a time.

Therefore, if `k` is odd, one element has to be selected separately.

The code does:

```cpp
if(k%2==1){
    mul*=arr[j];
    j--;
    k--;
}
```

Since the array is sorted, `arr[j]` is the largest element.

After selecting this one element:

```text
k = k - 1
```

so `k` becomes even.

The remaining elements can now be selected in pairs.

For example:

```text
arr = [-5, -2, 1, 3, 6]
k = 3
```

The code first selects:

```text
6
```

and then selects the remaining `2` elements as a pair.

---

# Pair Selection

Once `k` is even, the algorithm uses two pointers:

```text
i = 0
j = n - 1
```

The left pointer represents the two smallest remaining elements:

```cpp
arr[i] * arr[i+1]
```

The right pointer represents the two largest remaining elements:

```cpp
arr[j] * arr[j-1]
```

The algorithm compares these two products.

```cpp
if(arr[i]*arr[i+1]>arr[j]*arr[j-1])
```

### If the left pair is better

```cpp
mul*=(arr[i]*arr[i+1]);
k-=2;
i+=2;
```

The two smallest elements are selected and `i` moves forward by `2`.

### Otherwise

```cpp
mul*=(arr[j]*arr[j-1]);
k-=2;
j-=2;
```

The two largest elements are selected and `j` moves backward by `2`.

This continues until all `k` required elements have been selected.

---

# Why Do We Consider the Two Smallest Elements?

This is the most important observation in the problem.

A pair of negative numbers produces a positive product:

```text
negative × negative = positive
```

For example:

```text
(-10) × (-9) = 90
```

which is much larger than:

```text
2 × 3 = 6
```

Therefore, simply selecting the largest values does not always produce the maximum product.

After sorting, the two smallest elements are the best candidates for forming the largest positive product from negative numbers.

---

# Example of the Greedy Choice

Consider:

```text
arr = [-6, -3, 1, 2, 4]
k = 4
```

The array is sorted:

```text
[-6, -3, 1, 2, 4]
```

The algorithm compares:

```text
Left pair:
(-6) * (-3) = 18

Right pair:
4 * 2 = 8
```

Since:

```text
18 > 8
```

the algorithm chooses:

```text
-6, -3
```

The remaining pair is:

```text
2, 4
```

Therefore, the final product is:

```text
(-6) * (-3) * 2 * 4
= 144
```

---

# Handling a Negative Initial Product

When `k` is odd, the code first selects the largest element:

```cpp
mul*=arr[j];
```

After this selection, it checks:

```cpp
if(mul<0)
```

If the current product is negative, the code follows a separate branch:

```cpp
long long temp=1;
int x=n-1;
while(k>=0 && x>=0){
    temp*=arr[x];
    x--;
    k--;
}
```

This branch calculates the product using the largest remaining elements and returns that result.

---

# Role of Two Pointers

The algorithm uses:

```text
i = 0
j = n - 1
```

where:

* `i` points to the smallest unused elements.
* `j` points to the largest unused elements.

If the left pair is selected:

```text
i += 2
```

If the right pair is selected:

```text
j -= 2
```

Thus, the selected elements are removed from further consideration.

---

# Algorithm

1. Sort the array.
2. Initialize:

   ```text
   mul = 1
   i = 0
   j = n - 1
   ```
3. If `k` is odd:

   * Select the largest element.
   * Move `j` backward.
   * Decrease `k` by `1`.
4. If the current product is negative:

   * Execute the special branch from the code.
   * Return the calculated product.
5. While `k > 0`:

   * Calculate:

     ```text
     arr[i] * arr[i+1]
     ```
   * Calculate:

     ```text
     arr[j] * arr[j-1]
     ```
   * Choose the pair having the larger product.
   * Update the corresponding pointer.
   * Decrease `k` by `2`.
6. Return `mul`.

---

# Correctness Explanation

After sorting, the algorithm considers the two extreme pairs:

```text
Two smallest remaining elements
```

and

```text
Two largest remaining elements
```

The two smallest elements are important because they may both be negative. Their product can therefore be a large positive value.

The two largest elements are important because they contain the largest positive values available.

At every pair-selection step, the algorithm compares the products of these two pairs and chooses the larger product.

When `k` is odd, one element must be selected separately before pair selection. The code selects the largest element and then reduces `k` to an even number.

Thus, the algorithm considers the important possibilities at every step and greedily selects the pair that provides the larger product.

---

# Complexity Analysis

Let `n` be the size of the array.

## Time Complexity

Sorting the array takes:

```text
O(n log n)
```

The pair-selection process takes at most:

```text
O(n)
```

because `k` decreases by `2` after every iteration.

Therefore, the total complexity is:

```text
O(n log n + n)
```

which simplifies to:

```text
O(n log n)
```

## Space Complexity

The algorithm uses only a constant number of variables:

```text
O(1)
```

extra space, excluding the internal space used by the sorting algorithm.

---

# Code

The original solution code is kept **exactly unchanged**:

```cpp
class Solution {
  public:
    int maxProduct(vector<int> &arr, int k) {
        // code here
        int n=arr.size();
        
        sort(arr.begin(),arr.end());
        
        long long mul=1;
        
        int i=0;
        int j=n-1;
        
        if(k%2==1){
            mul*=arr[j];
            j--;
            k--;
        }
        
        if(mul<0){
            long long temp=1;
            int x=n-1;
            while(k>=0 && x>=0){
                temp*=arr[x];
                x--;;
                k--;
            }
            
            return temp;
        }
        
        while(i<j && k>0){
            if(arr[i]*arr[i+1]>arr[j]*arr[j-1]){
                mul*=(arr[i]*arr[i+1]);
                k-=2;
                i+=2;
            }
            
            else{
                mul*=(arr[j]*arr[j-1]);
                k-=2;
                j-=2;
            }
        }
        
        return mul;
        
    }
};
```

---

# Key Takeaway

The core idea is:

```text
Sort the array
      ↓
If k is odd, select one element
      ↓
Compare:
two smallest remaining
        vs
two largest remaining
      ↓
Choose the pair with larger product
      ↓
Repeat until k elements are selected
```

The key observation is:

```text
Negative × Negative = Positive
```

So the maximum product may require choosing the **smallest negative numbers** instead of simply choosing the largest elements.

After sorting, comparing the two smallest and two largest remaining elements provides the necessary greedy choices.
