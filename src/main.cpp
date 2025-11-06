#include <iostream>
#include <string>
#include <sstream>

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
        iss >> cmd >> arg;

        if (cmd == "exit") {
            int code = 0;
            if (!arg.empty()) {
                code = std::stoi(arg);
            }
            return code;
        }

        std::cout << cmd << ": command not found" << std::endl;
        std::cout << "$ ";
    }

    std::cout << std::endl;
    return 0;
}
