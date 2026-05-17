#include <string>
#include <string_view>
#include <cctype>
#include <iostream>

std::string lowerCase(std::string_view str) {
    /* TODO */
}

bool isPalindrome(std::string_view word) {
    /* TODO */
}

int main() {
    std::cout << "is palindrome?\n";
    std::cout << "Hello: " << (isPalindrome("Hello") ? "true" : "false") << '\n';
    std::cout << "Madam: " << (isPalindrome("Madam") ? "true" : "false") << '\n';
    std::cout << "A man a plan a canal Panama: " << (isPalindrome("A man a plan a canal Panama") ? "true" : "false") << '\n';
    return 0;
}