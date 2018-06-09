//
// Created by jacek on 09.06.18.
//

#ifndef SHELL_INTERPRETER_EXEC_H
#define SHELL_INTERPRETER_EXEC_H

#include "../Statement.h"

namespace Commands {
    class Exec: public Statement {
    public:
        void execute() override{
            std::cout << "exec: ";
            for(auto & I : arguments){
                std::cout << I << " ";
            }
            std::cout << "\n";
        };
    };
}

#endif //SHELL_INTERPRETER_EXEC_H
