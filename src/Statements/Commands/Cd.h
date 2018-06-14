#ifndef SHELL_INTERPRETER_CD_H
#define SHELL_INTERPRETER_CD_H

#include <pwd.h>
#include <unistd.h>
#include "../Statement.h"
#include "../../Exceptions.h"
#include "../../System.h"

namespace Commands {
    class Cd : public Statement {
        void myImplement(){
            if(inFile != "")
//                arguments.emplace_back(readFromPipe());
                arguments.emplace_back(readFromPipe());
            if (arguments.empty()) {
                if (chdir(getpwuid(getuid())->pw_dir) < 0)
                    throw NoSuchPathException();
            } else if (arguments.size() > 1) {
                throw InvalidNumberOfParametersException();
            } else if (chdir(arguments[0].c_str()) < 0) {
                throw NoSuchPathException();
            }
        }
    public:
        void execute() override {
            myImplement();
        }
    };
}
#endif //SHELL_INTERPRETER_CD_H
