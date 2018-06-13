#ifndef SHELL_INTERPRETER_STATEMENT_H
#define SHELL_INTERPRETER_STATEMENT_H

#include <vector>
#include <string>
#include <iostream>
#include <cstring>
#include "../Exceptions.h"
#include <sys/wait.h>

class Statement {
protected:
    std::vector<std::string> arguments;
public:
    Statement() = default;

    virtual ~Statement() = default;

    virtual void execute() = 0; // pure virtual
    void addArgument(const std::string &arg) {
        arguments.push_back(arg);
    }

    static bool isStringMatchPatern(const std::string &str, const std::string &pattern){
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
                else if (pattern[j-1] == '?' || str[i - 1] == pattern[j - 1]) { // characters match, or '?'
                    helpTable[i][j] = helpTable[i - 1][j - 1];
                } else // characters dont match
                    helpTable[i][j] = false;
            }
        }
        return helpTable[str.size()][pattern.size()];

    }
};

#endif //SHELL_INTERPRETER_STATEMENT_H
