#include <algorithm>
#include <iostream>
#include <vector>

template <typename T> class heap {
private:
  std::vector<T> arr;
  bool is_min_heap = true;

  void bubbleUp(int index) {
    while (index > 0) {
      int parent = (index - 1) / 2;
      if (is_min_heap ? (arr[index] < arr[parent])
                      : (arr[index] > arr[parent])) {
        std::swap(arr[index], arr[parent]);
        index = parent;
      } else {
        break;
      }
    }
  }
  void bubbleDown(int index) {
    while (true) {
      int left = 2 * index + 1;
      int right = 2 * index + 2;
      int largest = index;

      if (left < arr.size() && (is_min_heap ? (arr[left] < arr[largest])
                                            : (arr[left] > arr[largest]))) {
        largest = left;
      }

      if (right < arr.size() && (is_min_heap ? (arr[right] < arr[largest])
                                             : (arr[right] > arr[largest]))) {
        largest = right;
      }

      if (largest == index) {
        break;
      }

      std::swap(arr[index], arr[largest]);
      index = largest;
    }
  }

public:
  heap(bool is_min) : is_min_heap(is_min) {}

  void push(T val) {
    arr.push_back(val);
    bubbleUp(arr.size() - 1);
  }

  void print() {
    for (const auto &i : arr) {
      std::cout << i << " ";
    }
    std::cout << std::endl;
  }
  T extract() {
    T top = arr[0];
    arr.pop_back();
    if (!arr.empty()) {
      arr[0] = arr.back();
      bubbleDown(0);
    }
    return top;
  };
};
int main() {
  std::vector<int> abu = {5, 2, 1, 8, 3};
  heap<int> h(false);

  for (int x : abu) {
    h.push(x);
  }

  std::cout << "Min-Heap elements: ";
  h.print();

  return 0;
}