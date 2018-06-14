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
        int fd = open(inFile.c_str(), O_RDONLY);
        if (fd < 0)
            throw BadFileDescriptorException();

        char array[INT_MAX];
        read(fd, array, sizeof(array));

        close(fd);

        return std::string(array);
    }

    void writeToPipe(std::string buffer) {
        int fd = open(outFile.c_str(), O_WRONLY);
        if (fd < 0)
            throw BadFileDescriptorException();

        write(fd, buffer.c_str(), strlen(std::string(buffer).c_str()) + 1);

        close(fd);
    }

public:

    Statement() = default;

    virtual ~Statement() = default;

    virtual void execute() {};

    void addArgument(const std::string &arg) {
        arguments.push_back(arg);
    }

    void setInFile(std::string &file) { inFile = file; }

    void setOutFile(std::string &file) { outFile = file; }

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
