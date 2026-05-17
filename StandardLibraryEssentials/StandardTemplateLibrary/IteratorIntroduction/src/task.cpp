#include <iostream>
#include <vector>
#include <string>

std::vector<int>::iterator findMaximum(std::vector<int>& container) {
    /* TODO */
}

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6};
    std::cout << *findMaximum(vec) << std::endl;

    std::vector<int> empty_vec;
    std::cout << *findMaximum(empty_vec) << std::endl;

    return 0;
}