#include <iostream>
#include <string>

int main() {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    std::string command;
    std::cout << "$ ";  // 初始提示符

    while (std::getline(std::cin, command)) {
        if (command == "exit") {
            return 0;
        }

        std::cout << command << ": command not found" << std::endl;
        std::cout << "$ ";
    }

    std::cout << std::endl;
    return 0;
}
