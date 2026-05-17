#include <iostream>
#include <string>

int main() {
    while (true) {
        std::string command;
        int n = 0;
        int m = 0;

        std::cin >> command;
        if (command == "exit") {
            break;
        } else if (command == "sum" || command ==  "sub" || command == "mul" || command == "div") {
            std::cin >> n >> m;
            if (command == "sum") {
                std::cout << n + m << "\n";
            } else if (command == "sub") {
                std::cout << n - m << "\n";
            } else if (command == "mul") {
                std::cout << n * m << "\n";
            } else if (command == "div") {
                std::cout << n / m << "\n";
            }
        } else {
            std::cout << "Sorry, could not understand your command\n";
        }
    }
    return 0;
}