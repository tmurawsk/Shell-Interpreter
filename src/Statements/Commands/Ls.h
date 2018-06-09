//
// Created by dram on 06.06.18.
//

#ifndef SHELL_INTERPRETER_LS_H
#define SHELL_INTERPRETER_LS_H

#include "../Statement.h"

namespace Commands {
    class Ls: public Statement {
    public:
        void execute() override{
            std::cout << "ls: ";
            for(auto & I : arguments){
                std::cout << I << " ";
            }
            std::cout << "\n";
        };
    };
}
#endif //SHELL_INTERPRETER_LS_H
