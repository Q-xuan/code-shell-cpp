#include <iostream>
#include <string>

int main() {
    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    // TODO: Uncomment the code below to pass the first stage
    std::cout << "$ ";

    std::string command;
    //读取内容
    std::getline(std::cin, command);

    if (command != "echo" || command != "cd") {
        std::cout << command << ": command not found" << std::endl;
        return 1;
    }
}
