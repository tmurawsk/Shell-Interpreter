//
// Created by dram on 06.06.18.
//

#ifndef SHELL_INTERPRETER_PWD_H
#define SHELL_INTERPRETER_PWD_H

#include "../Statement.h"
#include "../../Exceptions.h"
#include <iostream>
#include <unistd.h>

namespace Commands {
    class Pwd : public Statement {
    public:
        void execute() override {
            if (!arguments.empty())
                throw InvalidNumberOfParametersException();

            std::cout << get_current_dir_name() << std::endl;
        };
    };
}
#endif //SHELL_INTERPRETER_PWD_H
