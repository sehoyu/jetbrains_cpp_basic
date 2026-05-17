#include <iostream>
#include <set>
#include <string>
#include <cctype>

std::set<std::string> splitIntoWords(const std::string& str) {
    Your implementation here
}

int main() {
    std::string str = "Hello, world! This is a test. Test again, hello.";
    std::set<std::string> words = splitIntoWords(str);
    for (const std::string& word : words) {
        std::cout << word << std::endl;
    }
    return 0;
}