//
// Created by dram on 06.06.18.
//

#ifndef SHELL_INTERPRETER_PWD_H
#define SHELL_INTERPRETER_PWD_H

#include "../Statement.h"

namespace Commands {
    class Pwd: public Statement {
    public:
        void execute() override{
            std::cout << "pwd: ";
            for(auto & I : arguments){
                std::cout << I << " ";
            }
            std::cout << "\n";
        };
    };
}
#endif //SHELL_INTERPRETER_PWD_H
