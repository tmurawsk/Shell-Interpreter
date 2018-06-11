//
// Created by jacek on 11.06.18.
//

#include "Environment.h"
#include "Parser/Parser.h"

bool Environment::add(std::string name, std::string value) {
    if(embeddedVariables.find(name) != embeddedVariables.end() && usersVariable.find(name) != usersVariable.end())
        return false;
    auto toInsert = std::pair<std::string,std::string>(name,value);
    usersVariable.insert(toInsert);
    return true;
}

std::string Environment::find(std::string name) {
    auto result = embeddedVariables.find(name);

    if(result != embeddedVariables.end())
        return result->second;

    result = usersVariable.find(name);

    if( result != usersVariable.end())
        return result->second;

    throw UnknownVariableException(name);
}

bool Environment::remove(std::string name) {
    auto result = embeddedVariables.find(name);
    if( result == embeddedVariables.end()) {
        result = usersVariable.find(name);
        if (result == usersVariable.end())
            return false;
        usersVariable.erase(result);
        return true;
    }
}

std::string Environment::getVariable(std:: string arg){
    if(arg.begin() != arg.end()){
        if(*arg.begin() == Parser::nonChangeValue)
            arg.erase(arg.begin());

        else if(*arg.begin() == '$'){
            arg.erase(arg.begin());
            arg = find(arg);
        }
    }
    return arg;
}
