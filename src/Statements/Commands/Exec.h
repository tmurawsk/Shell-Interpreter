#ifndef SHELL_INTERPRETER_EXEC_H
#define SHELL_INTERPRETER_EXEC_H

#include "../Statement.h"

namespace Commands {
    class Exec: public Statement {
    public:
        void execute() override{
            if(fork() == 0) {
                std::cout << "exec: ";          // TODO
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

#endif //SHELL_INTERPRETER_EXEC_H
