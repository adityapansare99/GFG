# Roll Characters of String

**Platform:** GeeksforGeeks  
**Difficulty:** Medium  
**Topics:** Strings, Arrays, Prefix/Suffix Sum, Frequency Counting

## 1. Problem Statement

Given a string `s` consisting of lowercase English letters and an integer array `roll[]`, perform a sequence of roll operations on the string.

For each value `roll[i]`, increment each of the first `roll[i]` characters of the string by one position in the English alphabet.

After `'z'`, the character wraps around to `'a'`.

Return the final string after applying all roll operations.

**Note:** A roll operation affects the current state of the string, including all previous modifications.

### Examples

#### Example 1

**Input:**

```text
s = "bca"
roll[] = [1, 2, 3]
```

**Output:**

```text
"eeb"
```

**Explanation:**

Initially:

```text
bca
```

Operation 1: `roll[0] = 1`

Roll the first character:

```text
bca -> cca
```

Operation 2: `roll[1] = 2`

Roll the first two characters:

```text
cca -> dda
```

Operation 3: `roll[2] = 3`

Roll all three characters:

```text
dda -> eeb
```

The final string is `"eeb"`.

#### Example 2

**Input:**

```text
s = "zcza"
roll[] = [1, 1, 3, 4]
```

**Output:**

```text
"debb"
```

**Explanation:**

Initially:

```text
zcza
```

After rolling the first character:

```text
zcza -> acza
```

After rolling the first character again:

```text
acza -> bcza
```

After rolling the first three characters:

```text
bcza -> cdaa
```

After rolling all four characters:

```text
cdaa -> debb
```

The final string is `"debb"`.

### Constraints

- `1 <= s.size(), roll.size() <= 10^5`
- `1 <= roll[i] <= s.size()`
- `s` consists only of lowercase English letters.

## 2. Approach: Suffix Sum

The solution uses a suffix-sum technique to avoid repeatedly modifying the string for every roll operation.

### Key Observation

A roll operation with value `x` affects the first `x` characters, meaning positions:

\[
0,1,2,\ldots,x-1
\]

Instead of performing every operation character by character, we count the number of operations that affect each position.

For example, consider:

```text
s = "bca"
roll = [1, 2, 3]
```

The operations affect these positions:

| Roll value | Affected positions (0-based) |
|---:|---|
| 1 | 0 |
| 2 | 0, 1 |
| 3 | 0, 1, 2 |

The total number of increments received by each character is:

```text
Position:       0  1  2
Total rolls:    3  2  1
```

Therefore, the string can be updated directly using these accumulated counts.

### Why use a suffix sum?

The code initially counts how many operations end at each position using the `suff` array.

It then traverses the array backward, accumulating the counts from right to left. This converts the operation counts into the total number of increments affecting each character.

Finally, each character is shifted by its accumulated count, using modulo `26` to handle alphabet wraparound.

## 3. Algorithm

1. Calculate the length of the string `s` and store it in `n`.
2. Calculate the number of roll operations and store it in `m`.
3. Create a vector `suff` of size `n`, initialized to zero.
4. For each value in `roll`:
   - Decrement the roll value by one to convert it to a 0-based index.
   - Increment the corresponding position in `suff`.
5. Traverse `suff` backward from `n - 2` to `0`.
   - Add the next position's accumulated count to the current position.
6. Traverse the string from left to right.
   - Convert each character to a zero-based alphabet position.
   - Add the accumulated roll count.
   - Apply modulo `26`.
   - Convert the result back to a lowercase character.
7. Return the modified string.

## 4. C++ Implementation

The following is your original code, preserved without changes.

```cpp
class Solution {
  public:
    string findRollOut(string& s, vector<int>& roll) {
        // code here
        int n=s.size();
        int m=roll.size();
        
        vector<int> suff(n,0);
        
        for(int i=0;i<m;i++){
            suff[roll[i]-1]++;
        }
        
        for(int i=n-2;i>=0;i--){
            suff[i]+=suff[i+1];
        }
        
        for(int i=0;i<n;i++){
            s[i]=(((s[i]-'a')+suff[i])%26)+'a';
        }
        
        return s;
    }
};
```

## 5. Detailed Code Explanation

### Step 1: Calculate the string length

```cpp
int n=s.size();
```

Stores the number of characters in the string.

For example:

```text
s = "bca"
n = 3
```

### Step 2: Calculate the number of roll operations

```cpp
int m=roll.size();
```

Stores the number of operations in the `roll` array.

For example:

```text
roll = [1, 2, 3]
m = 3
```

### Step 3: Initialize the suffix array

```cpp
vector<int> suff(n,0);
```

Creates an integer vector of size `n`, with every element initialized to zero.

For example:

```text
suff = [0, 0, 0]
```

This vector first stores the frequency of roll operations ending at each position. After the backward traversal, it stores the total number of rolls affecting each character.

### Step 4: Count roll operations

```cpp
for(int i=0;i<m;i++){
    suff[roll[i]-1]++;
}
```

For each roll operation, the code increments the position `roll[i] - 1`.

The subtraction converts the 1-based roll value into a 0-based index.

For example:

```text
roll = [1, 2, 3]
```

The operations increment the following positions in `suff`:

- `roll[0] = 1`: increment `suff[0]`.
- `roll[1] = 2`: increment `suff[1]`.
- `roll[2] = 3`: increment `suff[2]`.

The resulting vector is:

```text
suff = [1, 1, 1]
```

### Step 5: Calculate the suffix sums

```cpp
for(int i=n-2;i>=0;i--){
    suff[i]+=suff[i+1];
}
```

This loop traverses the vector backward, accumulating the values from the next position.

The recurrence is:

\[
suff[i]=suff[i]+suff[i+1]
\]

For the example above:

```text
Before: [1, 1, 1]
```

Processing from right to left:

- At `i = 1`, `suff[1] = 1 + 1 = 2`.
- At `i = 0`, `suff[0] = 1 + 2 = 3`.

The final vector becomes:

```text
suff = [3, 2, 1]
```

These values represent the number of increments each character receives.

### Step 6: Update the characters

```cpp
for(int i=0;i<n;i++){
    s[i]=(((s[i]-'a')+suff[i])%26)+'a';
}
```

This loop updates every character using its accumulated roll count.

The expression has four main parts.

**Convert the character into a number**

```cpp
s[i]-'a'
```

Maps lowercase letters to values from `0` to `25`.

For example:

```text
'a' -> 0
'b' -> 1
'c' -> 2
'z' -> 25
```

**Add the number of rolls**

```cpp
(s[i]-'a')+suff[i]
```

Adds the accumulated number of increments to the character's alphabet position.

**Handle alphabet wraparound**

```cpp
(...)%26
```

Keeps the result between `0` and `25`.

For example, shifting `'z'` by one position gives:

\[
(25+1)\bmod 26=0
\]

The resulting character is `'a'`.

**Convert back to a character**

```cpp
(... % 26)+'a'
```

Converts the resulting alphabet position back into a lowercase character.

### Step 7: Return the string

```cpp
return s;
```

Returns the modified string after all roll operations have been accounted for.

The string is updated in place, so the original string passed by reference is modified.

## 6. Dry Run

Consider Example 1:

```text
s = "bca"
roll = [1, 2, 3]
```

### Step 1: Initialize variables

```text
n = 3
m = 3
suff = [0, 0, 0]
```

### Step 2: Count the roll endpoints

Process the roll array:

| `i` | `roll[i]` | Updated position | `suff` |
|---:|---:|---:|---|
| 0 | 1 | 0 | `[1, 0, 0]` |
| 1 | 2 | 1 | `[1, 1, 0]` |
| 2 | 3 | 2 | `[1, 1, 1]` |

After counting:

```text
suff = [1, 1, 1]
```

### Step 3: Calculate suffix sums

Process from `i = n - 2 = 1` down to `0`.

| `i` | Calculation | `suff` |
|---:|---|---|
| 1 | `suff[1] += suff[2]` | `[1, 2, 1]` |
| 0 | `suff[0] += suff[1]` | `[3, 2, 1]` |

The final accumulated counts are:

```text
suff = [3, 2, 1]
```

### Step 4: Update each character

The initial string is:

```text
bca
```

**Position 0: `'b'`**

The character `'b'` has alphabet position `1`.

\[
(1+3)\bmod 26=4
\]

Alphabet position `4` corresponds to `'e'`.

**Position 1: `'c'`**

The character `'c'` has alphabet position `2`.

\[
(2+2)\bmod 26=4
\]

The resulting character is `'e'`.

**Position 2: `'a'`**

The character `'a'` has alphabet position `0`.

\[
(0+1)\bmod 26=1
\]

The resulting character is `'b'`.

The final string is:

```text
"eeb"
```

## 7. Complexity Analysis

### Time Complexity: \(O(n+m)\)

Let:

- `n` be the length of the string.
- `m` be the number of roll operations.

The algorithm performs:

- `O(m)` operations to count roll endpoints.
- `O(n)` operations to calculate suffix sums.
- `O(n)` operations to update the characters.

Therefore, the total time complexity is:

\[
O(m+n+n)=O(n+m)
\]

### Auxiliary Space Complexity: \(O(n)\)

The `suff` vector contains `n` integers.

Apart from this vector, the algorithm uses only a constant number of additional variables.

Therefore, the auxiliary space complexity is:

\[
O(n)
\]

## 8. Important Concepts

### 1. Suffix Sum

A suffix sum accumulates values from right to left. Here, it converts the number of operations ending at each position into the total number of operations affecting each character.

### 2. Difference-Array-Like Counting

Instead of updating every character for every roll operation, the solution records one count per operation endpoint and uses accumulation to determine the final effect.

### 3. Modulo Arithmetic

The modulo operator `% 26` ensures that character shifts wrap around after `'z'`.

### 4. ASCII Character Arithmetic

Subtracting `'a'` converts a lowercase character into its alphabet index, and adding `'a'` converts the index back into a character.

### 5. In-Place Modification

The function accepts `s` by reference and modifies its characters directly instead of creating another string.

## 9. Conclusion

The solution efficiently processes string roll operations using endpoint counting and a suffix-sum pass. Rather than simulating every operation across all affected characters, it calculates the total increment for each position and updates each character once.

The resulting complexity is **\(O(n+m)\) time and \(O(n)\) auxiliary space**, making this approach suitable for the constraints of up to \(10^5\) characters and roll operations.
