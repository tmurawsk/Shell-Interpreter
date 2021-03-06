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
//            if(fork() == 0) {
                if (!arguments.empty())
                    throw InvalidNumberOfParametersException();

                if(outFile == "")
                    std::cout << get_current_dir_name() << std::endl;
                else
                    writeToPipe(get_current_dir_name());

//                exit(0);
//            }
//            else{
//                wait(NULL);
//            }
        }
    };
}
#endif //SHELL_INTERPRETER_PWD_H
