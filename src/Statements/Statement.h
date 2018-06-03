//
// Created by jacek on 03.06.18.
//

#ifndef SHELL_INTERPRETER_STATEMENT_H
#define SHELL_INTERPRETER_STATEMENT_H

#include <list>
#include <string>
class Statement{
protected:
    std::list<std::string> arguments;
public:
    Statement() = default;
    virtual ~Statement() = default;
    virtual void execute(){};
};
#endif //SHELL_INTERPRETER_STATEMENT_H
