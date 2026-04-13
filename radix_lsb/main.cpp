#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

namespace radix {
using longVector = std::vector<long>;

longVector createArray(int size) {
    longVector arr(size);
    std::iota(arr.begin(), arr.end(), 1);
    return arr;
}

void shuffle(longVector& arr) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(arr.begin(), arr.end(), g);
}

int maxBits(const longVector& arr) {
    if (arr.empty()) return 0;
    long maxVal = *std::max_element(arr.begin(), arr.end());
    return (maxVal == 0) ? 1 : static_cast<int>(std::log2(maxVal)) + 1;
}

void sort(longVector& arr) {
    int bitsCount = maxBits(arr);
    int n = arr.size();

    for (int i = 0; i < bitsCount; ++i) {
        longVector temp(n);
        int pos0 = 0;
        int count0 = 0;

        for (long num : arr) {
            if (!(num & (1L << i))) count0++;
        }

        int pos1 = count0;

        for (long num : arr) {
            if (!(num & (1L << i))) {
                temp[pos0++] = num;
            } else {
                temp[pos1++] = num;
            }
        }
        arr = std::move(temp);
        std::cout << "Bit " << i << " processado." << std::endl;
    }
}
}  // namespace radix