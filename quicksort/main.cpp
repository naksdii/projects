#include <algorithm>  // For std::swap
#include <iostream>
#include <stack>
#include <vector>
void quickSort(std::vector<int>& arr) {
    if (arr.empty()) return;

    // Stack stores the [low, high] boundaries
    std::stack<std::pair<int, int>> s;
    s.push({0, (int)arr.size() - 1});

    while (!s.empty()) {
        int low = s.top().first;
        int high = s.top().second;
        s.pop();

        if (low >= high) continue;

        // --- Partition Logic (Lomuto scheme) ---
        int pivot = arr[high];  // Choosing the last element as pivot
        int i = low;

        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                std::swap(arr[i], arr[j]);
                i++;
            }
        }
        std::swap(arr[i], arr[high]);
        // Pivot is now at index 'i'

        // Push right side
        if (i + 1 < high) s.push({i + 1, high});
        // Push left side
        if (low < i - 1) s.push({low, i - 1});
    }
}
int main() {
    std::vector<int> list = {0};
    for(int i =0;i<100;++i)
    {
        list.push_back(100-i);
    }
    quickSort(list);
    for (const auto& i : list) {
        std::cout << i << '\n';
    };
}
