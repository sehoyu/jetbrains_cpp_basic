#include <iostream>
#include <list>
#include <deque>

std::list<int> sumAdjacentElements(const std::list<int>& nums) {
    if (nums.empty()) return nums;

    std::list<int> result;
    auto it = nums.begin();
    while (it != nums.end()) {
        int temp = *it++;
        if (it == nums.end()) {
            break;
        }
        result.push_back(temp + *it++);
    }

    return result;
}

std::deque<int> sumAdjacentElements(const std::deque<int>& nums) {
    if (nums.empty()) return nums;

    std::deque<int> result;
    auto it = nums.begin();
    while (it != nums.end()) {
        int temp = *it++;
        if (it == nums.end()) {
            break;
        }
        result.push_back(temp + *it++);
    }

    return result;
}

int main() {
    std::list<int> nums1 = {1, 2, 3, 4, 5, 6};
    std::list<int> result1 = sumAdjacentElements(nums1);
    for (auto it = result1.begin(); it != result1.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::deque<int> nums2 = {1, 2, 3, 4, 5, 6};
    std::deque<int> result2 = sumAdjacentElements(nums2);
    for (auto it = result2.begin(); it != result2.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}