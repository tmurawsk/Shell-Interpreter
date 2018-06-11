//
// Created by jacek on 11.06.18.
//

#ifndef SHELL_INTERPRETER_ENVIROMENT_H
#define SHELL_INTERPRETER_ENVIROMENT_H

#include <map>
#include <string>
#include "Exceptions.h"

namespace Environment {
    bool add(std::string, std::string);
    std::string find(std::string);
    bool remove(std::string);
    std::string getVariable(std:: string);

    std::map<std::string, std::string> embeddedVariables = {};
    std::map<std::string, std::string> usersVariable = {};


};


#endif //SHELL_INTERPRETER_ENVIROMENT_H
