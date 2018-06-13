#ifndef SHELL_INTERPRETER_EXIT_H
#define SHELL_INTERPRETER_EXIT_H

#include <unistd.h>
#include "../Statement.h"
#include "../../Exceptions.h"

namespace Commands {
    class Exit : public Statement {
    public:
        void execute() override{
            std::cout << "terminal closed" << std::endl;
            sleep(1);
            system("clear");
            throw ExitException();
        }
    };
}
#endif //SHELL_INTERPRETER_EXIT_H
