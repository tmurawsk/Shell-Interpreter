#ifndef SHELL_INTERPRETER_ECHO_H
#define SHELL_INTERPRETER_ECHO_H

#include "../Statement.h"

namespace Commands {
    class Echo : public Statement {
    public:
        void execute() override {
            if(fork() == 0) {
                for (auto &I : arguments) {
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
#endif //SHELL_INTERPRETER_ECHO_H
