//
// Created by dram on 06.06.18.
//

#ifndef SHELL_INTERPRETER_ECHO_H
#define SHELL_INTERPRETER_ECHO_H

#include "../Statement.h"

namespace Commands {
    class Echo: public Statement {
    public:
        void execute() override{
            std::cout << "echo: ";
            for(auto & I : arguments){
                std::cout << I << " ";
            }
            std::cout << "\n";
        };
    };
}
#endif //SHELL_INTERPRETER_ECHO_H
