#ifndef SHELL_INTERPRETER_STATEMENT_H
#define SHELL_INTERPRETER_STATEMENT_H

#include <vector>
#include <string>
#include <iostream>
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
};

#endif //SHELL_INTERPRETER_STATEMENT_H
