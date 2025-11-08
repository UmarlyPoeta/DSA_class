# 07. Linear Time Sorting & Order Statistics

## Learning Outcomes

After completing this module, you will be able to:

- Understand why comparison-based sorting has Ω(n log n) lower bound
- Implement linear time sorting algorithms (counting, radix, bucket sort)
- Determine when to use linear time sorting algorithms
- Find the kth smallest element efficiently
- Implement selection algorithms (randomized and deterministic)
- Solve order statistics problems

## Theory

### Breaking the Ω(n log n) Barrier

**Question**: Can we sort faster than O(n log n)?

**Answer**: Yes, if we don't use comparisons!

**Comparison-based sorting lower bound**: Any comparison-based sorting algorithm requires Ω(n log n) comparisons in the worst case.

**Non-comparison sorts**: Use properties of the input (e.g., integer range, digit structure) to achieve linear time.

## 1. Counting Sort

### Idea

Count occurrences of each element, then use counts to place elements in sorted order.

### When to Use

- **Input range k is small** (k = O(n))
- Elements are **integers** in range [0, k]
- Need a **stable** sort

### Pseudocode

```
CountingSort(A, k):
    // A is input array of size n
    // k is the maximum value in A
    
    n = length(A)
    C = array of size k+1, initialized to 0  // Count array
    B = array of size n                       // Output array
    
    // Count occurrences
    for i = 0 to n - 1:
        C[A[i]] = C[A[i]] + 1
    
    // Calculate cumulative counts (positions)
    for i = 1 to k:
        C[i] = C[i] + C[i - 1]
    
    // Build output array (from right to left for stability)
    for i = n - 1 down to 0:
        B[C[A[i]] - 1] = A[i]
        C[A[i]] = C[A[i]] - 1
    
    return B
```

### Example Walkthrough

```
Input: A = [2, 5, 3, 0, 2, 3, 0, 3]
k = 5 (max value)

Step 1: Count occurrences
C = [2, 0, 2, 3, 0, 1]  (index represents value)
     0  1  2  3  4  5

Step 2: Cumulative counts
C = [2, 2, 4, 7, 7, 8]
     ↑        ↑  ↑  ↑
   0's at   2's  3's 5 at
   pos 0-1  at   at  pos 7
            2-3  4-6

Step 3: Place elements
Starting from right: A[7] = 3
  C[3] = 7, so B[6] = 3, then C[3] = 6
Continue...

Output: B = [0, 0, 2, 2, 3, 3, 3, 5]
```

### Complexity Analysis

**Time Complexity**: O(n + k)
- Counting: O(n)
- Cumulative: O(k)
- Placement: O(n)

**Space Complexity**: O(n + k)

**Properties:**
- ✅ Stable
- ❌ Not in-place
- ✅ Linear time when k = O(n)
- ❌ Inefficient when k >> n

### When to Use

- Small range of integers (k = O(n))
- As subroutine in radix sort
- When stability is required

## 2. Radix Sort

### Idea

Sort numbers digit by digit, from least significant to most significant (or vice versa), using a stable sort for each digit.

### Types

1. **LSD (Least Significant Digit)**: Start from rightmost digit
2. **MSD (Most Significant Digit)**: Start from leftmost digit

### Pseudocode (LSD)

```
RadixSort(A, d):
    // A is array of d-digit numbers
    // d is number of digits
    
    for i = 1 to d:
        // Use stable sort to sort array A on digit i
        // (usually counting sort)
        StableSort(A, digit_i)
```

### Example (Base 10, LSD)

```
Input: [170, 045, 075, 090, 002, 024, 802, 066]

Pass 1 (ones place):
  [170, 090, 002, 802, 024, 045, 075, 066]
        ↑    ↑    ↑    ↑    ↑    ↑    ↑

Pass 2 (tens place):
  [002, 802, 024, 045, 066, 170, 075, 090]
    ↑    ↑    ↑    ↑    ↑    ↑    ↑    ↑

Pass 3 (hundreds place):
  [002, 024, 045, 066, 075, 090, 170, 802]
   ↑    ↑    ↑    ↑    ↑    ↑    ↑    ↑

Output: [2, 24, 45, 66, 75, 90, 170, 802]
```

### Complexity Analysis

**Time Complexity**: O(d(n + k))
- d = number of digits
- n = number of elements
- k = base (radix)

For **fixed-length integers** (d constant): O(n)

**Space Complexity**: O(n + k)

**Properties:**
- ✅ Stable (when using stable subroutine)
- ❌ Not in-place
- ✅ Linear time for fixed-length keys
- Not comparison-based

### When to Use

- Fixed-length integer keys
- String sorting (with fixed length)
- When k is small (e.g., base 256 for bytes)

## 3. Bucket Sort

### Idea

Distribute elements into buckets, sort each bucket, then concatenate.

### Assumptions

- Input is **uniformly distributed** over range [0, 1)
- Or can be mapped to this range

### Pseudocode

```
BucketSort(A):
    n = length(A)
    B = array of n empty lists (buckets)
    
    // Distribute elements into buckets
    for i = 0 to n - 1:
        index = floor(n * A[i])
        insert A[i] into B[index]
    
    // Sort each bucket
    for i = 0 to n - 1:
        sort B[i] using insertion sort (or any sort)
    
    // Concatenate buckets
    result = concatenate B[0], B[1], ..., B[n-1]
    return result
```

### Example

```
Input: [0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68]
n = 10

Buckets (index = floor(n * A[i])):
B[0]: []
B[1]: [0.17, 0.12]
B[2]: [0.26, 0.21, 0.23]
B[3]: [0.39]
B[4]: []
B[5]: []
B[6]: [0.68]
B[7]: [0.78, 0.72]
B[8]: []
B[9]: [0.94]

After sorting each bucket:
B[1]: [0.12, 0.17]
B[2]: [0.21, 0.23, 0.26]
B[3]: [0.39]
B[6]: [0.68]
B[7]: [0.72, 0.78]
B[9]: [0.94]

Output: [0.12, 0.17, 0.21, 0.23, 0.26, 0.39, 0.68, 0.72, 0.78, 0.94]
```

### Complexity Analysis

**Average Case**: O(n)
- Assuming uniform distribution
- Each bucket has O(1) elements on average

**Worst Case**: O(n²)
- All elements in one bucket

**Space Complexity**: O(n)

**Properties:**
- Depends on uniform distribution
- Good for floating-point numbers
- Can be stable (if insertion sort is used)

### When to Use

- Uniformly distributed data
- Floating-point numbers in known range
- Can map input to buckets easily

## Order Statistics

### The Selection Problem

**Given:** Array A of n distinct numbers and integer i (1 ≤ i ≤ n)  
**Goal:** Find the ith smallest element

**Special Cases:**
- i = 1: Minimum
- i = n: Maximum
- i = ⌊(n+1)/2⌋: Median

## 4. QuickSelect (Randomized Selection)

### Idea

Use quicksort's partition but recurse only on one side.

### Pseudocode

```
QuickSelect(A, left, right, k):
    // Find kth smallest element (k is 0-indexed)
    
    if left == right:
        return A[left]
    
    pivotIndex = Partition(A, left, right)
    
    if k == pivotIndex:
        return A[k]
    else if k < pivotIndex:
        return QuickSelect(A, left, pivotIndex - 1, k)
    else:
        return QuickSelect(A, pivotIndex + 1, right, k)

Partition(A, left, right):
    // Same as QuickSort partition
    pivot = A[right]
    i = left - 1
    
    for j = left to right - 1:
        if A[j] < pivot:
            i = i + 1
            swap(A[i], A[j])
    
    swap(A[i + 1], A[right])
    return i + 1
```

### Complexity Analysis

**Expected Time**: O(n)
- T(n) = T(n/2) + O(n) on average
- Recurrence solves to O(n)

**Worst Case**: O(n²)
- Bad pivot choices

**Space**: O(1) iterative, O(log n) recursive

### Optimization: Randomized QuickSelect

```
RandomizedQuickSelect(A, left, right, k):
    if left == right:
        return A[left]
    
    // Choose random pivot
    randomIndex = random(left, right)
    swap(A[randomIndex], A[right])
    
    pivotIndex = Partition(A, left, right)
    
    if k == pivotIndex:
        return A[k]
    else if k < pivotIndex:
        return RandomizedQuickSelect(A, left, pivotIndex - 1, k)
    else:
        return RandomizedQuickSelect(A, pivotIndex + 1, right, k)
```

## 5. Median of Medians (Deterministic Selection)

### Idea

Guarantee good pivot by finding median of medians.

### Algorithm

```
Select(A, left, right, k):
    if right - left < 5:
        // Use insertion sort for small arrays
        sort A[left..right]
        return A[k]
    
    // Step 1: Divide into groups of 5
    numGroups = ceiling((right - left + 1) / 5)
    medians = array of size numGroups
    
    for i = 0 to numGroups - 1:
        subLeft = left + i * 5
        subRight = min(subLeft + 4, right)
        medians[i] = findMedian(A, subLeft, subRight)
    
    // Step 2: Find median of medians recursively
    medianOfMedians = Select(medians, 0, numGroups - 1, numGroups / 2)
    
    // Step 3: Partition around median of medians
    pivotIndex = PartitionAroundValue(A, left, right, medianOfMedians)
    
    // Step 4: Recurse on appropriate partition
    if k == pivotIndex:
        return A[k]
    else if k < pivotIndex:
        return Select(A, left, pivotIndex - 1, k)
    else:
        return Select(A, pivotIndex + 1, right, k)
```

### Complexity Analysis

**Time Complexity**: O(n) - guaranteed!

**Recurrence**:
- T(n) ≤ T(n/5) + T(7n/10) + O(n)
- Solves to O(n)

**Space**: O(log n)

**Note**: Slower in practice than randomized quickselect despite better worst case.

## Code Examples

### Counting Sort (C++)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> countingSort(const std::vector<int>& arr) {
    if (arr.empty()) return arr;
    
    int n = arr.size();
    int maxVal = *std::max_element(arr.begin(), arr.end());
    
    std::vector<int> count(maxVal + 1, 0);
    std::vector<int> output(n);
    
    // Count occurrences
    for (int num : arr) {
        count[num]++;
    }
    
    // Cumulative count
    for (int i = 1; i <= maxVal; i++) {
        count[i] += count[i - 1];
    }
    
    // Build output array (stable)
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }
    
    return output;
}

int main() {
    std::vector<int> arr = {2, 5, 3, 0, 2, 3, 0, 3};
    
    std::cout << "Original: ";
    for (int x : arr) std::cout << x << " ";
    std::cout << std::endl;
    
    auto sorted = countingSort(arr);
    
    std::cout << "Sorted: ";
    for (int x : sorted) std::cout << x << " ";
    std::cout << std::endl;
    
    return 0;
}
```

### Radix Sort (C++)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

void countingSortByDigit(std::vector<int>& arr, int exp) {
    int n = arr.size();
    std::vector<int> output(n);
    std::vector<int> count(10, 0);
    
    // Count occurrences
    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }
    
    // Cumulative count
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    
    // Build output
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }
    
    // Copy to original array
    arr = output;
}

void radixSort(std::vector<int>& arr) {
    if (arr.empty()) return;
    
    int maxVal = *std::max_element(arr.begin(), arr.end());
    
    // Sort by each digit
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countingSortByDigit(arr, exp);
    }
}

int main() {
    std::vector<int> arr = {170, 45, 75, 90, 2, 24, 802, 66};
    
    std::cout << "Original: ";
    for (int x : arr) std::cout << x << " ";
    std::cout << std::endl;
    
    radixSort(arr);
    
    std::cout << "Sorted: ";
    for (int x : arr) std::cout << x << " ";
    std::cout << std::endl;
    
    return 0;
}
```

### Bucket Sort (C++)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

void bucketSort(std::vector<float>& arr) {
    int n = arr.size();
    if (n <= 1) return;
    
    // Create buckets
    std::vector<std::vector<float>> buckets(n);
    
    // Distribute elements into buckets
    for (float num : arr) {
        int bucketIndex = static_cast<int>(n * num);
        if (bucketIndex == n) bucketIndex--;  // Handle edge case
        buckets[bucketIndex].push_back(num);
    }
    
    // Sort each bucket
    for (auto& bucket : buckets) {
        std::sort(bucket.begin(), bucket.end());
    }
    
    // Concatenate buckets
    int index = 0;
    for (const auto& bucket : buckets) {
        for (float num : bucket) {
            arr[index++] = num;
        }
    }
}

int main() {
    std::vector<float> arr = {0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68};
    
    std::cout << "Original: ";
    for (float x : arr) std::cout << x << " ";
    std::cout << std::endl;
    
    bucketSort(arr);
    
    std::cout << "Sorted: ";
    for (float x : arr) std::cout << x << " ";
    std::cout << std::endl;
    
    return 0;
}
```

### QuickSelect (C++)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int partition(std::vector<int>& arr, int left, int right) {
    int pivot = arr[right];
    int i = left - 1;
    
    for (int j = left; j < right; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    
    std::swap(arr[i + 1], arr[right]);
    return i + 1;
}

int quickSelect(std::vector<int>& arr, int left, int right, int k) {
    if (left == right) {
        return arr[left];
    }
    
    int pivotIndex = partition(arr, left, right);
    
    if (k == pivotIndex) {
        return arr[k];
    } else if (k < pivotIndex) {
        return quickSelect(arr, left, pivotIndex - 1, k);
    } else {
        return quickSelect(arr, pivotIndex + 1, right, k);
    }
}

int findKthSmallest(std::vector<int>& arr, int k) {
    // k is 1-indexed (1st smallest, 2nd smallest, etc.)
    return quickSelect(arr, 0, arr.size() - 1, k - 1);
}

int main() {
    std::vector<int> arr = {7, 10, 4, 3, 20, 15};
    int k = 3;
    
    std::cout << "Array: ";
    for (int x : arr) std::cout << x << " ";
    std::cout << std::endl;
    
    int kthSmallest = findKthSmallest(arr, k);
    std::cout << k << "rd smallest element: " << kthSmallest << std::endl;
    
    return 0;
}
```

## Exercises

### Easy

1. **Counting Sort Variation**: Modify counting sort to work with negative integers.

2. **Sort Colors**: Sort array of 0s, 1s, and 2s in one pass (Dutch National Flag problem).

3. **Find Minimum and Maximum**: Find both min and max with fewer than 2n comparisons.

### Medium

4. **Top K Frequent Elements**: Find k most frequent elements in an array.

5. **Sort Array by Parity**: Sort array so even numbers come before odd numbers.

6. **Kth Largest in Stream**: Design data structure to find kth largest in a stream.

7. **Wiggle Sort**: Rearrange array so arr[0] ≤ arr[1] ≥ arr[2] ≤ arr[3]...

### Hard

8. **Median of Two Sorted Arrays**: Find median of two sorted arrays in O(log(min(m,n))).

9. **Sort Array by Increasing Frequency**: Sort by frequency, then by value.

10. **Smallest Range**: Find smallest range that includes at least one number from each of k sorted lists.

### Challenge

11. **Linear Time Median**: Implement deterministic median-of-medians algorithm.

12. **Custom Comparator Radix**: Extend radix sort to work with custom comparators.

13. **Parallel Bucket Sort**: Design parallel version of bucket sort.

## Algorithm Comparison Table

| Algorithm | Best | Average | Worst | Space | Stable | Notes |
|-----------|------|---------|-------|-------|--------|-------|
| Counting Sort | O(n+k) | O(n+k) | O(n+k) | O(k) | Yes | k = range |
| Radix Sort | O(d(n+k)) | O(d(n+k)) | O(d(n+k)) | O(n+k) | Yes | d = digits |
| Bucket Sort | O(n+k) | O(n+k) | O(n²) | O(n) | Yes* | Uniform dist. |
| QuickSelect | O(n) | O(n) | O(n²) | O(1) | No | Expected O(n) |
| Median-of-Medians | O(n) | O(n) | O(n) | O(log n) | No | Guaranteed O(n) |

*If using stable sort for buckets

## When to Use Linear Time Sorting

**Counting Sort:**
- Small integer range (k = O(n))
- Need stable sort
- Exact frequencies needed

**Radix Sort:**
- Fixed-length integer keys
- k is small (e.g., 256 for bytes)
- String sorting

**Bucket Sort:**
- Uniformly distributed data
- Floating-point numbers
- Can define good hash function

**General:**
Use **comparison-based sorts** (merge, quick) when:
- Don't know input distribution
- Keys are complex objects
- No special structure to exploit

## References

### Books
- **Introduction to Algorithms (CLRS)** - Chapters 8, 9
  - Chapter 8: Sorting in Linear Time
  - Chapter 9: Medians and Order Statistics

- **Algorithms** by Sedgewick & Wayne - Sections 5.1, 2.5

### Online Resources
- [VisuAlgo - Sorting (includes radix)](https://visualgo.net/en/sorting)
- [GeeksforGeeks - Counting Sort](https://www.geeksforgeeks.org/counting-sort/)
- [GeeksforGeeks - Radix Sort](https://www.geeksforgeeks.org/radix-sort/)
- [Median of Medians Visualization](https://www.youtube.com/watch?v=MZaf_9IZCrc)

### Papers
- Blum et al. - "Time Bounds for Selection" (1973) - Median of medians algorithm

## Summary

In this module, we covered:
- ✅ Linear time sorting: counting, radix, bucket sort
- ✅ When to use non-comparison sorts
- ✅ Order statistics and selection problem
- ✅ QuickSelect and median-of-medians algorithms
- ✅ Finding kth smallest element efficiently

**Congratulations!** You've completed all 7 modules of the DSA course. You now have a solid foundation in data structures and algorithms!

---

*💡 Tip: Linear time sorts are powerful when you can exploit special properties of your data. Otherwise, stick with O(n log n) comparison sorts!*

## Course Completion

**You've learned:**
1. ✅ Algorithm analysis and design paradigms
2. ✅ Fundamental data structures
3. ✅ Dynamic programming and greedy algorithms
4. ✅ Graph algorithms
5. ✅ Pattern matching algorithms
6. ✅ Sorting algorithms (comparison and linear)
7. ✅ Order statistics and selection

**Next steps:**
- Practice on LeetCode, HackerRank, Codeforces
- Implement algorithms from scratch
- Study advanced topics (advanced data structures, computational geometry, etc.)
- Apply knowledge to real-world projects

**Keep learning and coding!** 🚀
