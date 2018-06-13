//
// Created by dram on 06.06.18.
//

#ifndef SHELL_INTERPRETER_MKFIFO_H
#define SHELL_INTERPRETER_MKFIFO_H

#include "../Statement.h"

namespace Commands {
    class Mkfifo: public Statement {
    public:
        void execute() override{
            if (arguments.empty() || arguments.size() > 1)
                throw InvalidNumberOfParametersException();

            mkfifo(arguments[0].c_str(), 0644);
        };
    };
}
#endif //SHELL_INTERPRETER_MKFIFO_H
