#include <iostream>
#include <vector>
#include <string>
// #include <sstream>
#include <numeric>
// #include <algorithm>

bool is_quad(std::string ex) {
    std::vector<int> sides;
    for (const auto& c : ex) {
        if (c == ' ') continue;
        if (c == '\n') break;
        sides.push_back(c - '0');
    }
    if (sides.size() != 4) return false;
    long long total_sum = std::accumulate(sides.begin(), sides.end(), 0LL);
    
    for (long long s : sides) {
        if (s >= total_sum - s) {
            return false;
        }
    }
    return true;
}

void clean(std::string* s) {
    for (size_t i = 0; i < s->length();) {
        if ((*s)[i] == '\n' || (*s)[i] == '\r') {
            s->erase(i, 1);
        } else {
            i++;
        }
    }
}

int main() {
    int times;
    std::vector<std::string> data;
    std::cin >> times;
    std::string buffer;
    std::getline(std::cin, buffer);
    for (int i = 0; i < times; i++) {
        std::getline(std::cin, buffer);
        data.push_back(buffer);
    }
    for (std::string& s : data) {
        clean((std::string*)&s);
        std::cout << (is_quad(s) ? "YES" : "NO") << std::endl;
    }
}
