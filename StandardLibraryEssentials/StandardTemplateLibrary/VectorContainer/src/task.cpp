#include <iostream>
#include <vector>

std::vector<int> create(std::size_t capacity) {
    std::vector<int> v;
    v.reserve(capacity);
    return v;
}

std::vector<int> fill(std::vector<int>& vec, std::size_t size, int value) {
    vec.clear();
    for (size_t i = 0; i < size; i++) {
        vec.push_back(value);
        // vec[i] = value;
    }
    return vec;
}

void debugPrint(const std::vector<int>& vec) {
    size_t s = vec.size();
    size_t c = vec.capacity();
    std::cout << "Size: " << s << ", Capacity: " << c << std::endl;

    std::cout << "Vector: ";
    for (int num: vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> vec = create(10);
    debugPrint(vec);
    vec = fill(vec, 10, 1);
    debugPrint(vec);
    vec.clear();
    debugPrint(vec);
    return 0;
}