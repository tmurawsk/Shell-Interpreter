//
// Created by jacek on 11.06.18.
//

#include "Environment.h"
#include "Parser/Parser.h"

bool Environment::addOrSet(std::string name, std::string value) {
    setenv(name.c_str(),value.c_str(),0);
    /*if(embeddedVariables.find(name) != embeddedVariables.end() && usersVariable.find(name) != usersVariable.end())
        return false;
    auto toInsert = std::pair<std::string,std::string>(name,value);
    usersVariable.insert(toInsert);
    return true;*/
}

std::string Environment::find(std::string name) {
    char * result = getenv(name.c_str());
    if(result)
        return std::string(result);
    else
        throw UnknownVariableException(name);
    /*auto result = embeddedVariables.find(name);

    if(result != embeddedVariables.end())
        return result->second;

    result = usersVariable.find(name);

    if( result != usersVariable.end())
        return result->second;

    throw UnknownVariableException(name);*/
}

bool Environment::remove(std::string name) {
    unsetenv(name.c_str());
    /*auto result = embeddedVariables.find(name);
    if( result == embeddedVariables.end()) {
        result = usersVariable.find(name);
        if (result == usersVariable.end())
            return false;
        usersVariable.erase(result);
        return true;
    }*/
}
