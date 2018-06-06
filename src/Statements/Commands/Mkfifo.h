//
// Created by dram on 06.06.18.
//

#ifndef SHELL_INTERPRETER_MKFIFO_H
#define SHELL_INTERPRETER_MKFIFO_H

#include "../Statement.h"

namespace Commands {
    class Mkfifo: public Statement {
    public:
        void execute() {};
    };
}
#endif //SHELL_INTERPRETER_MKFIFO_H
