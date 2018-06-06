//
// Created by dram on 06.06.18.
//

#ifndef SHELL_INTERPRETER_EXP_H
#define SHELL_INTERPRETER_EXP_H

#include "../Statement.h"

namespace Commands {
    class Exp: public Statement {
    public:
        void execute() {};
    };
}
#endif //SHELL_INTERPRETER_EXP_H
