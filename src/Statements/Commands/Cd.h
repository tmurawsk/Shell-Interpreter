//
// Created by dram on 06.06.18.
//

#ifndef SHELL_INTERPRETER_CD_H
#define SHELL_INTERPRETER_CD_H

#include "../Statement.h"

namespace Commands {
    class Cd : public Statement {
    public:
        void execute() override {
            std::cout << "cd: ";
            for(auto & I : arguments){
                std::cout << I << " ";
            }
            std::cout << "\n";
        };
    };
}
#endif //SHELL_INTERPRETER_CD_H
