//
// Created by jacek on 11.06.18.
//

#ifndef SHELL_INTERPRETER_ENVIROMENT_H
#define SHELL_INTERPRETER_ENVIROMENT_H

#include <map>
#include <string>
#include "Exceptions.h"
#include <cstdlib>

namespace Environment {
    bool addOrSet(std::string, std::string);
    std::string find(std::string);
    bool remove(std::string);
};


#endif //SHELL_INTERPRETER_ENVIROMENT_H
