# Trace Path

**Platform:** GeeksforGeeks  
**Difficulty:** Easy  
**Topics:** String, Grid, Simulation, Prefix Positions

## Problem Statement

Given a rectangular grid with `n` rows and `m` columns, and a string `s` representing movement commands, Geek can start from any cell and must follow every command in `s` in order.

The commands are:

- `L`: move one cell left, from `(i, j)` to `(i, j - 1)`.
- `R`: move one cell right, from `(i, j)` to `(i, j + 1)`.
- `D`: move one cell up, from `(i, j)` to `(i - 1, j)`.
- `U`: move one cell down, from `(i, j)` to `(i + 1, j)`.

Determine whether there is at least one starting cell such that Geek stays inside the grid throughout the entire route.

### Examples

**Example 1**

```text
Input: n = 1, m = 1, s = "R"
Output: false
```

The grid has only one cell. Moving right leaves the grid, so no valid starting cell exists.

**Example 2**

```text
Input: n = 2, m = 3, s = "LLRU"
Output: true
```

One valid starting cell is `(1, 3)`:

```text
(1, 3) -> (1, 2) -> (1, 1) -> (1, 2) -> (2, 2)
```

The entire route remains inside the grid.

### Constraints

- `1 <= n, m, s.length() <= 10^4`
- `s` contains only `L`, `R`, `D`, and `U`.

---

## Approach: Track the Route's Bounding Range

The starting cell is not specified, so simulating the route from a particular cell is not enough. Instead, imagine that Geek starts at relative position `(0, 0)` and track the displacement after every command.

The code uses two variables:

- `h`: horizontal displacement.
- `v`: vertical displacement.

It also tracks the minimum and maximum displacement reached on each axis:

- `minh` and `maxh`: minimum and maximum horizontal displacement.
- `minv` and `maxv`: minimum and maximum vertical displacement.

In this implementation, `L` increases `h` and `R` decreases it; `U` increases `v` and `D` decreases it. These signs are a chosen coordinate convention. The key is the total range between the minimum and maximum displacement, which is unaffected by shifting the starting point.

### Why the Range Determines Whether a Start Exists

On the vertical axis, the route spans `maxv - minv` cell-to-cell units. To fit inside a grid with `n` rows, this span must be strictly less than `n`:

```text
maxv - minv < n
```

Likewise, the horizontal span must fit inside `m` columns:

```text
maxh - minh < m
```

Both conditions must hold. If they do, we can choose a starting cell that offsets the minimum displacement to the first row/column, leaving enough room for the maximum displacement. If either span is too large, no starting cell can fit the whole route inside the grid.

## C++ Solution

```cpp
class Solution {
public:
    bool isPossible(int n, int m, string& s) {
        int v = 0;
        int h = 0;

        int minv = 0;
        int maxv = 0;
        int minh = 0;
        int maxh = 0;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == 'L') {
                h++;
            } else if (s[i] == 'R') {
                h--;
            } else if (s[i] == 'U') {
                v++;
            } else {
                v--;
            }

            minv = min(minv, v);
            maxv = max(maxv, v);
            minh = min(minh, h);
            maxh = max(maxh, h);
        }

        return (maxv - minv < n && maxh - minh < m);
    }
};
```

## Algorithm

1. Initialize horizontal and vertical displacement (`h` and `v`) to `0`.
2. Initialize the minimum and maximum displacement on both axes to `0`, because the starting position is part of the route.
3. Process each command in `s`:
   - Update `h` for `L` or `R`.
   - Update `v` for `U` or `D`.
   - Update the minimum and maximum displacement values.
4. Check whether the vertical displacement range is less than `n` and the horizontal range is less than `m`.
5. Return `true` if both conditions hold; otherwise, return `false`.

## Dry Runs

### Example 1: `n = 1, m = 1, s = "R"`

Start with:

```text
h = 0, v = 0
minh = maxh = 0
minv = maxv = 0
```

Process `R`:

- `h` becomes `-1`.
- `minh = -1`, `maxh = 0`.
- Horizontal range: `maxh - minh = 0 - (-1) = 1`.
- Vertical range: `maxv - minv = 0`.

Check:

- `1 < m` means `1 < 1`, which is false.
- Therefore, the route cannot fit in the grid.

**Output: `false`**

### Example 2: `n = 2, m = 3, s = "LLRU"`

| Command | `h` | `v` | `minh` | `maxh` | `minv` | `maxv` |
|---|---:|---:|---:|---:|---:|---:|
| Start | 0 | 0 | 0 | 0 | 0 | 0 |
| `L` | 1 | 0 | 0 | 1 | 0 | 0 |
| `L` | 2 | 0 | 0 | 2 | 0 | 0 |
| `R` | 1 | 0 | 0 | 2 | 0 | 0 |
| `U` | 1 | 1 | 0 | 2 | 0 | 1 |

Final ranges:

- Vertical: `maxv - minv = 1 - 0 = 1`, and `1 < 2`.
- Horizontal: `maxh - minh = 2 - 0 = 2`, and `2 < 3`.

Both conditions hold.

**Output: `true`**

## Complexity Analysis

Let `k = s.length()`.

- **Time Complexity: `O(k)`** — each movement command is processed exactly once.
- **Auxiliary Space Complexity: `O(1)`** — the algorithm uses a fixed number of integer variables and does not construct the route or grid.

## Correctness Explanation

The algorithm records the minimum and maximum relative displacement reached on each axis, including the starting position. Any actual starting cell translates every relative position by the same constant, so the total displacement ranges remain unchanged. A route fits within `n` rows exactly when its vertical range is less than `n`, and it fits within `m` columns exactly when its horizontal range is less than `m`. If both conditions hold, a starting cell can be selected to keep all visited positions within the grid. If either condition fails, the route spans too many rows or columns for any translation to fit. Therefore, the returned boolean is correct.

## Key Takeaway

The grid does not need to be simulated cell by cell. Track the route's minimum and maximum displacement on each axis. The route is possible if and only if:

```text
maxv - minv < n
maxh - minh < m
```

This gives a linear-time solution with constant extra space.
