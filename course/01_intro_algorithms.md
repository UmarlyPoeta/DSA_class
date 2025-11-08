# 01. Introduction to Algorithms

## Learning Outcomes

After completing this module, you will be able to:

- Define what an algorithm is and identify its key properties
- Analyze algorithm efficiency using asymptotic notation (Big-O, Θ, Ω)
- Apply different algorithm design paradigms
- Evaluate correctness and performance of algorithms
- Compare different approaches to solving the same problem

## Theory

### What is an Algorithm?

An **algorithm** is a well-defined computational procedure that takes some value(s) as **input** and produces some value(s) as **output**. It is a sequence of computational steps that transform the input into the output.

**Key Properties of Algorithms:**
1. **Finiteness** - Must terminate after a finite number of steps
2. **Definiteness** - Each step must be precisely defined
3. **Input** - Zero or more quantities are externally supplied
4. **Output** - At least one quantity is produced
5. **Effectiveness** - Each operation must be basic enough to be performed exactly and in finite time

### Algorithm Analysis

Algorithm analysis helps us predict the resources (time, memory) an algorithm requires.

#### Asymptotic Notation

**Big-O Notation (O)** - Upper bound (worst case)
- f(n) = O(g(n)) means f(n) grows no faster than g(n)
- Example: If an algorithm takes at most 3n² + 5n + 2 steps, we say it is O(n²)

**Omega Notation (Ω)** - Lower bound (best case)
- f(n) = Ω(g(n)) means f(n) grows at least as fast as g(n)

**Theta Notation (Θ)** - Tight bound (average case)
- f(n) = Θ(g(n)) means f(n) grows at the same rate as g(n)

#### Common Time Complexities (from best to worst)

| Complexity | Name | Example |
|------------|------|---------|
| O(1) | Constant | Array access |
| O(log n) | Logarithmic | Binary search |
| O(n) | Linear | Linear search |
| O(n log n) | Linearithmic | Merge sort, heap sort |
| O(n²) | Quadratic | Bubble sort, insertion sort |
| O(n³) | Cubic | Matrix multiplication (naive) |
| O(2ⁿ) | Exponential | Recursive fibonacci |
| O(n!) | Factorial | Traveling salesman (brute force) |

### Algorithm Design Paradigms

#### 1. Divide and Conquer
Break problem into smaller subproblems, solve recursively, and combine solutions.

**Structure:**
```
DivideAndConquer(problem):
    if problem is small enough:
        solve directly
    else:
        divide problem into subproblems
        recursively solve each subproblem
        combine solutions
```

**Examples:** Merge sort, quick sort, binary search

#### 2. Dynamic Programming
Solve problems by breaking them down into overlapping subproblems and storing solutions to avoid recomputation.

**Key characteristics:**
- Optimal substructure
- Overlapping subproblems

**Examples:** Fibonacci, longest common subsequence, knapsack

#### 3. Greedy Algorithms
Make locally optimal choice at each step, hoping to find global optimum.

**Examples:** Dijkstra's algorithm, Huffman coding, activity selection

#### 4. Brute Force
Try all possible solutions and pick the best one.

**Examples:** Linear search, selection sort

#### 5. Backtracking
Build solution incrementally and abandon solutions that fail to satisfy constraints.

**Examples:** N-Queens, Sudoku solver, graph coloring

## Pseudocode Examples

### Example 1: Linear Search

```
LinearSearch(A, n, key):
    Input: Array A of size n, search key
    Output: Index of key in A, or -1 if not found
    
    for i = 0 to n-1:
        if A[i] == key:
            return i
    return -1
```

**Time Complexity:** O(n)  
**Space Complexity:** O(1)

### Example 2: Binary Search

```
BinarySearch(A, left, right, key):
    Input: Sorted array A, search key
    Output: Index of key in A, or -1 if not found
    
    if left > right:
        return -1
    
    mid = (left + right) / 2
    
    if A[mid] == key:
        return mid
    else if A[mid] > key:
        return BinarySearch(A, left, mid-1, key)
    else:
        return BinarySearch(A, mid+1, right, key)
```

**Time Complexity:** O(log n)  
**Space Complexity:** O(log n) due to recursion

### Example 3: Maximum Subarray (Divide and Conquer)

```
MaxCrossingSum(A, left, mid, right):
    leftSum = -∞
    sum = 0
    for i = mid down to left:
        sum = sum + A[i]
        if sum > leftSum:
            leftSum = sum
    
    rightSum = -∞
    sum = 0
    for i = mid+1 to right:
        sum = sum + A[i]
        if sum > rightSum:
            rightSum = sum
    
    return leftSum + rightSum

MaxSubArray(A, left, right):
    if left == right:
        return A[left]
    
    mid = (left + right) / 2
    
    leftMax = MaxSubArray(A, left, mid)
    rightMax = MaxSubArray(A, mid+1, right)
    crossMax = MaxCrossingSum(A, left, mid, right)
    
    return max(leftMax, rightMax, crossMax)
```

**Time Complexity:** O(n log n)  
**Space Complexity:** O(log n)

## Code Examples

### Example 1: Linear Search (C++)

```cpp
#include <iostream>
#include <vector>

int linearSearch(const std::vector<int>& arr, int key) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == key) {
            return i;
        }
    }
    return -1;
}

int main() {
    std::vector<int> arr = {5, 2, 8, 1, 9, 3};
    int key = 8;
    
    int result = linearSearch(arr, key);
    
    if (result != -1) {
        std::cout << "Element found at index " << result << std::endl;
    } else {
        std::cout << "Element not found" << std::endl;
    }
    
    return 0;
}
```

### Example 2: Binary Search (C++)

```cpp
#include <iostream>
#include <vector>

int binarySearch(const std::vector<int>& arr, int left, int right, int key) {
    if (left > right) {
        return -1;
    }
    
    int mid = left + (right - left) / 2;  // Avoid overflow
    
    if (arr[mid] == key) {
        return mid;
    } else if (arr[mid] > key) {
        return binarySearch(arr, left, mid - 1, key);
    } else {
        return binarySearch(arr, mid + 1, right, key);
    }
}

int main() {
    std::vector<int> arr = {1, 2, 3, 5, 8, 9};  // Must be sorted
    int key = 5;
    
    int result = binarySearch(arr, 0, arr.size() - 1, key);
    
    if (result != -1) {
        std::cout << "Element found at index " << result << std::endl;
    } else {
        std::cout << "Element not found" << std::endl;
    }
    
    return 0;
}
```

## Exercises

### Easy

1. **Array Sum**: Write an algorithm to compute the sum of all elements in an array. What is its time complexity?

2. **Find Minimum**: Design an algorithm to find the minimum element in an unsorted array. Analyze its complexity.

3. **Palindrome Check**: Write an algorithm to check if a string is a palindrome. What is the time and space complexity?

### Medium

4. **Two Sum Problem**: Given an array of integers and a target sum, find two numbers that add up to the target. Try to achieve O(n) time complexity.

5. **Peak Element**: Find a peak element in an array where arr[i] >= arr[i-1] and arr[i] >= arr[i+1]. Can you do it in O(log n)?

6. **Majority Element**: Find the element that appears more than n/2 times in an array. Can you solve it in O(n) time and O(1) space?

### Hard

7. **Maximum Subarray**: Implement both the divide-and-conquer O(n log n) and dynamic programming O(n) solutions for the maximum subarray problem.

8. **Median of Two Sorted Arrays**: Find the median of two sorted arrays in O(log(min(m,n))) time.

9. **Recursive Staircase**: A person can climb 1, 2, or 3 steps at a time. How many ways are there to climb n steps? Solve using:
   - Recursive approach
   - Dynamic programming
   - Analyze and compare complexities

### Challenge

10. **Algorithm Design**: Given an array where every element appears twice except one element which appears once, find the single element in O(n) time and O(1) space.

## Complexity Analysis Practice

For each algorithm below, determine:
- Best case time complexity
- Average case time complexity
- Worst case time complexity
- Space complexity

```
Algorithm A:
for i = 1 to n:
    for j = 1 to n:
        print(i * j)
```

```
Algorithm B:
i = n
while i > 0:
    print(i)
    i = i / 2
```

```
Algorithm C:
for i = 1 to n:
    for j = 1 to i:
        print(j)
```

## References

### Books
- **Introduction to Algorithms (CLRS)** - Chapters 1-4
  - Chapter 1: The Role of Algorithms
  - Chapter 2: Getting Started
  - Chapter 3: Growth of Functions
  - Chapter 4: Divide-and-Conquer

- **Algorithm Design Manual** by Steven Skiena - Chapters 1-2

### Online Resources
- [Big-O Cheat Sheet](https://www.bigocheatsheet.com/) - Quick reference for complexities
- [VisuAlgo - Algorithm Visualizations](https://visualgo.net/) - Interactive algorithm animations
- [GeeksforGeeks - Analysis of Algorithms](https://www.geeksforgeeks.org/analysis-of-algorithms-set-1-asymptotic-analysis/)
- [MIT OpenCourseWare - Introduction to Algorithms](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/)

### Practice Platforms
- [LeetCode](https://leetcode.com/) - Start with Easy problems
- [HackerRank - Algorithms](https://www.hackerrank.com/domains/algorithms)
- [Codeforces](https://codeforces.com/) - Competitive programming

## Summary

In this module, we covered:
- ✅ Definition and properties of algorithms
- ✅ Asymptotic notation for complexity analysis
- ✅ Common algorithm design paradigms
- ✅ Basic algorithm examples with complexity analysis
- ✅ Practice problems from easy to challenging

**Next Steps:** Proceed to [Module 2: Data Structures](02_data_structures.md) to learn about fundamental data structures used in algorithm implementation.

---

*💡 Remember: Understanding algorithm complexity is crucial for writing efficient code. Always analyze both time and space complexity!*
