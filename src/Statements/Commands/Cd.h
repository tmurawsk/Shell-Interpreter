//
// Created by dram on 06.06.18.
//

#ifndef SHELL_INTERPRETER_CD_H
#define SHELL_INTERPRETER_CD_H

#include <pwd.h>
#include <unistd.h>
#include "../Statement.h"

namespace Commands {
    class Cd : public Statement {
    public:
        void execute() override {
            if (arguments.empty()) {
                if (chdir(getpwuid(getuid())->pw_dir) < 0)
                    throw std::runtime_error("No such path: " +
                                             std::string(getpwuid(getuid())->pw_dir) +
                                             "\n"
                    );
            } else if (arguments.size() > 1) {
                throw std::runtime_error("Invalid arguments to command: cd\n");
            } else if (chdir(arguments[0].c_str()) < 0) {
                throw std::runtime_error("No such path: " +
                                         arguments[0] +
                                         "\n"
                );
            }
        };
    };
}
#endif //SHELL_INTERPRETER_CD_H
