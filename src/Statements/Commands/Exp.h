#ifndef SHELL_INTERPRETER_EXP_H
#define SHELL_INTERPRETER_EXP_H

#include "../Statement.h"
#include "../../Environment.h"
#include <unistd.h>

namespace Commands {
    class Exp : public Statement {
    public:
        void execute() override {
            if (arguments.size() != 3)
                throw InvalidNumberOfParametersException();
            if (arguments[1] != "=")
                throw InvalidArgumentsException();
            Environment::addOrSet(arguments[0], arguments[2]);
            exit(0);
        }
    };
}
#endif //SHELL_INTERPRETER_EXP_H
