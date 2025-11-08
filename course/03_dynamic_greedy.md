# 03. Dynamic Programming & Greedy Algorithms

## Learning Outcomes

After completing this module, you will be able to:

- Identify problems suitable for dynamic programming
- Apply the principle of optimal substructure and overlapping subproblems
- Implement both top-down (memoization) and bottom-up (tabulation) DP approaches
- Recognize when greedy algorithms are appropriate
- Prove correctness of greedy algorithms using exchange arguments
- Solve classic optimization problems using DP and greedy strategies

## Theory

### Dynamic Programming (DP)

**Dynamic Programming** is an algorithmic paradigm that solves complex problems by breaking them down into simpler overlapping subproblems and storing their solutions to avoid redundant computation.

#### Key Characteristics

1. **Optimal Substructure**: An optimal solution to the problem contains optimal solutions to subproblems
2. **Overlapping Subproblems**: The same subproblems are solved multiple times

#### DP vs Divide and Conquer

| Feature | Divide and Conquer | Dynamic Programming |
|---------|-------------------|---------------------|
| Subproblems | Independent | Overlapping |
| Example | Merge Sort | Fibonacci |
| Recomputation | No | Yes (without DP) |

#### Approaches

**1. Top-Down (Memoization)**
- Start with original problem
- Recursively break down
- Store results in cache (memo)

**2. Bottom-Up (Tabulation)**
- Start with smallest subproblems
- Build up to final solution
- Use table to store intermediate results

### Greedy Algorithms

**Greedy algorithms** make locally optimal choices at each step, hoping to find a global optimum.

#### When Greedy Works

A greedy algorithm works when the problem has:
1. **Greedy Choice Property**: A global optimum can be arrived at by making locally optimal choices
2. **Optimal Substructure**: An optimal solution contains optimal solutions to subproblems

#### Proving Greedy Correctness

Use **exchange argument**: Show that any solution can be transformed into a greedy solution without making it worse.

## Dynamic Programming Examples

### 1. Fibonacci Sequence

**Problem**: Compute the nth Fibonacci number.

**Recurrence**: F(n) = F(n-1) + F(n-2), with F(0) = 0, F(1) = 1

#### Naive Recursive (Exponential)

```
Fibonacci(n):
    if n <= 1:
        return n
    return Fibonacci(n-1) + Fibonacci(n-2)
```

**Time Complexity**: O(2ⁿ) - exponential!  
**Space Complexity**: O(n) - recursion depth

#### Top-Down with Memoization

```
memo = array of size n+1, initialized to -1

Fibonacci_Memo(n):
    if n <= 1:
        return n
    
    if memo[n] != -1:
        return memo[n]
    
    memo[n] = Fibonacci_Memo(n-1) + Fibonacci_Memo(n-2)
    return memo[n]
```

**Time Complexity**: O(n)  
**Space Complexity**: O(n)

#### Bottom-Up with Tabulation

```
Fibonacci_DP(n):
    if n <= 1:
        return n
    
    dp = array of size n+1
    dp[0] = 0
    dp[1] = 1
    
    for i = 2 to n:
        dp[i] = dp[i-1] + dp[i-2]
    
    return dp[n]
```

**Time Complexity**: O(n)  
**Space Complexity**: O(n), can be optimized to O(1)

### 2. Longest Common Subsequence (LCS)

**Problem**: Find the length of the longest subsequence common to two sequences.

**Example**: LCS("ABCDGH", "AEDFHR") = "ADH" (length 3)

#### Recurrence Relation

```
LCS(X[1..m], Y[1..n]) =
    0                                    if m = 0 or n = 0
    LCS(X[1..m-1], Y[1..n-1]) + 1       if X[m] = Y[n]
    max(LCS(X[1..m-1], Y[1..n]),        if X[m] ≠ Y[n]
        LCS(X[1..m], Y[1..n-1]))
```

#### Bottom-Up Solution

```
LCS_Length(X, Y, m, n):
    dp = 2D array of size (m+1) × (n+1)
    
    // Initialize first row and column to 0
    for i = 0 to m:
        dp[i][0] = 0
    for j = 0 to n:
        dp[0][j] = 0
    
    // Fill the dp table
    for i = 1 to m:
        for j = 1 to n:
            if X[i-1] == Y[j-1]:
                dp[i][j] = dp[i-1][j-1] + 1
            else:
                dp[i][j] = max(dp[i-1][j], dp[i][j-1])
    
    return dp[m][n]
```

**Time Complexity**: O(m × n)  
**Space Complexity**: O(m × n), can be optimized to O(min(m, n))

### 3. 0/1 Knapsack Problem

**Problem**: Given n items with weights and values, and a knapsack of capacity W, maximize the total value without exceeding capacity. Each item can be taken at most once.

#### Recurrence Relation

```
Knapsack(n, W) =
    0                                       if n = 0 or W = 0
    Knapsack(n-1, W)                       if weight[n] > W
    max(Knapsack(n-1, W),                   if weight[n] <= W
        value[n] + Knapsack(n-1, W-weight[n]))
```

#### Bottom-Up Solution

```
Knapsack(weights, values, n, W):
    dp = 2D array of size (n+1) × (W+1)
    
    for i = 0 to n:
        for w = 0 to W:
            if i == 0 or w == 0:
                dp[i][w] = 0
            else if weights[i-1] <= w:
                dp[i][w] = max(values[i-1] + dp[i-1][w - weights[i-1]],
                               dp[i-1][w])
            else:
                dp[i][w] = dp[i-1][w]
    
    return dp[n][W]
```

**Time Complexity**: O(n × W)  
**Space Complexity**: O(n × W)

### 4. Longest Increasing Subsequence (LIS)

**Problem**: Find the length of the longest strictly increasing subsequence in an array.

**Example**: LIS([10, 9, 2, 5, 3, 7, 101, 18]) = 4 (e.g., [2, 3, 7, 101])

#### DP Solution O(n²)

```
LIS(arr, n):
    dp = array of size n, all initialized to 1
    
    for i = 1 to n-1:
        for j = 0 to i-1:
            if arr[i] > arr[j] and dp[i] < dp[j] + 1:
                dp[i] = dp[j] + 1
    
    return max(dp)
```

**Time Complexity**: O(n²)  
**Space Complexity**: O(n)

#### Optimized Solution O(n log n)

Using binary search with patience sorting concept.

```
LIS_Optimized(arr, n):
    tails = empty array  // tails[i] = smallest tail of LIS of length i+1
    
    for num in arr:
        pos = binary_search_position(tails, num)
        if pos == length(tails):
            append num to tails
        else:
            tails[pos] = num
    
    return length(tails)
```

**Time Complexity**: O(n log n)  
**Space Complexity**: O(n)

### 5. Edit Distance (Levenshtein Distance)

**Problem**: Find minimum number of operations (insert, delete, replace) to convert one string to another.

```
EditDistance(str1, str2, m, n):
    dp = 2D array of size (m+1) × (n+1)
    
    // Base cases
    for i = 0 to m:
        dp[i][0] = i  // Delete all characters
    for j = 0 to n:
        dp[0][j] = j  // Insert all characters
    
    for i = 1 to m:
        for j = 1 to n:
            if str1[i-1] == str2[j-1]:
                dp[i][j] = dp[i-1][j-1]  // No operation needed
            else:
                dp[i][j] = 1 + min(
                    dp[i-1][j],      // Delete
                    dp[i][j-1],      // Insert
                    dp[i-1][j-1]     // Replace
                )
    
    return dp[m][n]
```

**Time Complexity**: O(m × n)  
**Space Complexity**: O(m × n)

## Greedy Algorithm Examples

### 1. Activity Selection Problem

**Problem**: Given start and finish times of activities, select maximum number of non-overlapping activities.

**Greedy Strategy**: Always pick the activity that finishes first.

```
ActivitySelection(start, finish, n):
    // Assume activities are sorted by finish time
    
    selected = [0]  // Always select first activity
    lastFinish = finish[0]
    
    for i = 1 to n-1:
        if start[i] >= lastFinish:
            selected.append(i)
            lastFinish = finish[i]
    
    return selected
```

**Time Complexity**: O(n log n) if sorting needed, O(n) if pre-sorted  
**Space Complexity**: O(1)

**Proof of Correctness**: Exchange argument - any optimal solution can be modified to include the earliest finishing activity.

### 2. Fractional Knapsack

**Problem**: Like 0/1 knapsack, but items can be taken fractionally.

**Greedy Strategy**: Take items in order of value-to-weight ratio.

```
FractionalKnapsack(weights, values, capacity, n):
    // Calculate value/weight ratio
    items = array of (value/weight, weight, value) for each item
    sort items by ratio in descending order
    
    totalValue = 0
    remainingCapacity = capacity
    
    for each item in items:
        if item.weight <= remainingCapacity:
            // Take whole item
            totalValue += item.value
            remainingCapacity -= item.weight
        else:
            // Take fraction of item
            totalValue += item.ratio × remainingCapacity
            break
    
    return totalValue
```

**Time Complexity**: O(n log n)  
**Space Complexity**: O(n)

### 3. Huffman Coding

**Problem**: Build optimal prefix-free binary code for data compression.

**Greedy Strategy**: Always combine two nodes with smallest frequencies.

```
HuffmanCoding(characters, frequencies):
    // Create a min heap of all characters
    minHeap = build_min_heap(characters, frequencies)
    
    while size(minHeap) > 1:
        // Extract two nodes with minimum frequency
        left = extract_min(minHeap)
        right = extract_min(minHeap)
        
        // Create internal node with frequency = sum
        internal = new Node
        internal.freq = left.freq + right.freq
        internal.left = left
        internal.right = right
        
        insert(minHeap, internal)
    
    return extract_min(minHeap)  // Root of Huffman tree
```

**Time Complexity**: O(n log n)  
**Space Complexity**: O(n)

### 4. Minimum Spanning Tree (MST)

See Module 4 for Kruskal's and Prim's algorithms.

## Code Examples

### Fibonacci with DP (C++)

```cpp
#include <iostream>
#include <vector>

// Top-down with memoization
int fibMemo(int n, std::vector<int>& memo) {
    if (n <= 1) return n;
    
    if (memo[n] != -1) return memo[n];
    
    memo[n] = fibMemo(n-1, memo) + fibMemo(n-2, memo);
    return memo[n];
}

// Bottom-up
int fibDP(int n) {
    if (n <= 1) return n;
    
    std::vector<int> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;
    
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i-1] + dp[i-2];
    }
    
    return dp[n];
}

// Space-optimized
int fibOptimized(int n) {
    if (n <= 1) return n;
    
    int prev2 = 0, prev1 = 1;
    
    for (int i = 2; i <= n; i++) {
        int curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    
    return prev1;
}

int main() {
    int n = 10;
    
    std::vector<int> memo(n + 1, -1);
    std::cout << "Fib(" << n << ") memoization: " << fibMemo(n, memo) << std::endl;
    std::cout << "Fib(" << n << ") DP: " << fibDP(n) << std::endl;
    std::cout << "Fib(" << n << ") optimized: " << fibOptimized(n) << std::endl;
    
    return 0;
}
```

### Longest Common Subsequence (C++)

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int lcs(const std::string& X, const std::string& Y) {
    int m = X.length();
    int n = Y.length();
    
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i-1] == Y[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    
    return dp[m][n];
}

// Function to reconstruct the LCS
std::string getLCS(const std::string& X, const std::string& Y) {
    int m = X.length();
    int n = Y.length();
    
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i-1] == Y[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    
    // Backtrack to find the LCS
    std::string result;
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i-1] == Y[j-1]) {
            result = X[i-1] + result;
            i--;
            j--;
        } else if (dp[i-1][j] > dp[i][j-1]) {
            i--;
        } else {
            j--;
        }
    }
    
    return result;
}

int main() {
    std::string X = "ABCDGH";
    std::string Y = "AEDFHR";
    
    std::cout << "LCS length: " << lcs(X, Y) << std::endl;
    std::cout << "LCS: " << getLCS(X, Y) << std::endl;
    
    return 0;
}
```

### 0/1 Knapsack (C++)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int knapsack(const std::vector<int>& weights, 
             const std::vector<int>& values, 
             int capacity) {
    int n = weights.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(capacity + 1, 0));
    
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= capacity; w++) {
            if (weights[i-1] <= w) {
                dp[i][w] = std::max(
                    values[i-1] + dp[i-1][w - weights[i-1]],
                    dp[i-1][w]
                );
            } else {
                dp[i][w] = dp[i-1][w];
            }
        }
    }
    
    return dp[n][capacity];
}

int main() {
    std::vector<int> values = {60, 100, 120};
    std::vector<int> weights = {10, 20, 30};
    int capacity = 50;
    
    std::cout << "Maximum value: " << knapsack(weights, values, capacity) << std::endl;
    
    return 0;
}
```

## Exercises

### Easy

1. **Climbing Stairs**: You can climb 1 or 2 steps at a time. How many ways to climb n steps?

2. **Coin Change (Count)**: Count number of ways to make change for amount n using given coin denominations.

3. **House Robber**: Houses in a line have money. Can't rob adjacent houses. Maximize money robbed.

### Medium

4. **Longest Palindromic Subsequence**: Find the length of the longest palindromic subsequence in a string.

5. **Matrix Chain Multiplication**: Find the optimal way to parenthesize a chain of matrix multiplications.

6. **Coin Change (Minimum)**: Find minimum number of coins needed to make a given amount.

7. **Partition Problem**: Determine if an array can be partitioned into two subsets with equal sum.

8. **Job Scheduling**: Given jobs with deadlines and profits, maximize profit (greedy).

### Hard

9. **Egg Drop Problem**: With k eggs and n floors, find minimum drops needed to determine critical floor.

10. **Wildcard Pattern Matching**: Implement wildcard pattern matching with '?' and '*'.

11. **Word Break**: Given a string and dictionary, determine if string can be segmented into dictionary words.

12. **Maximum Profit with k Transactions**: Buy and sell stock with at most k transactions.

### Challenge

13. **Palindrome Partitioning II**: Minimum cuts needed to partition string into palindromes.

14. **Distinct Subsequences**: Count distinct subsequences of string S that equal string T.

15. **Regular Expression Matching**: Implement regex matching with '.' and '*'.

## DP vs Greedy Decision Tree

```
Can the problem be solved optimally?
    ├─ Is there optimal substructure?
    │   ├─ Yes → Continue
    │   └─ No → Try other approaches
    │
    └─ Greedy choice property?
        ├─ Yes → Use GREEDY
        │   └─ Can you prove it? (exchange argument)
        │       ├─ Yes → Greedy works!
        │       └─ No → Use DP
        │
        └─ No → Use DYNAMIC PROGRAMMING
            └─ Overlapping subproblems?
                ├─ Yes → DP is beneficial
                └─ No → Use Divide & Conquer
```

## Common DP Patterns

1. **Linear DP**: dp[i] depends on previous elements
   - Example: Fibonacci, climbing stairs

2. **2D DP**: dp[i][j] depends on dp[i-1][j], dp[i][j-1], etc.
   - Example: LCS, edit distance

3. **Interval DP**: dp[i][j] represents optimal solution for subarray [i..j]
   - Example: Matrix chain multiplication

4. **Subsequence DP**: Problems involving subsequences
   - Example: LIS, LCS

5. **Knapsack-type**: Limited capacity constraint
   - Example: 0/1 knapsack, subset sum

## References

### Books
- **Introduction to Algorithms (CLRS)** - Chapters 15, 16
  - Chapter 15: Dynamic Programming
  - Chapter 16: Greedy Algorithms

- **Algorithm Design** by Kleinberg & Tardos - Chapters 6, 4
  - Chapter 6: Dynamic Programming
  - Chapter 4: Greedy Algorithms

### Online Resources
- [GeeksforGeeks - Dynamic Programming](https://www.geeksforgeeks.org/dynamic-programming/)
- [TopCoder - Dynamic Programming Tutorial](https://www.topcoder.com/community/competitive-programming/tutorials/dynamic-programming-from-novice-to-advanced/)
- [LeetCode DP Problems](https://leetcode.com/tag/dynamic-programming/)
- [Codeforces DP Tutorial](https://codeforces.com/blog/entry/43256)

### Video Lectures
- MIT 6.006 - Dynamic Programming lectures
- Abdul Bari - Dynamic Programming YouTube series

## Summary

In this module, we covered:
- ✅ Dynamic programming principles and approaches
- ✅ Top-down (memoization) vs bottom-up (tabulation)
- ✅ Classic DP problems: Fibonacci, LCS, knapsack, LIS
- ✅ Greedy algorithm strategy and correctness proofs
- ✅ When to use DP vs greedy approaches

**Next Steps:** Proceed to [Module 4: Graph Algorithms](04_graph_algorithms.md) to learn about graph representations and algorithms.

---

*💡 Tip: Start with the recurrence relation, then choose memoization or tabulation based on the problem structure!*
