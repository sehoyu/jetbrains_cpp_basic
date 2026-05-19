#include <string>
#include <string_view>
#include <cctype>
#include <iostream>

std::string lowerCase(std::string_view str) {
    std::string result;
    for (auto c : str) {
        if (std::isalnum(c)) {
            result += std::tolower(c);
        }
    }

    return result;
}

bool isPalindrome(std::string_view word) {
    std::string result = lowerCase(word);

    // if (result[0] != result[result.size() - 1]) return false;
    if (result.empty()) return true;

    size_t left = 0;
    size_t right = result.size() - 1;
    while (left < right) {
        if (result[left] != result[right]) return false;
        left++;
        right--;
    }

    return true;
}

int main() {
    std::cout << "is palindrome?\n";
    std::cout << "Hello: " << (isPalindrome("Hello") ? "true" : "false") << '\n';
    std::cout << "Madam: " << (isPalindrome("Madam") ? "true" : "false") << '\n';
    std::cout << "A man a plan a canal Panama: " << (isPalindrome("A man a plan a canal Panama") ? "true" : "false") << '\n';
    return 0;
}