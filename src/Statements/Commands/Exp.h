#ifndef SHELL_INTERPRETER_EXP_H
#define SHELL_INTERPRETER_EXP_H

#include "../Statement.h"
#include <unistd.h>

namespace Commands {
    class Exp: public Statement {
    public:
        void execute() override{
            if(fork() == 0) {
                std::cout << "export: ";        // TODO
                for(auto & I : arguments){
                    std::cout << I << " ";
                }
                std::cout << "\n";
                exit(1);
            }
            else{
                wait(NULL);
            }
        }
    };
}
#endif //SHELL_INTERPRETER_EXP_H
