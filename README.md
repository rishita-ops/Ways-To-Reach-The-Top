# DSA — Climbing Stairs

A focused C++ implementation of the classic **Climbing Stairs** problem using **bottom-up dynamic programming**. This is one of the most well-known introductory DP problems in competitive programming and technical interviews — canonical on LeetCode (#70) and a standard benchmark for understanding how to think in terms of subproblems, recurrences, and tabulation. The solution is elegant, efficient, and opens a direct conceptual path to Fibonacci, memoization, and space optimization.

---

## Problem Statement

You are climbing a staircase with `n` steps. At each move, you can climb either **1 step** or **2 steps**. In how many **distinct ways** can you reach the top?

**Example Input:**
```
Enter number of steps : 5
```

**Example Output:**
```
Number of ways to climb stairs : 8
```

---

## The Code

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cout << "Enter number of steps : ";
    cin >> n;

    int dp[n + 1];
    dp[0] = 1;
    dp[1] = 1;

    for (int i = 2; i <= n; i++)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    cout << "Number of ways to climb stairs : " << dp[n];

    return 0;
}
```

---

## The Core Insight — Why `dp[i] = dp[i-1] + dp[i-2]`

To reach step `i`, you must have arrived from one of exactly two places:
- **Step `i-1`** — by taking 1 step up
- **Step `i-2`** — by taking 2 steps up

So the number of distinct ways to reach step `i` is the **sum of the ways to reach the two steps immediately below it**. This is the recurrence:

```
dp[i] = dp[i-1] + dp[i-2]
```

Every subproblem builds directly on two smaller subproblems already solved — the defining characteristic of dynamic programming.

---

## The Base Cases — Why `dp[0] = 1`, Not `0`

This is the most important semantic detail in the entire program.

| Base Case | Value | Meaning |
|-----------|-------|---------|
| `dp[0] = 1` | 1 | There is **1 way** to be at the ground floor — do nothing |
| `dp[1] = 1` | 1 | There is **1 way** to reach step 1 — take one single step |

`dp[0] = 1` does **not** mean "step 0 exists to climb." It is an **accounting base case** — it exists so that `dp[2] = dp[1] + dp[0] = 1 + 1 = 2` evaluates correctly. Without it, `dp[2]` would be `1 + 0 = 1`, which is wrong (there are two ways to climb 2 steps: `{1,1}` and `{2}`).

This is the key distinction from the Fibonacci sequence, where `F(0) = 0`. Same recurrence, different base cases, different meaning.

---

## How It Works — Tabulation (Bottom-Up DP)

The `dp` array is filled iteratively from the smallest subproblem upward — this is called **tabulation** or **bottom-up DP**:

```
dp[0] = 1     ← base: 1 way to stand at ground
dp[1] = 1     ← base: 1 way to reach step 1
dp[2] = dp[1] + dp[0] = 2
dp[3] = dp[2] + dp[1] = 3
dp[4] = dp[3] + dp[2] = 5
dp[5] = dp[4] + dp[3] = 8
```

Each cell is computed exactly once, in order, with no recursion and no redundant recomputation.

---

## Algorithm (Pseudocode)

```
read n

dp[0] ← 1
dp[1] ← 1

for i from 2 to n:
    dp[i] ← dp[i-1] + dp[i-2]

print dp[n]
```

---

## Dry Run

**Input:** `n = 6`

| `i` | `dp[i-2]` | `dp[i-1]` | `dp[i]` | Meaning |
|-----|-----------|-----------|---------|---------|
| 0   | —         | —         | 1       | Ground: 1 way |
| 1   | —         | —         | 1       | Step 1: 1 way |
| 2   | 1         | 1         | 2       | `{1,1}` or `{2}` |
| 3   | 1         | 2         | 3       | `{1,1,1}`, `{1,2}`, `{2,1}` |
| 4   | 2         | 3         | 5       | 5 distinct paths |
| 5   | 3         | 5         | 8       | 8 distinct paths |
| 6   | 5         | 8         | 13      | 13 distinct paths |

**Output:** `Number of ways to climb stairs : 13`

---

## All Distinct Paths for Small `n`

**`n = 3` → 3 ways:**
```
1. {1, 1, 1}
2. {1, 2}
3. {2, 1}
```

**`n = 4` → 5 ways:**
```
1. {1, 1, 1, 1}
2. {1, 1, 2}
3. {1, 2, 1}
4. {2, 1, 1}
5. {2, 2}
```

---

## Climbing Stairs vs Fibonacci — Same Recurrence, Different Base Cases

The recurrence `dp[i] = dp[i-1] + dp[i-2]` is identical to Fibonacci, but the base cases shift the sequence by one position:

| `n`          | 0 | 1 | 2 | 3 | 4 | 5  | 6  | 7  |
|--------------|---|---|---|---|---|----|----|----|
| Fibonacci    | 0 | 1 | 1 | 2 | 3 | 5  | 8  | 13 |
| Climbing Stairs | 1 | 1 | 2 | 3 | 5 | 8 | 13 | 21 |

`climbStairs(n) = Fibonacci(n + 1)`

The Fibonacci sequence is offset by one. This is not a coincidence — it is a direct consequence of `dp[0] = 1` instead of `F(0) = 0`. Recognizing this connection is a signal of deep understanding that interviewers specifically look for.

---

## Complexity Analysis

| Metric | Complexity |
|--------|------------|
| Time   | **O(n)** — single forward pass, each subproblem solved exactly once |
| Space  | **O(n)** — `dp` array of size `n + 1` allocated on the stack (VLA) |

> **Space can be reduced to O(1).** Since `dp[i]` only depends on `dp[i-1]` and `dp[i-2]`, the entire array is unnecessary — only the last two values need to be kept at any point. See the optimization section below.

> **VLA note:** `int dp[n + 1]` is a Variable Length Array — a GCC/C99 extension, not standard C++. For portable code, use `std::vector<int> dp(n + 1)`.

---

## Space Optimization — O(1)

The full `dp` array stores `n + 1` values, but only the last two are ever accessed at any step. This reduces space to O(1):

```cpp
int prev2 = 1, prev1 = 1;

for (int i = 2; i <= n; i++) {
    int curr = prev1 + prev2;
    prev2 = prev1;
    prev1 = curr;
}

cout << "Number of ways to climb stairs : " << prev1;
```

Same O(n) time. Same correct output. No array needed.

---

## Three Ways to Solve the Same Problem

| Approach | Time | Space | Notes |
|----------|------|-------|-------|
| Recursion (naive) | O(2ⁿ) | O(n) call stack | Intuitive, exponentially slow — identical issue as naive Fibonacci |
| Tabulation / Bottom-Up DP (this repo) | O(n) | O(n) | Clean, explicit subproblem table |
| Space-Optimized Iteration | O(n) | O(1) | Production-preferred; two variables only |

The tabulation approach in this repo is the right place to start — it makes the subproblem structure visible and explicit before optimizing it away.

---

## Edge Cases

| Input | Expected Output | Behavior |
|-------|----------------|----------|
| `n = 0` | 1 (1 way — do nothing) | `dp[0] = 1` returned directly ✅ |
| `n = 1` | 1 | `dp[1] = 1` returned directly ✅ |
| `n = 2` | 2 | `dp[2] = dp[1] + dp[0] = 2` ✅ |
| `n = 44` | 1,134,903,170 | Near `INT_MAX` (2,147,483,647) — fits in `int` ✅ |
| `n = 45` | 1,836,311,903 | Still within `int` range ✅ |
| `n = 46` | 2,971,215,073 | **Overflows `int`** ⚠️ — use `long long` for `n ≥ 46` |

> For safety with large inputs, declare `long long dp[n + 1]` and change the output type accordingly.

---

## Repository Structure

```
DSA-Climbing-Stairs/
│
├── climbing_stairs.cpp     # Main C++ bottom-up DP implementation
└── README.md               # Project documentation
```

---

## How to Compile and Run

**Prerequisites:** GCC / G++

```bash
# Clone the repository
git clone https://github.com/rishita-ops/DSA-Climbing-Stairs.git
cd DSA-Climbing-Stairs

# Compile
g++ climbing_stairs.cpp -o climbing_stairs

# Run
./climbing_stairs
```

**On Windows:**
```bash
g++ climbing_stairs.cpp -o climbing_stairs.exe
climbing_stairs.exe
```

---

## Key Concepts Covered

- **Dynamic programming (tabulation)** — bottom-up subproblem construction using an explicit array
- **Recurrence relation** — `dp[i] = dp[i-1] + dp[i-2]` derived from the two valid moves
- **Base case semantics** — why `dp[0] = 1` is an accounting base case, not a physical step
- **Climbing Stairs ↔ Fibonacci equivalence** — `climbStairs(n) = Fibonacci(n+1)`
- **Space optimization** — reducing O(n) array to O(1) two-variable iteration
- **Integer overflow** — recognizing that `int` overflows at `n ≥ 46` for this sequence
- **VLA vs `std::vector`** — GCC extension vs portable C++ standard

---

## Why This Problem Matters in DSA

The Climbing Stairs problem is **the gateway to dynamic programming**. It introduces every core DP concept in the simplest possible setting:

| DP Concept | How It Appears Here |
|------------|---------------------|
| Optimal substructure | Ways to reach step `i` depends only on steps `i-1` and `i-2` |
| Overlapping subproblems | Naive recursion recomputes `dp[3]`, `dp[4]` etc. multiple times |
| Tabulation (bottom-up) | Fill `dp[]` iteratively from index 0 to `n` |
| Memoization (top-down) | Cache recursive results to avoid recomputation |
| Space optimization | Drop the array, keep only the last two values |

Once this problem is fully understood — recurrence, base cases, and the Fibonacci connection — the following problems are direct extensions:

| Problem | Connection |
|---------|------------|
| LeetCode #70 (Climbing Stairs) | This exact problem |
| LeetCode #746 (Min Cost Climbing Stairs) | Same structure, minimize cost instead of count paths |
| LeetCode #509 (Fibonacci Number) | Identical recurrence, different base cases |
| LeetCode #198 (House Robber) | DP with a skip constraint — direct extension of this pattern |
| LeetCode #322 (Coin Change) | Generalized step sizes — climb with coins of any denomination |
| LeetCode #91 (Decode Ways) | Conditional recurrence — same two-step DP skeleton |

Every one of these problems is solved with the same mental model built here: *define the subproblem, write the recurrence, handle base cases, fill bottom-up.*

---

## Contributing

Contributions are welcome. Consider adding:
- A **recursive with memoization** (top-down DP) version for comparison
- A **space-optimized O(1)** iterative version
- A **generalized version** supporting steps of size 1, 2, or 3
- Input validation for `n < 0`
- Implementations in Python, Java, or JavaScript

```bash
git checkout -b feature/your-feature
git commit -m "Add: your feature description"
git push origin feature/your-feature
# Then open a Pull Request
```

---

## License

This project is open-source and available under the [MIT License](LICENSE).

---

*Part of a structured DSA practice series — fundamentals, done right.*
