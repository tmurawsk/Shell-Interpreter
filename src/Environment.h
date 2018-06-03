#ifndef SHELL_INTERPRETER_ENVIRONMENT_H
#define SHELL_INTERPRETER_ENVIRONMENT_H

#include <string>
#include <unistd.h>
#include "Exceptions/PathReadException.h"

namespace Environment {

    const static unsigned int maxPathSize = 256;
    const static unsigned int maxNameSize = 64;
    const static unsigned int maxTimeSize = 16;


    static std::string getUser() {
        char * userName = getlogin();
        if(userName != nullptr)
            return std::string(userName);
        return "UnknownUser";

        /*char userName[maxUserSize];
        if(getlogin_r(userName,maxUserSize))
            return std::string(userName);
        return "UnknownUser";*/
    }

    static std::string getHost(){
        char hostName[maxNameSize];
        if(gethostname(hostName,maxNameSize)==0){
            hostName[maxNameSize] = 0;
            return std::string(hostName);
        }
        return std::string("UnknownHost");
    }

    static std::string getDir() {
        char path[maxPathSize];
        if (getcwd(path, maxPathSize - 1) != nullptr) {
            path[maxPathSize - 1] = 0;
            return std::string(path);
        }
        throw PathReadException();
    }

    static std::string getDate() {
        time_t currentTime = time(nullptr);
        struct tm tstr =*localtime(&currentTime);
        char buffor[maxTimeSize];
        strftime(buffor, maxTimeSize, "%X", &tstr);
        return std::string(buffor);
    }
}
#endif //SHELL_INTERPRETER_ENVIRONMENT_H
