//
// Created by dram on 06.06.18.
//

#ifndef SHELL_INTERPRETER_LS_H
#define SHELL_INTERPRETER_LS_H

#include "../Statement.h"
#include "../../Exceptions.h"
#include <iostream>
#include <dirent.h>
#include <sstream>

namespace Commands {
    class Ls: public Statement {
    public:
        void execute() override{

            if (arguments.size() > 1) {
                throw InvalidNumberOfParametersException();
            }

            DIR *dir;
            struct dirent *ent;
            std::stringstream files;
            int counter = 0;
            std::string path;

            path = arguments.empty() ? "." : arguments[0];

            if((dir = opendir(path.c_str())) != NULL) {
                while ((ent = readdir(dir)) != NULL) {
                    files << ent->d_name << "\n";
                    counter++;
                }
            }
            else
                throw NoSuchPathException();

            std::stringstream output;
            output << "total: " << counter << "\n" << files.str();

            std::cout << output.str();
        };
    };
}
#endif //SHELL_INTERPRETER_LS_H
