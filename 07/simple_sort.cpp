#include <iostream>
#include <random>
#include <ctime>
#include <cstring>

using namespace std;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void select_sort(int arr[], int size, int &comparisons, int &swaps) {
    comparisons = 0;
    swaps = 0;

    for (int i = 0; i < size - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < size; j++) {
            comparisons++;
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            swap(arr[i], arr[min_index]);
            swaps++;
        }
    }
}

void insert_sort(int arr[], int size, int &comparisons, int &swaps) {
    comparisons = 0;
    swaps = 0;

    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0) {
            comparisons++;
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                swaps++;
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
    }
}

int getNextGap(int gap) {
    gap = (gap * 10) / 13;
    if (gap < 1) {
        return 1;
    }
    return gap;
}

void comb_sort(int arr[], int size, int &comparisons, int &swaps) {
    comparisons = 0;
    swaps = 0;
    int gap = size;
    bool swapped = true;

    while (gap != 1 || swapped) {
        gap = getNextGap(gap);
        swapped = false;

        for (int i = 0; i < size - gap; i++) {
            comparisons++;
            if (arr[i] > arr[i + gap]) {
                swap(arr[i], arr[i + gap]);
                swapped = true;
                swaps++;
            }
        }
    }
}

void shell_sort(int arr[], int size, int &comparisons, int &swaps) {
    comparisons = 0;
    swaps = 0;

    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap; j -= gap) {
                comparisons++;
                if (arr[j - gap] > temp) {
                    arr[j] = arr[j - gap];
                    swaps++;
                } else {
                    break;
                }
            }
            arr[j] = temp;
        }
    }
}

void bubble_sort(int arr[], int size, int &comparisons, int &swaps) {
    comparisons = 0;
    swaps = 0;

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swaps++;
            }
        }
    }
}

void testSort(const char* name, void (*sortFunc)(int[], int, int&, int&), 
              int original[], int size, FILE* file) {
    int* arr = new int[size];
    memcpy(arr, original, size * sizeof(int));
    
    int comparisons, swaps;
    clock_t start = clock();
    sortFunc(arr, size, comparisons, swaps);
    clock_t end = clock();
    
    double time_ms = (double(end - start) / CLOCKS_PER_SEC) * 1000.0;
    
    fprintf(file, "%s, Size: %d, Time: %.3f ms, Comparisons: %d, Swaps: %d\n",
            name, size, time_ms, comparisons, swaps);
    
    printf("%s (n=%d): %.3f ms, Comparisons: %d, Swaps: %d\n",
           name, size, time_ms, comparisons, swaps);
    
    delete[] arr;
}

int main() {
    const int SIZES[] = {1000, 5000, 10000};
    const int NUM_SIZES = 3;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100000);

    FILE* file = fopen("sorting_results.txt", "w");
    if (file == nullptr) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    for (int s = 0; s < NUM_SIZES; s++) {
        int size = SIZES[s];
        int* original = new int[size];
        
        for (int i = 0; i < size; i++) {
            original[i] = dis(gen);
        }

        printf("\n=== Testing with array size: %d ===\n", size);
        fprintf(file, "\n=== Array size: %d ===\n", size);

        testSort("Bubble Sort", bubble_sort, original, size, file);
        testSort("Insertion Sort", insert_sort, original, size, file);
        testSort("Selection Sort", select_sort, original, size, file);
        testSort("Comb Sort", comb_sort, original, size, file);
        testSort("Shell Sort", shell_sort, original, size, file);

        delete[] original;
    }

    fclose(file);
    printf("\nResults saved to sorting_results.txt\n");

    return 0;
}
