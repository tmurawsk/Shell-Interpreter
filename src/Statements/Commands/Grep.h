#ifndef SHELL_INTERPRETER_GREP_H
#define SHELL_INTERPRETER_GREP_H

#include "../Statement.h"
#include <cstdio>
#include <cstdlib>

namespace Commands {
    class Grep : public Statement {
    public:
        void execute() override {
            std::string argument = "grep";
            for (auto &I : arguments) {
                argument += " ";
                argument += I;
            }
            FILE *cmd;
            char result[1024];
            cmd = popen(argument.c_str(), "r");
            if (cmd == nullptr) {
                perror("popen");
                exit(EXIT_FAILURE);
            }
            while (fgets(result, sizeof(result), cmd)) {
                printf("%s", result);
            }
            pclose(cmd);
        }
    };
};

#endif //SHELL_INTERPRETER_GREP_H
