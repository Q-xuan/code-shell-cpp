#include <iostream>
#include <string>
#include <sstream>

int exitMethod(const std::string &arg) {
    int code = 0;
    if (!arg.empty()) {
        code = std::stoi(arg);
    }
    return code;
}

void echoMethod(std::string arg) {
    if (!arg.empty() && arg[0] == ' ')
        arg.erase(0, 1);
    std::cout << arg << std::endl;
}

int main() {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    std::string line;
    std::cout << "$ "; // 初始提示符

    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        std::string cmd;
        std::string arg;

        //解析出第一个和第二个单词
        iss >> cmd;

        if (cmd == "exit") {
            iss >> arg;
            return exitMethod(arg);
        }

        if (cmd == "echo") {
            std::getline(iss, arg);
            echoMethod(arg);
        }

        std::cout << cmd << ": command not found" << std::endl;
        std::cout << "$ ";
    }

    std::cout << std::endl;
    return 0;
}
