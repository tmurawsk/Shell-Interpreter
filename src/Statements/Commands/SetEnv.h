//
// Created by jacek on 13.06.18.
//

#ifndef SHELL_INTERPRETER_SETENV_H
#define SHELL_INTERPRETER_SETENV_H

#include "../Statement.h"
#include "../../Exceptions.h"

namespace Commands {
    class SetEnv : public Statement {
    public:
        void execute() override {
            std::cout << "setValue: ";
            for(auto & I : arguments){
                std::cout << I << " ";
            }
            std::cout << "\n";
        };
    };
}

#endif //SHELL_INTERPRETER_SETENV_H
