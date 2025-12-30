#include <iostream>
#include <chrono>
#include <cstring>
#include <iomanip>
#include <fstream>

using namespace std;
using namespace chrono;

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void swap(float& a, float& b) {
    float temp = a;
    a = b;
    b = temp;
}
void insertionSortFloat(float arr[], int n) {
    for (int i = 1; i < n; i++) {
        float key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void insertionSortInt(int arr[], int n) {
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

void bucketSort(float arr[], int n) {
    if (n <= 0) return;
    
    float** buckets = new float*[n];
    int* bucketSizes = new int[n];
    int* bucketCapacities = new int[n]; 
    for (int i = 0; i < n; i++) {
        bucketSizes[i] = 0;
        bucketCapacities[i] = 2;
        buckets[i] = new float[bucketCapacities[i]];
    }
    
    for (int i = 0; i < n; i++) {
        int bucketIndex = (int)(n * arr[i]);
        if (bucketIndex >= n) bucketIndex = n - 1;
        if (bucketSizes[bucketIndex] == bucketCapacities[bucketIndex]) {
            int newCapacity = bucketCapacities[bucketIndex] * 2;
            float* newBucket = new float[newCapacity];
            for (int j = 0; j < bucketSizes[bucketIndex]; j++) {
                newBucket[j] = buckets[bucketIndex][j];
            }
            delete[] buckets[bucketIndex];
            buckets[bucketIndex] = newBucket;
            bucketCapacities[bucketIndex] = newCapacity;
        }
        buckets[bucketIndex][bucketSizes[bucketIndex]++] = arr[i];
    }




    for (int i = 0; i < n; i++) {
        if (bucketSizes[i] > 0) {
            insertionSortFloat(buckets[i], bucketSizes[i]);
        }
    }
    int index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < bucketSizes[i]; j++) {
            arr[index++] = buckets[i][j];
        }
    }
    



    for (int i = 0; i < n; i++) {
        delete[] buckets[i];
    }
    delete[] buckets;
    delete[] bucketSizes;
    delete[] bucketCapacities;
}






void bucketSortInt(int arr[], int n) {
    if (n <= 0) return;
    int minVal = arr[0], maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < minVal) minVal = arr[i];

        if (arr[i] > maxVal) maxVal = arr[i];
    }
    
    if (minVal == maxVal) return; 
    int bucketCount = (n < 5) ? n : n / 5; 
    int** buckets = new int*[bucketCount];
    int* bucketSizes = new int[bucketCount];
    int* bucketCapacities = new int[bucketCount];
    
    for (int i = 0; i < bucketCount; i++) {
        bucketSizes[i] = 0;
        bucketCapacities[i] = 10;
        buckets[i] = new int[bucketCapacities[i]];
    }
    int range = maxVal - minVal + 1;
    for (int i = 0; i < n; i++) {
        int bucketIndex = (int)((long long)(arr[i] - minVal) * bucketCount / range);
        if (bucketIndex >= bucketCount) bucketIndex = bucketCount - 1;
        



        if (bucketSizes[bucketIndex] == bucketCapacities[bucketIndex]) {
            int newCapacity = bucketCapacities[bucketIndex] * 2;
            int* newBucket = new int[newCapacity];
            for (int j = 0; j < bucketSizes[bucketIndex]; j++) {
                newBucket[j] = buckets[bucketIndex][j];
            }
            delete[] buckets[bucketIndex];
            buckets[bucketIndex] = newBucket;
            bucketCapacities[bucketIndex] = newCapacity;
        }
        
        buckets[bucketIndex][bucketSizes[bucketIndex]++] = arr[i];
    }
    


    int index = 0;
    for (int i = 0; i < bucketCount; i++) {
        if (bucketSizes[i] > 0) {
            insertionSortInt(buckets[i], bucketSizes[i]);
            for (int j = 0; j < bucketSizes[i]; j++) {
                arr[index++] = buckets[i][j];
            }
        }
    }
    




    for (int i = 0; i < bucketCount; i++) {
        delete[] buckets[i];
    }
    delete[] buckets;
    delete[] bucketSizes;
    delete[] bucketCapacities;
}



int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    int* L = new int[n1];
    int* R = new int[n2];
    
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    
    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}



void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;
    
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}


struct Person {
    char name[50];
    int age;
    float salary;
    
    void display() const {
        cout << "Name: " << setw(10) << name 
             << ", Age: " << setw(3) << age 
             << ", Salary: " << setw(8) << salary << endl;
    }
};

bool compareByAge(const Person& a, const Person& b) {
    return a.age < b.age;
}

bool compareBySalary(const Person& a, const Person& b) {
    return a.salary < b.salary;}

bool compareMultiCriteria(const Person& a, const Person& b) {
    if (a.age != b.age) return a.age < b.age;
    return a.salary > b.salary;
}
void sortPersons(Person arr[], int n, bool (*comparator)(const Person&, const Person&)) {
    for (int i = 1; i < n; i++) {
        Person key = arr[i];
        int j = i - 1;
        while (j >= 0 && !comparator(arr[j], key)) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
void pushHeap(int arr[], int heapSize) {
    int i = heapSize - 1;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (arr[i] <= arr[parent]) break;
        swap(arr[i], arr[parent]);
        i = parent;
    }
}

void popHeap(int arr[], int heapSize) {
    swap(arr[0], arr[heapSize - 1]);
    int i = 0;
    while (true) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;
        
        if (left < heapSize - 1 && arr[left] > arr[largest])
            largest = left;
        if (right < heapSize - 1 && arr[right] > arr[largest])
            largest = right;
        



        if (largest == i) break;
        swap(arr[i], arr[largest]);
        i = largest;
    }
}

void partialSortManual(int arr[], int n, int k) {
    if (k >= n) {
        insertionSortInt(arr, n);
        return;
    }
    for (int i = 1; i < k; i++) { pushHeap(arr, i + 1);}
    
    for (int i = k; i < n; i++) {
        if (arr[i] < arr[0]) {
            popHeap(arr, k);
            arr[k - 1] = arr[i];
            pushHeap(arr, k);
        }
    }
    for (int i = k - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
void insertionSort(int arr[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void hybridSort(int arr[], int left, int right) {
    const int INSERTION_THRESHOLD = 10;
    const int BUCKET_THRESHOLD = 1000;
    
    int size = right - left + 1;
    
    if (size <= INSERTION_THRESHOLD) {
        insertionSort(arr, left, right);
    }
    else if (size <= BUCKET_THRESHOLD) {
        quickSort(arr, left, right);
    }
    else {
        bucketSortInt(arr + left, size);
    }
}



// chat gpt
void compareAlgorithms(ofstream& outFile) {
    int sizes[] = {100, 500, 1000, 2000, 5000, 10000, 20000, 50000};
    int numSizes = 8;
    

    outFile << "Size,BucketSort,QuickSort,MergeSort,HeapSort,HybridSort\n";
    
    for (int s = 0; s < numSizes; s++) {
        int n = sizes[s];

        int* original = new int[n];
        srand(12345);
        for (int i = 0; i < n; i++) {
            original[i] = rand() % 10000;
        }
        
        outFile << n;
        
        int* arr1 = new int[n];
        memcpy(arr1, original, n * sizeof(int));
        auto start = high_resolution_clock::now();
        bucketSortInt(arr1, n);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "  Bucket Sort:     " << setw(8) << duration.count() << " μs" << endl;
        outFile << "," << duration.count();
        delete[] arr1;
        
        // Quick Sort
        int* arr2 = new int[n];
        memcpy(arr2, original, n * sizeof(int));
        start = high_resolution_clock::now();
        quickSort(arr2, 0, n - 1);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        cout << "  Quick Sort:      " << setw(8) << duration.count() << " μs" << endl;
        outFile << "," << duration.count();
        delete[] arr2;
        
        // Merge Sort
        int* arr3 = new int[n];
        memcpy(arr3, original, n * sizeof(int));
        start = high_resolution_clock::now();
        mergeSort(arr3, 0, n - 1);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        cout << "  Merge Sort:      " << setw(8) << duration.count() << " μs" << endl;
        outFile << "," << duration.count();
        delete[] arr3;
        
        // Heap Sort
        int* arr4 = new int[n];
        memcpy(arr4, original, n * sizeof(int));
        start = high_resolution_clock::now();
        heapSort(arr4, n);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        cout << "  Heap Sort:       " << setw(8) << duration.count() << " μs" << endl;
        outFile << "," << duration.count();
        delete[] arr4;
        
        // Hybrid Sort
        int* arr5 = new int[n];
        memcpy(arr5, original, n * sizeof(int));
        start = high_resolution_clock::now();
        hybridSort(arr5, 0, n - 1);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        cout << "  Hybrid Sort:     " << setw(8) << duration.count() << " μs" << endl;
        outFile << "," << duration.count();
        delete[] arr5;
        
        outFile << "\n";
        delete[] original;
        cout << endl;
    }
}


// chat gpt
int main() {
    ofstream resultsFile("sorting_results.csv");
    if (!resultsFile.is_open()) {
        cerr << "Nie można otworzyć pliku do zapisu!" << endl;
        return 1;
    }

    float arr1[] = {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    cout << "Przed sortowaniem: ";
    for (int i = 0; i < n1; i++) cout << arr1[i] << " ";
    cout << endl;
    bucketSort(arr1, n1);
    cout << "Po sortowaniu:     ";
    for (int i = 0; i < n1; i++) cout << arr1[i] << " ";
    cout << "\n\nPrzypadki użycia Bucket Sort:" << endl;
    cout << "- Dane z ograniczonego zakresu (np. 0-1)" << endl;
    cout << "- Dane równomiernie rozłożone" << endl;
    cout << "- Liczby zmiennoprzecinkowe w znanym zakresie" << endl;
    cout << "- Sortowanie wyników testów (0-100%)" << endl;
    
    cout << "\n\n--- 2. SORTOWANIE NIESTANDARDOWYCH DANYCH ---" << endl;
    Person people[5] = {
        {"Anna", 25, 5000.50},
        {"Jan", 30, 6000.00},
        {"Katarzyna", 25, 5500.00},
        {"Piotr", 35, 7000.00},
        {"Maria", 28, 5200.00}
    };
    int nPeople = 5;
    
    cout << "\nDane oryginalne:" << endl;
    for (int i = 0; i < nPeople; i++) people[i].display();
    
    Person peopleCopy[5];
    
    memcpy(peopleCopy, people, sizeof(people));
    cout << "\nPosortowane według wieku:" << endl;
    sortPersons(peopleCopy, nPeople, compareByAge);
    for (int i = 0; i < nPeople; i++) peopleCopy[i].display();
    
    memcpy(peopleCopy, people, sizeof(people));
    cout << "\nPosortowane według pensji:" << endl;
    sortPersons(peopleCopy, nPeople, compareBySalary);
    for (int i = 0; i < nPeople; i++) peopleCopy[i].display();
    
    memcpy(peopleCopy, people, sizeof(people));
    cout << "\nPosortowane wielokryterialnie (wiek rosnąco, pensja malejąco):" << endl;
    sortPersons(peopleCopy, nPeople, compareMultiCriteria);
    for (int i = 0; i < nPeople; i++) peopleCopy[i].display();
    
    cout << "\n\n--- 3. SORTOWANIE CZĄSTKOWE (PARTIAL SORT) ---" << endl;
    int arr3[] = {64, 25, 12, 22, 11, 90, 88, 45, 50, 23};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int k = 3;
    
    cout << "Tablica oryginalna: ";
    for (int i = 0; i < n3; i++) cout << arr3[i] << " ";
    cout << endl;
    
    partialSortManual(arr3, n3, k);
    cout << "Po sortowaniu " << k << " najmniejszych: ";
    for (int i = 0; i < n3; i++) {
        if (i == k) cout << "| ";
        cout << arr3[i] << " ";
    }
    cout << "\n(Pierwsze " << k << " elementów są posortowane)" << endl;
    cout << "\nZastosowania partial sort:" << endl;
    cout << "- Top K elementów (np. 10 najlepszych wyników)" << endl;
    cout << "- Mediana i percentyle" << endl;
    cout << "- Systemy rekomendacji" << endl;
    
    cout << "\n\n--- 4. HYBRYDOWY ALGORYTM SORTOWANIA ---" << endl;
    cout << "Kryteria wyboru algorytmu:" << endl;
    cout << "- n <= 10:        Insertion Sort (niski overhead)" << endl;
    cout << "- 10 < n <= 1000: Quick Sort (szybki średnio)" << endl;
    cout << "- n > 1000:       Bucket Sort (dla dużych zbiorów)" << endl;
    
    int arr4[] = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    cout << "\nPrzykład (n=" << n4 << ", użyje Insertion Sort):" << endl;
    cout << "Przed: ";
    for (int i = 0; i < n4; i++) cout << arr4[i] << " ";
    cout << endl;
    hybridSort(arr4, 0, n4 - 1);
    cout << "Po:    ";
    for (int i = 0; i < n4; i++) cout << arr4[i] << " ";
    cout << endl;
    
    cout << "\n\n--- 5. SORTOWANIE W MIEJSCU (IN-PLACE) ---" << endl;
    cout << "\nAlgorytmy IN-PLACE (O(1) dodatkowej pamięci):" << endl;
    cout << "- Heap Sort:      O(n log n), zawsze" << endl;
    cout << "- Quick Sort:     O(n log n) średnio, O(n²) najgorszy" << endl;
    cout << "- Insertion Sort: O(n²), dobry dla małych n" << endl;
    
    cout << "\nAlgorytmy NON IN-PLACE (wymagają dodatkowej pamięci):" << endl;
    cout << "- Merge Sort:     O(n) pamięci, O(n log n) zawsze" << endl;
    cout << "- Bucket Sort:    O(n+k) pamięci, O(n+k) dla równomiernych danych" << endl;
    cout << "- Counting Sort:  O(k) pamięci, O(n+k)" << endl;
    
    int arr5[] = {12, 11, 13, 5, 6, 7};
    int n5 = sizeof(arr5) / sizeof(arr5[0]);
    cout << "\nDemonstracja Heap Sort (in-place):" << endl;
    cout << "Przed: ";
    for (int i = 0; i < n5; i++) cout << arr5[i] << " ";
    cout << endl;
    heapSort(arr5, n5);
    cout << "Po:    ";
    for (int i = 0; i < n5; i++) cout << arr5[i] << " ";
    cout << endl;
    
    compareAlgorithms(resultsFile);
    
    resultsFile.close();
    cout << "\n✓ Wyniki zapisane do pliku: sorting_results.csv" << endl;
    return 0;
}
