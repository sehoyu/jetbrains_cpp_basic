#include <cstdlib>

int* copy(int* p, size_t size) {
    if (size == 0 || p == nullptr) {
        return nullptr;
    }

    int* c = (int*) malloc(size * sizeof(int));

    if (c == nullptr) {
        return nullptr;
    }

    for (size_t i = 0; i < size; i++) {
        c[i] = p[i];
    }

    return c;
}