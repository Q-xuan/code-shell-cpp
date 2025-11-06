#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>

// 去掉前导空格
void ltrim(std::string &s) {
    s.erase(s.begin(), std::ranges::find_if(s,
                                            [](const unsigned char ch) { return !std::isspace(ch); }));
}

int echoMethod(const std::string &arg) {
    std::string output = arg;
    ltrim(output);
    std::cout << output << std::endl;
    return 0;
}

int exitMethod(const std::string &arg) {
    int code = 0;
    if (!arg.empty()) {
        code = std::stoi(arg);
    }
    return code;
}

int typeMethod(const std::string &arg,
               const std::map<std::string, std::function<int(const std::string &)> >& commands) {
    if (const auto it = commands.find(arg); it == commands.end()) {
        std::cout << arg << ": not found" << std::endl;
        return -1;
    }
    std::cout << arg << " is a shell builtin" << std::endl;
    return 0;
}

int main() {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    // 命令映射表
    std::map<std::string, std::function<int(const std::string &)> > commands;
    commands["exit"] = [](const std::string &arg) { return exitMethod(arg); };
    commands["echo"] = [](const std::string &arg) { return echoMethod(arg); };
    commands["type"] = [&commands](const std::string &arg) {
        return typeMethod(arg, commands);
    };

    std::string line;
    std::cout << "$ "; // 初始提示符

    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            std::cout << "$ ";
            continue;
        }
        std::istringstream iss(line);
        std::string cmd;
        std::string arg;

        //解析出第一个和第二个单词
        iss >> cmd;

        std::getline(iss, arg);
        ltrim(arg);

        if (auto it = commands.find(cmd); it != commands.end()) {
            const int code = it->second(arg);
            if (cmd == "exit") {
                return code;
            }
        } else {
            std::cout << cmd << ": command not found" << std::endl;
        }


        std::cout << "$ ";
    }

    std::cout << std::endl;
    return 0;
}
