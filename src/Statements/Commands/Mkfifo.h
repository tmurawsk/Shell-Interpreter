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
            std::cout << "mkfifo: ";
            for(auto & I : arguments){
                std::cout << I << " ";
            }
            std::cout << "\n";
        };
    };
}
#endif //SHELL_INTERPRETER_MKFIFO_H
