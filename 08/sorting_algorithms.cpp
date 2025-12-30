#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstring>
#include <iomanip>
#include <fstream>

using namespace std;
using namespace chrono;


void bucketSort(float arr[], int n) {

    vector<float> buckets[n];
    for (int i = 0; i < n; i++) {
        int bucketIndex = n * arr[i];
        buckets[bucketIndex].push_back(arr[i]);
    }
    
    for (int i = 0; i < n; i++) {
        sort(buckets[i].begin(), buckets[i].end());
    }
    
    int index = 0;
    for (int i = 0; i < n; i++) {
        for (size_t j = 0; j < buckets[i].size(); j++) {
            arr[index++] = buckets[i][j];
        }
    }
}

void bucketSortInt(int arr[], int n) {
    if (n <= 0) return;
    
    int minVal = arr[0], maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
    }
    
    // Tworzenie kubełków
    int range = maxVal - minVal + 1;
    int bucketCount = max(1, n / 5); // Heurystyka: n/5 kubełków
    vector<int> buckets[bucketCount];
    
    // Dystrybucja elementów do kubełków
    for (int i = 0; i < n; i++) {
        int bucketIndex = (arr[i] - minVal) * bucketCount / range;
        if (bucketIndex >= bucketCount) bucketIndex = bucketCount - 1;
        buckets[bucketIndex].push_back(arr[i]);
    }
    
    // Sortowanie każdego kubełka i łączenie
    int index = 0;
    for (int i = 0; i < bucketCount; i++) {
        sort(buckets[i].begin(), buckets[i].end());
        for (size_t j = 0; j < buckets[i].size(); j++) {
            arr[index++] = buckets[i][j];
        }
    }
}

// ============================================
// 2. INNE ALGORYTMY SORTOWANIA (DO PORÓWNANIA)
// ============================================

// Quick Sort
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

// Merge Sort
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

// Heap Sort (sortowanie w miejscu)
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

// ============================================
// 3. SORTOWANIE NIESTANDARDOWYCH DANYCH
// ============================================

struct Person {
    string name;
    int age;
    float salary;
    
    void display() const {
        cout << "Name: " << setw(10) << name 
             << ", Age: " << setw(3) << age 
             << ", Salary: " << setw(8) << salary << endl;
    }
};

// Komparator wielokryterialny
bool compareByAge(const Person& a, const Person& b) {
    return a.age < b.age;
}

bool compareBySalary(const Person& a, const Person& b) {
    return a.salary < b.salary;
}

bool compareMultiCriteria(const Person& a, const Person& b) {
    if (a.age != b.age) return a.age < b.age;
    return a.salary > b.salary; // Malejąco po pensji jeśli wiek taki sam
}

template<typename T>
void sortCustomData(vector<T>& data, bool (*comparator)(const T&, const T&)) {
    sort(data.begin(), data.end(), comparator);
}

// ============================================
// 4. SORTOWANIE CZĄSTKOWE (PARTIAL SORT)
// ============================================

void partialSort(int arr[], int n, int k) {
    // Sortuje tylko k pierwszych najmniejszych elementów
    partial_sort(arr, arr + k, arr + n);
}

// Własna implementacja partial sort używając heap
void partialSortManual(int arr[], int n, int k) {
    // Tworzymy max-heap z pierwszych k elementów
    make_heap(arr, arr + k);
    
    // Dla pozostałych elementów
    for (int i = k; i < n; i++) {
        if (arr[i] < arr[0]) {
            pop_heap(arr, arr + k);
            arr[k - 1] = arr[i];
            push_heap(arr, arr + k);
        }
    }
    
    // Sortujemy k elementów
    sort_heap(arr, arr + k);
}

// ============================================
// 5. HYBRYDOWY ALGORYTM SORTOWANIA
// ============================================

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
    
    // Dla małych tablic: Insertion Sort (O(n²) ale szybki dla małych n)
    if (size <= INSERTION_THRESHOLD) {
        insertionSort(arr, left, right);
    }
    // Dla średnich tablic: Quick Sort (O(n log n) średnio)
    else if (size <= BUCKET_THRESHOLD) {
        quickSort(arr, left, right);
    }
    // Dla dużych tablic z ograniczonym zakresem: Bucket Sort
    else {
        bucketSortInt(arr + left, size);
    }
}

// ============================================
// 6. PORÓWNANIE ALGORYTMÓW
// ============================================

void compareAlgorithms(ofstream& outFile) {
    vector<int> sizes = {100, 500, 1000, 2000, 5000, 10000, 20000, 50000};
    
    cout << "\n========================================" << endl;
    cout << "PORÓWNANIE ALGORYTMÓW SORTOWANIA" << endl;
    cout << "========================================\n" << endl;
    
    // Nagłówek pliku CSV
    outFile << "Size,BucketSort,QuickSort,MergeSort,HeapSort,HybridSort\n";
    
    for (int n : sizes) {
        cout << "Testowanie dla n = " << n << "..." << endl;
        
        int* original = new int[n];
        srand(12345); // Stały seed dla powtarzalności
        for (int i = 0; i < n; i++) {
            original[i] = rand() % 10000;
        }
        
        outFile << n;
        
        // Bucket Sort
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

// ============================================
// GŁÓWNA FUNKCJA DEMONSTRACYJNA
// ============================================

int main() {
    // Otwarcie pliku do zapisu wyników
    ofstream resultsFile("sorting_results.csv");
    if (!resultsFile.is_open()) {
        cerr << "Nie można otworzyć pliku do zapisu!" << endl;
        return 1;
    }
    
    cout << "\n╔════════════════════════════════════════════════════════╗" << endl;
    cout << "║      ALGORYTMY SORTOWANIA - KOMPLETNA DEMONSTRACJA    ║" << endl;
    cout << "╚════════════════════════════════════════════════════════╝\n" << endl;
    
    // 1. BUCKET SORT
    cout << "\n--- 1. BUCKET SORT ---" << endl;
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
    
    // 2. SORTOWANIE NIESTANDARDOWYCH DANYCH
    cout << "\n\n--- 2. SORTOWANIE NIESTANDARDOWYCH DANYCH ---" << endl;
    vector<Person> people = {
        {"Anna", 25, 5000.50},
        {"Jan", 30, 6000.00},
        {"Katarzyna", 25, 5500.00},
        {"Piotr", 35, 7000.00},
        {"Maria", 28, 5200.00}
    };
    
    cout << "\nDane oryginalne:" << endl;
    for (const auto& p : people) p.display();
    
    cout << "\nPosortowane według wieku:" << endl;
    sortCustomData(people, compareByAge);
    for (const auto& p : people) p.display();
    
    cout << "\nPosortowane według pensji:" << endl;
    sortCustomData(people, compareBySalary);
    for (const auto& p : people) p.display();
    
    cout << "\nPosortowane wielokryterialnie (wiek rosnąco, pensja malejąco):" << endl;
    sortCustomData(people, compareMultiCriteria);
    for (const auto& p : people) p.display();
    
    // 3. SORTOWANIE CZĄSTKOWE
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
    
    // 4. HYBRYDOWY ALGORYTM
    cout << "\n\n--- 4. HYBRYDOWY ALGORYTM SORTOWANIA ---" << endl;
    cout << "Kryteria wyboru algorytmu:" << endl;
    cout << "- n <= 10:    Insertion Sort (niski overhead)" << endl;
    cout << "- 10 < n <= 1000: Quick Sort (szybki średnio)" << endl;
    cout << "- n > 1000:   Bucket Sort (dla dużych zbiorów)" << endl;
    
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
    
    // 5. IN-PLACE VS NON IN-PLACE
    cout << "\n\n--- 5. SORTOWANIE W MIEJSCU (IN-PLACE) ---" << endl;
    cout << "\nAlgorytmy IN-PLACE (O(1) dodatkowej pamięci):" << endl;
    cout << "- Heap Sort:      O(n log n), zawsze, stabilny względem czasu" << endl;
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
    
    // 6. PORÓWNANIE WYDAJNOŚCI
    compareAlgorithms(resultsFile);
    
    resultsFile.close();
    cout << "\n✓ Wyniki zapisane do pliku: sorting_results.csv" << endl;
    
    // PODSUMOWANIE
    cout << "\n\n╔════════════════════════════════════════════════════════╗" << endl;
    cout << "║                     PODSUMOWANIE                       ║" << endl;
    cout << "╚════════════════════════════════════════════════════════╝" << endl;
    cout << "\nWybór algorytmu zależy od:" << endl;
    cout << "1. Rozmiaru danych (n)" << endl;
    cout << "2. Zakresu wartości (k)" << endl;
    cout << "3. Dostępnej pamięci" << endl;
    cout << "4. Rozkładu danych (losowe/częściowo posortowane)" << endl;
    cout << "5. Wymagań stabilności sortowania" << endl;
    cout << "6. Gwarancji czasowych (średni vs najgorszy przypadek)" << endl;
    
    return 0;
}
