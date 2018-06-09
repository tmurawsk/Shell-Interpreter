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
                    throw NoSuchPathException();
            } else if (arguments.size() > 1) {
                throw NoSuchPathException();
            } else if (chdir(arguments[0].c_str()) < 0) {
                throw NoSuchPathException();
            }
        };
    };
}
#endif //SHELL_INTERPRETER_CD_H
