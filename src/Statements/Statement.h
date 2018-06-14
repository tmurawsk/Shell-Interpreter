#ifndef SHELL_INTERPRETER_STATEMENT_H
#define SHELL_INTERPRETER_STATEMENT_H

#include <vector>
#include <string>
#include <iostream>
#include <cstring>
#include "../Exceptions.h"
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <climits>

class Statement {
protected:
    std::vector<std::string> arguments;
    std::string inFile;
    std::string outFile;

    std::string readFromPipe() {
//    std::cout<<"read"<<std::endl;
        int fd = open(inFile.c_str(), O_RDONLY);
        if (fd < 0)
            throw BadFileDescriptorException();

        char *array = new char[1024];
        ssize_t r = read(fd, array, 1024);
//        std::cout<<"get: "<<(int)r<<std::endl;
        close(fd);
        auto result = std::string(array);
        delete[]array;
        result.erase(--result.end());
        result.erase(--result.end());
//        std::cout<<"end read"<<std::endl;
        return result;
    };

    void writeToPipe(std::string buffer) {
//        std::cout<<"buf: "<<buffer<<" size: "<<buffer.size()<<std::endl;
//        std::cout<<"write"<<std::endl;
        int fd = open(outFile.c_str(), O_WRONLY);
        if (fd < 0)
            throw BadFileDescriptorException();
        write(fd, buffer.c_str(), buffer.size());
//        std::cout<<"end write"<<std::endl;
        close(fd);
    }

public:

    explicit Statement() = default;

    virtual ~Statement() = default;

    virtual void execute() {};

    void addArgument(const std::string &arg) {
        arguments.push_back(arg);
    }

    void setInFile(const std::string &file) { inFile = file; }

    void setOutFile(const std::string &file) { outFile = file; }

    static bool isStringMatchPatern(const std::string &str, const std::string &pattern) {
        //empty patern match to empty string
        if (str.empty())
            return pattern.empty();

        //using dynamic programing
        bool helpTable[str.size() + 1][pattern.size() + 1];
        memset(helpTable, false, sizeof(helpTable));

        helpTable[0][0] = true; //empty pattern, match to empty string

        // '*' match with empty string

        for (int j = 1; j <= pattern.size(); j++) {
            if (pattern[j - 1] == '*') {
                helpTable[0][j] = helpTable[0][j - 1];
            }
        }

        //fill table with bottom-up
        for (int i = 1; i <= str.size(); i++) {
            for (int j = 1; j <= pattern.size(); j++) {
                // we see *
                // ignore *, and move to next char
                // * matches in character in input
                if (pattern[j - 1] == '*')
                    helpTable[i][j] = helpTable[i][j - 1] || helpTable[i - 1][j];
                else if (pattern[j - 1] == '?' || str[i - 1] == pattern[j - 1]) { // characters match, or '?'
                    helpTable[i][j] = helpTable[i - 1][j - 1];
                } else // characters dont match
                    helpTable[i][j] = false;
            }
        }
        return helpTable[str.size()][pattern.size()];

    }
};

#endif //SHELL_INTERPRETER_STATEMENT_H
