#include <iostream>
#include <map>
#include <string>
#include <cctype>

std::map<char, int> countLetters(const std::string& str) {
    Your implementation here
}

int main() {
    std::string str = "The distribution of letters in any text is uneven. Letter frequency is the number of times letters of the alphabet appear on average in written language. The data may vary from source to source, but almost everywhere it is indicated that the letter ‘e’ is the most common in the English text. The rarest letter is ‘z’";
    std::cout << str << '\n';
    std::map<char, int> letter_counts = countLetters(str);
    for (const auto& pair : letter_counts) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    return 0;
}