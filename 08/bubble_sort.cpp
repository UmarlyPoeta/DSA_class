#include <iostream>

void bubble_sort(int arr[], int n) {
  int tmp;
  int c = 0;
  for (int i = 0; i < n - 1; i++) {
    c = 0;
    for (int j = i + 1; j < n; j++) {
      if (arr[i] > arr[j]) {
        tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
        c++;
      }
    }
    if (!c) {
      break;
    }
  }
}

int main() {
  int arr[] = {3, 4, 2, 0, 20, 1};
  int n = sizeof(arr) / sizeof(arr[0]);
  std::cout << "arr before sort: ";
  for (int i = 0; i < n; ++i) std::cout << arr[i] << ' ';
  std::cout << std::endl;
  bubble_sort(arr, n);
  std::cout << "arr after sort: ";
  for (int i = 0; i < n; ++i) std::cout << arr[i] << ' ';
  std::cout << std::endl;
  return 0;
}
