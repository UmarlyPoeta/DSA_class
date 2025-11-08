# 06. Sorting Algorithms - Basics

## Learning Outcomes

After completing this module, you will be able to:

- Understand different sorting paradigms and their trade-offs
- Implement basic sorting algorithms (bubble, insertion, selection)
- Implement efficient comparison-based sorts (merge, quick, heap)
- Analyze time and space complexity of sorting algorithms
- Choose the appropriate sorting algorithm for different scenarios
- Understand the lower bound for comparison-based sorting

## Theory

### The Sorting Problem

**Given:** An array A of n elements  
**Goal:** Rearrange elements so that A[0] ≤ A[1] ≤ ... ≤ A[n-1]

### Sorting Algorithm Properties

1. **In-place**: Uses O(1) extra space
2. **Stable**: Preserves relative order of equal elements
3. **Adaptive**: Takes advantage of existing order
4. **Online**: Can sort as data arrives

### Lower Bound for Comparison-Based Sorting

**Theorem**: Any comparison-based sorting algorithm requires Ω(n log n) comparisons in the worst case.

**Proof**: Using decision tree model with n! leaves (all permutations).

## 1. Simple Sorting Algorithms

### Bubble Sort

**Idea**: Repeatedly swap adjacent elements if they're in wrong order.

#### Pseudocode

```
BubbleSort(A):
    n = length(A)
    
    for i = 0 to n - 1:
        for j = 0 to n - i - 2:
            if A[j] > A[j + 1]:
                swap(A[j], A[j + 1])
```

#### Optimized Version (Early Exit)

```
BubbleSort_Optimized(A):
    n = length(A)
    
    for i = 0 to n - 1:
        swapped = false
        
        for j = 0 to n - i - 2:
            if A[j] > A[j + 1]:
                swap(A[j], A[j + 1])
                swapped = true
        
        if not swapped:
            break  // Array is sorted
```

#### Complexity

**Time Complexity:**
- Best Case: O(n) - already sorted (with optimization)
- Average Case: O(n²)
- Worst Case: O(n²) - reverse sorted

**Space Complexity**: O(1)

**Properties:**
- ✅ In-place
- ✅ Stable
- ✅ Adaptive (with optimization)
- ❌ Not efficient for large arrays

**When to Use:**
- Small datasets
- Nearly sorted data (with optimization)
- Educational purposes

### Selection Sort

**Idea**: Find minimum element and place it at the beginning. Repeat for remaining array.

#### Pseudocode

```
SelectionSort(A):
    n = length(A)
    
    for i = 0 to n - 2:
        minIndex = i
        
        for j = i + 1 to n - 1:
            if A[j] < A[minIndex]:
                minIndex = j
        
        if minIndex != i:
            swap(A[i], A[minIndex])
```

#### Complexity

**Time Complexity:**
- Best Case: O(n²)
- Average Case: O(n²)
- Worst Case: O(n²)

**Space Complexity**: O(1)

**Comparisons**: Always (n-1) + (n-2) + ... + 1 = n(n-1)/2

**Properties:**
- ✅ In-place
- ❌ Not stable (can be made stable with modifications)
- ❌ Not adaptive
- Minimum number of swaps: O(n)

**When to Use:**
- When write operations are expensive
- Small datasets

### Insertion Sort

**Idea**: Build sorted array one element at a time by inserting each element into its correct position.

#### Pseudocode

```
InsertionSort(A):
    n = length(A)
    
    for i = 1 to n - 1:
        key = A[i]
        j = i - 1
        
        // Shift elements greater than key to the right
        while j >= 0 and A[j] > key:
            A[j + 1] = A[j]
            j = j - 1
        
        A[j + 1] = key
```

#### Complexity

**Time Complexity:**
- Best Case: O(n) - already sorted
- Average Case: O(n²)
- Worst Case: O(n²) - reverse sorted

**Space Complexity**: O(1)

**Properties:**
- ✅ In-place
- ✅ Stable
- ✅ Adaptive
- ✅ Online
- Efficient for small arrays and nearly sorted data

**When to Use:**
- Small datasets (n < 50)
- Nearly sorted data
- Online sorting
- Part of hybrid algorithms (Timsort uses insertion sort for small subarrays)

## 2. Efficient Sorting Algorithms

### Merge Sort (Divide and Conquer)

**Idea**: Divide array into halves, recursively sort, then merge sorted halves.

#### Pseudocode

```
MergeSort(A, left, right):
    if left < right:
        mid = (left + right) / 2
        
        MergeSort(A, left, mid)
        MergeSort(A, mid + 1, right)
        Merge(A, left, mid, right)

Merge(A, left, mid, right):
    n1 = mid - left + 1
    n2 = right - mid
    
    L = copy of A[left..mid]
    R = copy of A[mid+1..right]
    
    i = 0, j = 0, k = left
    
    while i < n1 and j < n2:
        if L[i] <= R[j]:
            A[k] = L[i]
            i = i + 1
        else:
            A[k] = R[j]
            j = j + 1
        k = k + 1
    
    // Copy remaining elements
    while i < n1:
        A[k] = L[i]
        i = i + 1
        k = k + 1
    
    while j < n2:
        A[k] = R[j]
        j = j + 1
        k = k + 1
```

#### Complexity

**Time Complexity:**
- Best Case: O(n log n)
- Average Case: O(n log n)
- Worst Case: O(n log n)

**Space Complexity**: O(n) - requires auxiliary array

**Recurrence**: T(n) = 2T(n/2) + O(n)

**Properties:**
- ❌ Not in-place (standard version)
- ✅ Stable
- ❌ Not adaptive (always O(n log n))
- Guaranteed O(n log n) performance

**When to Use:**
- Guaranteed O(n log n) needed
- Stability required
- Linked lists (can be in-place)
- External sorting

### Quick Sort (Divide and Conquer)

**Idea**: Choose pivot, partition array around pivot, recursively sort partitions.

#### Pseudocode

```
QuickSort(A, low, high):
    if low < high:
        pivotIndex = Partition(A, low, high)
        QuickSort(A, low, pivotIndex - 1)
        QuickSort(A, pivotIndex + 1, high)

Partition(A, low, high):
    pivot = A[high]  // Choose last element as pivot
    i = low - 1      // Index of smaller element
    
    for j = low to high - 1:
        if A[j] < pivot:
            i = i + 1
            swap(A[i], A[j])
    
    swap(A[i + 1], A[high])
    return i + 1
```

#### Partition Schemes

**Lomuto Partition** (above):
- Simple, uses last element as pivot
- Less efficient than Hoare

**Hoare Partition**:
- Original scheme, more efficient
- Can reduce swaps

#### Complexity

**Time Complexity:**
- Best Case: O(n log n) - balanced partitions
- Average Case: O(n log n)
- Worst Case: O(n²) - already sorted with poor pivot choice

**Space Complexity**: O(log n) - recursion stack (best case)

**Properties:**
- ✅ In-place
- ❌ Not stable (standard version)
- Cache-friendly
- Good average-case performance

**Pivot Selection Strategies:**
1. **First/Last element**: Simple but bad for sorted data
2. **Random element**: Avoids worst case
3. **Median-of-three**: Middle, first, last
4. **Median-of-medians**: Guaranteed O(n log n) but slower in practice

**When to Use:**
- General-purpose sorting
- Average case more important than worst case
- Cache performance important
- Virtual memory systems

### Heap Sort

**Idea**: Build max-heap, repeatedly extract maximum.

#### Pseudocode

```
HeapSort(A):
    BuildMaxHeap(A)
    heapSize = length(A)
    
    for i = length(A) - 1 down to 1:
        swap(A[0], A[i])
        heapSize = heapSize - 1
        MaxHeapify(A, 0, heapSize)

BuildMaxHeap(A):
    heapSize = length(A)
    for i = length(A) / 2 - 1 down to 0:
        MaxHeapify(A, i, heapSize)

MaxHeapify(A, i, heapSize):
    left = 2 * i + 1
    right = 2 * i + 2
    largest = i
    
    if left < heapSize and A[left] > A[largest]:
        largest = left
    
    if right < heapSize and A[right] > A[largest]:
        largest = right
    
    if largest != i:
        swap(A[i], A[largest])
        MaxHeapify(A, largest, heapSize)
```

#### Complexity

**Time Complexity:**
- Best Case: O(n log n)
- Average Case: O(n log n)
- Worst Case: O(n log n)

**Space Complexity**: O(1) (if using iterative heapify)

**Properties:**
- ✅ In-place
- ❌ Not stable
- ❌ Not adaptive
- Guaranteed O(n log n)
- Not cache-friendly

**When to Use:**
- Guaranteed O(n log n) with O(1) space
- Priority queue implementation
- When stability not required

## Code Examples

### Bubble Sort (C++)

```cpp
#include <iostream>
#include <vector>

void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        
        if (!swapped) break;  // Already sorted
    }
}

void printArray(const std::vector<int>& arr) {
    for (int x : arr) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    
    std::cout << "Original array: ";
    printArray(arr);
    
    bubbleSort(arr);
    
    std::cout << "Sorted array: ";
    printArray(arr);
    
    return 0;
}
```

### Insertion Sort (C++)

```cpp
#include <iostream>
#include <vector>

void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        
        arr[j + 1] = key;
    }
}

int main() {
    std::vector<int> arr = {12, 11, 13, 5, 6};
    
    std::cout << "Original array: ";
    for (int x : arr) std::cout << x << " ";
    std::cout << std::endl;
    
    insertionSort(arr);
    
    std::cout << "Sorted array: ";
    for (int x : arr) std::cout << x << " ";
    std::cout << std::endl;
    
    return 0;
}
```

### Merge Sort (C++)

```cpp
#include <iostream>
#include <vector>

void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    std::vector<int> L(n1), R(n2);
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main() {
    std::vector<int> arr = {12, 11, 13, 5, 6, 7};
    
    std::cout << "Original array: ";
    for (int x : arr) std::cout << x << " ";
    std::cout << std::endl;
    
    mergeSort(arr, 0, arr.size() - 1);
    
    std::cout << "Sorted array: ";
    for (int x : arr) std::cout << x << " ";
    std::cout << std::endl;
    
    return 0;
}
```

### Quick Sort (C++)

```cpp
#include <iostream>
#include <vector>

int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    std::vector<int> arr = {10, 7, 8, 9, 1, 5};
    
    std::cout << "Original array: ";
    for (int x : arr) std::cout << x << " ";
    std::cout << std::endl;
    
    quickSort(arr, 0, arr.size() - 1);
    
    std::cout << "Sorted array: ";
    for (int x : arr) std::cout << x << " ";
    std::cout << std::endl;
    
    return 0;
}
```

### Heap Sort (C++)

```cpp
#include <iostream>
#include <vector>

void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && arr[left] > arr[largest])
        largest = left;
    
    if (right < n && arr[right] > arr[largest])
        largest = right;
    
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(std::vector<int>& arr) {
    int n = arr.size();
    
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    
    // Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    std::vector<int> arr = {12, 11, 13, 5, 6, 7};
    
    std::cout << "Original array: ";
    for (int x : arr) std::cout << x << " ";
    std::cout << std::endl;
    
    heapSort(arr);
    
    std::cout << "Sorted array: ";
    for (int x : arr) std::cout << x << " ";
    std::cout << std::endl;
    
    return 0;
}
```

## Exercises

### Easy

1. **Bubble Sort Variations**: Implement bidirectional bubble sort (cocktail sort).

2. **Counting Inversions**: Count the number of inversions in an array using merge sort.

3. **Sort Analysis**: Analyze the number of comparisons and swaps for each algorithm on different inputs.

### Medium

4. **Dutch National Flag**: Partition array into three parts (< pivot, = pivot, > pivot) in one pass.

5. **Kth Largest Element**: Find kth largest element using quickselect (based on quicksort partition).

6. **Merge K Sorted Arrays**: Merge k sorted arrays using heap (min-heap approach).

7. **Sort Linked List**: Implement merge sort for a linked list.

### Hard

8. **3-Way QuickSort**: Implement quicksort with three-way partitioning for arrays with many duplicates.

9. **External Merge Sort**: Design algorithm for sorting data larger than RAM.

10. **Hybrid Sort**: Implement a hybrid algorithm that uses quicksort with insertion sort for small subarrays.

### Challenge

11. **Parallel QuickSort**: Design parallel version of quicksort.

12. **IntroSort**: Implement introspective sort (hybrid of quicksort, heapsort, insertion sort).

13. **TimSort**: Understand and implement Python's default sorting algorithm.

## Algorithm Comparison

| Algorithm | Best | Average | Worst | Space | Stable | Adaptive |
|-----------|------|---------|-------|-------|--------|----------|
| Bubble Sort | O(n) | O(n²) | O(n²) | O(1) | Yes | Yes |
| Selection Sort | O(n²) | O(n²) | O(n²) | O(1) | No | No |
| Insertion Sort | O(n) | O(n²) | O(n²) | O(1) | Yes | Yes |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) | Yes | No |
| Quick Sort | O(n log n) | O(n log n) | O(n²) | O(log n) | No | No |
| Heap Sort | O(n log n) | O(n log n) | O(n log n) | O(1) | No | No |

## Which Algorithm to Choose?

**Small arrays (n < 50):**
- Insertion Sort

**Need stability:**
- Merge Sort or Timsort

**Need O(1) space:**
- Heap Sort or Quick Sort

**General purpose:**
- Quick Sort (with good pivot selection)
- Timsort (Python, Java default)

**Guaranteed O(n log n):**
- Merge Sort or Heap Sort

**Linked lists:**
- Merge Sort

**Nearly sorted data:**
- Insertion Sort or Timsort

## References

### Books
- **Introduction to Algorithms (CLRS)** - Chapters 2, 6, 7, 8
  - Chapter 2: Getting Started (Insertion Sort)
  - Chapter 6: Heapsort
  - Chapter 7: Quicksort
  - Chapter 8: Sorting in Linear Time

- **Algorithms** by Sedgewick & Wayne - Chapter 2

### Online Resources
- [VisuAlgo - Sorting](https://visualgo.net/en/sorting)
- [Sorting Algorithm Animations](https://www.toptal.com/developers/sorting-algorithms)
- [GeeksforGeeks - Sorting Algorithms](https://www.geeksforgeeks.org/sorting-algorithms/)
- [Comparison Sorting Visualizations](https://www.cs.usfca.edu/~galles/visualization/ComparisonSort.html)

### Videos
- [15 Sorting Algorithms in 6 Minutes](https://www.youtube.com/watch?v=kPRA0W1kECg)
- Abdul Bari - Sorting Algorithms YouTube series

## Summary

In this module, we covered:
- ✅ Simple sorts: bubble, selection, insertion
- ✅ Efficient sorts: merge, quick, heap
- ✅ Time and space complexity analysis
- ✅ Stability, adaptivity, and in-place properties
- ✅ When to use each algorithm

**Next Steps:** Proceed to [Module 7: Linear Time Sorting & Order Statistics](07_linear_sorting.md) to learn about non-comparison-based sorting and selection algorithms.

---

*💡 Tip: For general use, choose quicksort. For guaranteed O(n log n), use merge sort or heap sort!*
