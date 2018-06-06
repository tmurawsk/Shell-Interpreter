//
// Created by dram on 06.06.18.
//

#ifndef SHELL_INTERPRETER_ECHO_H
#define SHELL_INTERPRETER_ECHO_H

#include "../Statement.h"

namespace Commands {
    class Echo: public Statement {
    public:
        void execute() {
            std::cout << "ECHO command" << std::endl;
        };
    };
}
#endif //SHELL_INTERPRETER_ECHO_H
