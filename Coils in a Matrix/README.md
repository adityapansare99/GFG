# Coils in a Matrix

## Problem

Given a positive integer `n`, construct a `4n × 4n` matrix containing the integers from `1` to `(4n)²` in row-major order.

Two coils are formed from this matrix:

1. The **first coil** starts from the top-left cell `(0, 0)` and moves inward.
2. The **second coil** starts from the bottom-right cell `(4n-1, 4n-1)` and moves inward in the opposite direction.

Return the two coils in the same order.

---

## Example

### Input

```text
n = 1
```

The matrix is:

```text
 1   2   3   4
 5   6   7   8
 9  10  11  12
13  14  15  16
```

The required coils are:

```text
First coil:
[1, 5, 9, 13, 14, 15, 11, 7]

Second coil:
[16, 12, 8, 4, 3, 2, 6, 10]
```

Therefore:

```text
[
    [1, 5, 9, 13, 14, 15, 11, 7],
    [16, 12, 8, 4, 3, 2, 6, 10]
]
```

---

## Constraints

```text
1 ≤ n ≤ 20
```

The matrix dimension is:

```text
4n × 4n
```

So the maximum dimension is:

```text
80 × 80
```

and the maximum number of cells is:

```text
80 × 80 = 6400
```

---

# Approach

The solution does **not explicitly construct the `4n × 4n` matrix**.

Instead, it uses the fact that the matrix is filled in row-major order.

Let:

```text
m = 4n
```

Then:

- Moving one cell **right** increases the value by `1`.
- Moving one cell **left** decreases the value by `1`.
- Moving one cell **down** increases the value by `m`.
- Moving one cell **up** decreases the value by `m`.

For example, for `n = 1`, `m = 4`:

```text
 1   2   3   4
 5   6   7   8
 9  10  11  12
13  14  15  16
```

From `1`:

```text
down  -> +4
right -> +1
up    -> -4
left  -> -1
```

The first coil can therefore be generated only by performing arithmetic on the current value.

Similarly, the second coil uses the opposite movement pattern:

```text
up    -> -m
left  -> -1
down  -> +m
right -> +1
```

---

# Important Observation

Each coil contains exactly half of all matrix elements.

The total number of cells is:

```text
(4n)²
```

Therefore, each coil contains:

```text
(4n)² / 2
```

elements.

The code stores this value as:

```cpp
total / 2
```

where:

```cpp
int total = 4*n*4*n;
```

Since `4*n*4*n` is equivalent to `(4n)²`, this correctly represents the total number of matrix cells.

---

# First Coil

The first coil starts from the top-left cell.

The first column is:

```text
1
1 + 4n
1 + 2(4n)
1 + 3(4n)
...
```

Therefore the code initializes it with:

```cpp
for(int i=1;i<=total;i+=4*n){
    firstCoil.push_back(i);
}
```

For `n = 1`, this produces:

```text
[1, 5, 9, 13]
```

This is the first downward part of the coil.

After reaching the bottom-left corner, the coil continues:

```text
right
up
left
down
right
up
left
...
```

The implementation generates these movements using the following value changes:

```text
down  : +4n
right : +1
up    : -4n
left  : -1
```

---

# Controlling the Spiral Length

The important variables used by the implementation are:

```cpp
int take = 4*n-1;
bool first = true;
int c = 0;
```

### `take`

`take` represents the current side length used while generating the spiral.

Initially:

```text
take = 4n - 1
```

After the outer layer is completed, the available side length becomes smaller.

The code reduces it by `2`:

```cpp
take -= 2;
```

This is because every completed inner layer removes one row/column from both sides.

The sequence is therefore approximately:

```text
4n - 1
4n - 3
4n - 5
4n - 7
...
```

---

## Role of `c`

The variable:

```cpp
c
```

keeps track of the movement number inside the current layer.

The code uses:

```cpp
c++;
if(c>2){
    c=1;
    take-=2;
}
```

This controls when the side length needs to shrink.

The implementation uses this mechanism while moving through the four directions.

---

# Why `take - 1`?

The code generates additional cells using:

```cpp
x = take - 1;
```

and then performs the movement `x` times.

For example, for `n = 1`:

```text
take = 3
x = 2
```

Starting from:

```text
1 5 9 13
```

the next movement is to the right.

Two additional cells are required:

```text
13 -> 14 -> 15
```

Therefore:

```cpp
for(int i=0;i<x;i++){
    firstCoil.push_back(firstCoil.back()+1);
}
```

adds:

```text
14, 15
```

The current cell is already included in the vector, so only the number of **new cells** needs to be generated.

---

# First Coil Movement Pattern

After initializing the first column, the code repeatedly performs:

### 1. Move Down

```cpp
firstCoil.push_back(firstCoil.back()+4*n);
```

This increases the value by one complete row.

### 2. Move Right

```cpp
firstCoil.push_back(firstCoil.back()+1);
```

This moves to the next column.

### 3. Move Up

```cpp
firstCoil.push_back(firstCoil.back()-4*n);
```

This moves one row upward.

### 4. Move Left

```cpp
firstCoil.push_back(firstCoil.back()-1);
```

This moves one column to the left.

These operations reproduce the required inward coil without storing the matrix itself.

---

# Why `first` Is Used

The first column is already generated before entering the main spiral loop:

```cpp
for(int i=1;i<=total;i+=4*n){
    firstCoil.push_back(i);
}
```

Therefore, the first iteration must not generate another downward movement.

This is handled using:

```cpp
bool first = true;
```

Inside the loop:

```cpp
if(!first){
    ...
}
```

The downward movement is skipped during the first iteration.

At the end of the first full cycle:

```cpp
first = false;
```

From that point onward, the normal movement sequence is used.

---

# Stopping Condition

Each coil must contain exactly:

```text
total / 2
```

elements.

Therefore, the main loop is controlled by:

```cpp
while(firstCoil.size()<total/2)
```

The implementation also checks:

```cpp
if(firstCoil.size()>total/2){
    break;
}
```

after each movement.

This prevents the algorithm from continuing after reaching the required half of the matrix.

The same logic is used for the second coil.

---

# Second Coil

The second coil is generated symmetrically from the bottom-right corner.

The bottom-right value is:

```text
total
```

The first column-equivalent sequence for this coil is generated using:

```cpp
for(int i=total;i>0;i-=4*n){
    secondCoil.push_back(i);
}
```

For `n = 1`:

```text
16
12
8
4
```

So initially:

```text
[16, 12, 8, 4]
```

The second coil then moves in the opposite direction.

Its movement pattern is:

```text
up
left
down
right
up
left
down
right
...
```

The corresponding value changes are:

```text
up    : -4n
left  : -1
down  : +4n
right : +1
```

---

# Second Coil Movement Implementation

The code generates the second coil using:

### 1. Move Up

```cpp
secondCoil.push_back(secondCoil.back()-4*n);
```

### 2. Move Left

```cpp
secondCoil.push_back(secondCoil.back()-1);
```

### 3. Move Down

```cpp
secondCoil.push_back(secondCoil.back()+4*n);
```

### 4. Move Right

```cpp
secondCoil.push_back(secondCoil.back()+1);
```

This is the reverse-direction counterpart of the first coil.

---

# Dry Run for `n = 1`

Here:

```text
4n = 4
total = 16
total / 2 = 8
```

## First Coil

Initial construction:

```text
1, 5, 9, 13
```

Now:

```text
take = 3
```

Move right:

```text
13 -> 14 -> 15
```

So:

```text
1, 5, 9, 13, 14, 15
```

Move up:

```text
15 -> 11
```

So:

```text
1, 5, 9, 13, 14, 15, 11
```

Move left:

```text
11 -> 7
```

Final:

```text
1, 5, 9, 13, 14, 15, 11, 7
```

There are exactly:

```text
8 = 16 / 2
```

elements.

---

## Second Coil

Initial construction:

```text
16, 12, 8, 4
```

Move left:

```text
4 -> 3 -> 2
```

Move down:

```text
2 -> 6
```

Move right:

```text
6 -> 10
```

Therefore:

```text
16, 12, 8, 4, 3, 2, 6, 10
```

Again there are exactly `8` elements.

---

# Dry Run for `n = 2`

Here:

```text
4n = 8
```

The matrix is:

```text
 1   2   3   4   5   6   7   8
 9  10  11  12  13  14  15  16
17  18  19  20  21  22  23  24
25  26  27  28  29  30  31  32
33  34  35  36  37  38  39  40
41  42  43  44  45  46  47  48
49  50  51  52  53  54  55  56
57  58  59  60  61  62  63  64
```

The total number of elements is:

```text
64
```

so each coil contains:

```text
32
```

elements.

The first coil begins:

```text
1, 9, 17, 25, 33, 41, 49, 57
```

Then it moves right:

```text
58, 59, 60, 61, 62, 63
```

then upward:

```text
55, 47, 39, 31, 23, 15
```

and then inward to:

```text
14, 13, 12, 11
```

followed by the next inward section.

This produces:

```text
[
    1, 9, 17, 25, 33, 41, 49, 57,
    58, 59, 60, 61, 62, 63,
    55, 47, 39, 31, 23, 15,
    14, 13, 12, 11,
    19, 27, 35, 43,
    44, 45,
    37, 29
]
```

which contains `32` values.

The second coil is generated symmetrically from `64` and contains the other `32` values.

---

# Why We Do Not Need the Matrix

A straightforward solution could first create:

```text
matrix[4n][4n]
```

and then traverse it.

However, that is unnecessary.

Because the matrix is filled in row-major order, every movement has a fixed numerical difference.

For matrix width:

```text
m = 4n
```

we know:

| Movement | Change in value |
|---|---:|
| Right | `+1` |
| Left | `-1` |
| Down | `+m` |
| Up | `-m` |

Therefore, the matrix can be represented implicitly using only the current value.

This saves the additional matrix storage.

---

# Correctness Proof

We prove that the algorithm produces the two required coils.

## First Coil

The algorithm initially inserts:

```text
1, 1+m, 1+2m, ..., 1+(m-1)m
```

where:

```text
m = 4n
```

These are exactly the values obtained by starting at the top-left cell and moving downward through the first column.

After that, every movement follows the required coil direction:

```text
right → up → left → down → ...
```

The value changes used by the algorithm are exactly the changes corresponding to those matrix movements:

```text
right = +1
up    = -m
left  = -1
down  = +m
```

The side length is reduced by `2` after completing the appropriate outer sections, so subsequent movements operate on progressively smaller inner regions.

The algorithm stops when the first coil has:

```text
total / 2
```

elements.

Therefore, the generated sequence is the required first coil.

---

## Second Coil

The algorithm initially inserts:

```text
total, total-m, total-2m, ..., total-(m-1)m
```

which corresponds to starting at the bottom-right cell and moving upward through the last column.

It then follows the opposite movement direction:

```text
left → down → right → up → ...
```

using the correct numerical changes:

```text
left  = -1
down  = +m
right = +1
up    = -m
```

The same shrinking side-length logic is applied to the inner regions.

The algorithm stops after generating:

```text
total / 2
```

elements.

Therefore, the generated sequence is the required second coil.

---

# Complexity Analysis

Let:

```text
m = 4n
```

The matrix contains:

```text
m² = (4n)² = 16n²
```

elements.

Each element of both coils is generated once.

Therefore:

### Time Complexity

```text
O(m²)
```

or equivalently:

```text
O(n²)
```

### Space Complexity

The two output vectors together contain all `m²` elements:

```text
O(m²)
```

or:

```text
O(n²)
```

The algorithm does **not** allocate an additional `m × m` matrix.

---

# Implementation

```cpp
class Solution {
  public:
    vector<vector<int>> formCoils(int n) {
        int total=4*n*4*n;
        vector<int> firstCoil;

        for(int i=1;i<=total;i+=4*n){
            firstCoil.push_back(i);
        }

        int take=4*n-1;
        bool first=true;
        int c=0;

        while(firstCoil.size()<total/2){
            int x=-1;

            if(!first){
                c++;
                if(c>2){
                    c=1;
                    take-=2;
                }

                x=take-1;
                for(int i=0;i<x;i++){
                    firstCoil.push_back(firstCoil.back()+4*n);
                }
            }

            if(firstCoil.size()>total/2){
                break;
            }

            c++;
            if(c>2){
                take-=2;
                c=1;
            }

            x=take-1;
            for(int i=0;i<x;i++){
                firstCoil.push_back(firstCoil.back()+1);
            }

            if(firstCoil.size()>total/2){
                break;
            }

            c++;
            if(c>2){
                take-=2;
                c=1;
            }

            x=take-1;
            for(int i=0;i<x;i++){
                firstCoil.push_back(firstCoil.back()-4*n);
            }

            if(firstCoil.size()>total/2){
                break;
            }

            c++;
            if(c>2){
                take-=2;
                c=1;
            }

            x=take-1;
            for(int i=0;i<x;i++){
                firstCoil.push_back(firstCoil.back()-1);
            }

            first=false;

            if(firstCoil.size()>total/2){
                break;
            }

            if(take<3){
                break;
            }
        }

        vector<int> secondCoil;

        for(int i=total;i>0;i-=4*n){
            secondCoil.push_back(i);
        }

        first=true;
        c=0;
        take=4*n-1;

        while(secondCoil.size()<total/2){
            int x=-1;

            if(!first){
                c++;
                if(c>2){
                    c=1;
                    take-=2;
                }

                x=take-1;
                for(int i=0;i<x;i++){
                    secondCoil.push_back(secondCoil.back()-4*n);
                }
            }

            if(secondCoil.size()>total/2){
                break;
            }

            c++;
            if(c>2){
                take-=2;
                c=1;
            }

            x=take-1;
            for(int i=0;i<x;i++){
                secondCoil.push_back(secondCoil.back()-1);
            }

            if(secondCoil.size()>total/2){
                break;
            }

            c++;
            if(c>2){
                c=1;
                take-=2;
            }

            x=take-1;
            for(int i=0;i<x;i++){
                secondCoil.push_back(secondCoil.back()+4*n);
            }

            if(secondCoil.size()>total/2){
                break;
            }

            c++;
            if(c>2){
                take-=2;
                c=1;
            }

            x=take-1;
            for(int i=0;i<x;i++){
                secondCoil.push_back(secondCoil.back()+1);
            }

            if(secondCoil.size()>total/2){
                break;
            }

            if(take<3){
                break;
            }

            first=false;
        }

        return {firstCoil,secondCoil};
    }
};
```

---

# Key Takeaways

1. The matrix dimension is `4n × 4n`.
2. The total number of elements is `(4n)²`.
3. Every coil contains exactly half of the elements.
4. The matrix itself does not need to be constructed.
5. Because the matrix is row-major:
   - right = `+1`
   - left = `-1`
   - down = `+4n`
   - up = `-4n`
6. The first coil starts from `1` and follows the inward direction.
7. The second coil starts from `total` and follows the opposite direction.
8. `take` controls the shrinking side length of the inner coil.
9. `c` controls when `take` is reduced by `2`.
10. The final time complexity is `O(n²)`, while the output itself requires `O(n²)` space.
