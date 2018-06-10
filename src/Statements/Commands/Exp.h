//
// Created by dram on 06.06.18.
//

#ifndef SHELL_INTERPRETER_EXP_H
#define SHELL_INTERPRETER_EXP_H

#include "../Statement.h"

namespace Commands {
    class Exp: public Statement {
    public:
        void execute() override{
            std::cout << "export: ";
            for(auto & I : arguments){
                std::cout << I << " ";
            }
            std::cout << "\n";
        };
    };
}
#endif //SHELL_INTERPRETER_EXP_H
