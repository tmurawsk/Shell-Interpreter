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

            if (inFile != "") {
                arguments.emplace_back(readFromPipe());
            }

            FILE *cmd;
            char result[1024];
            std::string res;
            cmd = popen(argument.c_str(), "r");

            if (cmd == nullptr) {
                perror("popen");
                exit(EXIT_FAILURE);
            }

            while (fgets(result, sizeof(result), cmd)) {
                res += std::string(result);
            }

            if (outFile != "")
                writeToPipe(res);
            else
                std::cout << res;

            pclose(cmd);
            exit(0);

        }
    };
};

#endif //SHELL_INTERPRETER_GREP_H
