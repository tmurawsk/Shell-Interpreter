#ifndef SHELL_INTERPRETER_EXEC_H
#define SHELL_INTERPRETER_EXEC_H

#include "../Statement.h"

namespace Commands {
    class Exec : public Statement {
    public:
        void execute() override {
            if (fork() == 0) {
                char *args[arguments.size() + 1];
                std::string tmp = "./";
                tmp += arguments[0];
                args[0] = strdup(tmp.c_str());

                for (int i = 1; i < arguments.size(); ++i) {
                    args[i] = strdup(arguments[i].c_str());
                }

                args[arguments.size()] = NULL;
                execvp(args[0], args);
                exit(1);
            } else {
                wait(NULL);
            }
        }
    };
}

#endif //SHELL_INTERPRETER_EXEC_H
