//
// Created by jacek on 11.06.18.
//

#include "Enviroment.h"

Enviroment::Enviroment() {
    /*Variables = {
            std::make_pair<std::string, std::string>(),

            std::make_pair<std::string, std::string>(),

            std::make_pair<std::string, std::string>(),

            std::make_pair<std::string, std::string>(),
    }*/
}

bool Enviroment::add(std::string name, std::string value) {
    if(usersVariable.find(name) != usersVariable.end())
        return false;
    auto toInstert = std::pair<std::string,std::string>(name,value);
    usersVariable.insert(toInstert);
    return true;
}

std::string Enviroment::find(std::string name) {
    auto result = usersVariable.find(name);
    if( result == usersVariable.end())
        throw UnknownVariableException(name);
    return result->second;
}

bool Enviroment::remove(std::string name) {
    auto result = usersVariable.find(name);
    if( result == usersVariable.end())
        return false;
    usersVariable.erase(result);
}
