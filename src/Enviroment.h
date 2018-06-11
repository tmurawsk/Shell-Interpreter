//
// Created by jacek on 11.06.18.
//

#ifndef SHELL_INTERPRETER_ENVIROMENT_H
#define SHELL_INTERPRETER_ENVIROMENT_H

#include <map>
#include <string>
#include "Exceptions.h"

class Enviroment {
public:
    explicit Enviroment();
    bool add(std::string, std::string);
    std::string find(std::string);
    bool remove(std::string);

private:
    std::map<std::string, std::string> embeddedVariables;
    std::map<std::string, std::string> usersVariable;
};


#endif //SHELL_INTERPRETER_ENVIROMENT_H
