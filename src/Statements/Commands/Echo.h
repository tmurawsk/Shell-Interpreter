#ifndef SHELL_INTERPRETER_ECHO_H
#define SHELL_INTERPRETER_ECHO_H

#include "../Statement.h"

namespace Commands {
    class Echo : public Statement {
    public:
        void execute() override {
            for (auto &I : arguments) {
                std::cout << I << " ";
            }
            std::cout << "\n";
        };
    };
}
#endif //SHELL_INTERPRETER_ECHO_H
