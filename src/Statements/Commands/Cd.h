//
// Created by dram on 06.06.18.
//

#ifndef SHELL_INTERPRETER_CD_H
#define SHELL_INTERPRETER_CD_H

#include "../Statement.h"

namespace Commands {
    class Cd : public Statement {
    public:
        void execute() {};
    };
}
#endif //SHELL_INTERPRETER_CD_H
