#include <iostream>
#include <random>


struct Student {
    std::string name;
    int age;
    double gpa;
};

void insertion_sort_by_gpa(Student arr[], int n) {
    for (int i = 1; i < n; ++i) {
        Student key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].gpa > key.gpa) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// void insertion_sort_by_age```cpp
// Structure for custom data with multiple attributes
struct Student {
    std::string name;
    int age;
    double gpa;
    
    Student() : name(""), age(0), gpa(0.0) {}
    Student(std::string n, int a, double g) : name(n), age(a), gpa(g) {}
};

// Comparator functions for different sorting criteria
bool compare_by_age(const Student& a, const Student& b) {
    return a.age < b.age;
}

bool compare_by_gpa(const Student& a, const Student& b) {
    return a.gpa < b.gpa;
}

bool compare_by_name(const Student& a, const Student& b) {
    return a.name < b.name;
}

// Generic insertion sort with custom comparator
template<typename T, typename Compare>
void insertion_sort(T arr[], int n, Compare comp) {
    for (int i = 1; i < n; ++i) {
        T key = arr[i];
        int j = i - 1;
        while (j >= 0 && comp(key, arr[j])) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// Bucket sort for custom objects using a key extractor
template<typename T, typename KeyExtractor>
void bucket_sort_custom(T arr[], int n, int bucket_count, KeyExtractor get_key) {
    if (n <= 0) return;
    
    // Find max and min keys
    int max_key = get_key(arr[0]);
    int min_key = get_key(arr[0]);
    for (int i = 1; i < n; ++i) {
        int key = get_key(arr[i]);
        if (key > max_key) max_key = key;
        if (key < min_key) min_key = key;
    }
    
    int range = (max_key - min_key + 1) / bucket_count + 1;
    
    T** buckets = new T*[bucket_count];
    int* bucket_sizes = new int[bucket_count]();
    
    for (int i = 0; i < bucket_count; ++i) {
        buckets[i] = new T[n];
    }
    
    for (int i = 0; i < n; ++i) {
        int bucket_index = (get_key(arr[i]) - min_key) / range;
        buckets[bucket_index][bucket_sizes[bucket_index]++] = arr[i];
    }
    
    int index = 0;
    for (int b = 0; b < bucket_count; ++b) {
        // Sort bucket using insertion sort with key-based comparison
        for (int i = 1; i < bucket_sizes[b]; ++i) {
            T key_obj = buckets[b][i];
            int j = i - 1;
            while (j >= 0 && get_key(buckets[b][j]) > get_key(key_obj)) {
                buckets[b][j + 1] = buckets[b][j];
                --j;
            }
            buckets[b][j + 1] = key_obj;
        }
        
        for (int i = 0; i < bucket_sizes[b]; ++i) {
            arr[index++] = buckets[b][i];
        }
    }
    
    for (int i = 0; i < bucket_count; ++i) {
        delete[] buckets[i];
    }
    delete[] buckets;
    delete[] bucket_sizes;
}


void bucket_sort(int arr[], int n, int bucket_count) {
    // Find maximum and minimum values
    int max_value = arr[0];
    int min_value = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] > max_value) max_value = arr[i];
        if (arr[i] < min_value) min_value = arr[i];
    }
    
    int range = (max_value - min_value + 1) / bucket_count + 1;

    // Create buckets using dynamic arrays
    int** buckets = new int*[bucket_count];
    int* bucket_sizes = new int[bucket_count]();
    
    // Allocate max possible size for each bucket
    for (int i = 0; i < bucket_count; ++i) {
        buckets[i] = new int[n];
    }

    // Distribute input array values into buckets
    for (int i = 0; i < n; ++i) {
        int bucket_index = (arr[i] - min_value) / range;
        buckets[bucket_index][bucket_sizes[bucket_index]++] = arr[i];
    }

    // Sort individual buckets using insertion sort and concatenate results
    int index = 0;
    for (int b = 0; b < bucket_count; ++b) {
        // Insertion sort for current bucket
        for (int i = 1; i < bucket_sizes[b]; ++i) {
            int key = buckets[b][i];
            int j = i - 1;
            while (j >= 0 && buckets[b][j] > key) {
                buckets[b][j + 1] = buckets[b][j];
                --j;
            }
            buckets[b][j + 1] = key;
        }
        
        // Copy sorted bucket to result
        for (int i = 0; i < bucket_sizes[b]; ++i) {
            arr[index++] = buckets[b][i];
        }
    }

    // Free memory
    for (int i = 0; i < bucket_count; ++i) {
        delete[] buckets[i];
    }
    delete[] buckets;
    delete[] bucket_sizes;
}