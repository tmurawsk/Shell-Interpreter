#ifndef SHELL_INTERPRETER_SETENV_H
#define SHELL_INTERPRETER_SETENV_H

#include "../Statement.h"
#include "../../Environment.h"
#include "../../Exceptions.h"

namespace Commands {
    class SetEnv : public Statement {
    public:
        void execute() override {
            if(fork() == 0) {
                if(arguments.size()!=3){
                    if(arguments.size()>=2 && arguments[1] != "=")
                        throw UnknownCommandException(arguments[0]);
                    else if(arguments.size()>=2)
                        throw InvalidNumberOfParametersException();
                    else
                        throw UnknownCommandException(arguments[0]);
                }
                if(arguments[1] != "=")
                    throw InvalidArgumentsException();
                Environment::addOrSet(arguments[0],arguments[2]);
            }
            else{
                wait(NULL);
            }
        };
    };
}

#endif //SHELL_INTERPRETER_SETENV_H
