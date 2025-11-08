#include <filesystem>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>

//查询文件是否存在并且是否是可执行的
bool isExecutable(const std::string &path) {
    const std::filesystem::path filePath(path);
    return std::filesystem::exists(filePath) && std::filesystem::is_regular_file(filePath) && (std::filesystem::status(filePath).permissions() & std::filesystem::perms::owner_exec) != std::filesystem::perms::none;
}

// 查找命令
void findCommandPath(const std::string& command) {
    if (const char* path = std::getenv("PATH")) {
        const std::string path_str = path;
        std::stringstream ss(path_str);
        std::string token;

        // 遍历 PATH 中的每个目录
        while (std::getline(ss, token, ':')) {
            std::string command_path = token + "/" + command;
            if (isExecutable(command_path)) {
                std::cout << command << " is " << command_path << std::endl;
                return;  // 找到命令后返回
            }
        }
    }
    std::cout << command << ": not found" << std::endl;
}

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
               const std::map<std::string, std::function<int(const std::string &)>> &commands) {
    if (const auto it = commands.find(arg); it != commands.end()) {
        std::cout << arg << " is a shell builtin" << std::endl;
        return 0;
    }

    // 如果不是内建命令，则调用路径查找函数
    findCommandPath(arg);
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
