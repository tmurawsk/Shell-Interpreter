#include "Environment.h"
#include "Parser/Parser.h"

bool Environment::addOrSet(std::string name, std::string value) {
    return 0==setenv(name.c_str(),value.c_str(),1);
}

std::string Environment::find(std::string name) {
    char * result = getenv(name.c_str());
    if(result)
        return std::string(result);
    else
        return "";
}

bool Environment::remove(std::string name) {
    return 0==unsetenv(name.c_str());
}
