#include <cstdlib>

int sum_size(int* p, size_t size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += *(p + i);
    }
    return sum;
}

int sum_ptrs(int* begin, int* end) {
    int sum = 0;
    for (int* p = begin; p < end; p++) {
        sum += *p;
    }
    return sum;
}