#ifndef SHELL_INTERPRETER_ENVIRONMENT_H
#define SHELL_INTERPRETER_ENVIRONMENT_H

#include <string>
#include <unistd.h>
#include <pwd.h>

#include "Exceptions.h"

namespace Environment {

    const static unsigned int maxPathSize = 256;
    const static unsigned int maxNameSize = 64;
    const static unsigned int maxTimeSize = 16;

    const static unsigned int maxCommandSize = 256;
    const static unsigned int maxArgumants = 64;

    static std::string getUser() {
        char * userName = getlogin();
        if(userName != nullptr)
            return std::string(userName);

        struct passwd * user;
        user = getpwuid(getuid());

        if(user->pw_name != nullptr)
            return std::string(user->pw_name);

        throw UnknownUserException();
    }

    static std::string getHost(){
        char hostName[maxNameSize];
        if(gethostname(hostName,maxNameSize)==0){
            hostName[maxNameSize] = 0;
            return std::string(hostName);
        }
        throw UnknownHostException();
    }

    static std::string getDir() {
        char path[maxPathSize];
        if (getcwd(path, maxPathSize - 1) != nullptr) {
            path[maxPathSize - 1] = 0;
            return std::string(path);
        }
        throw UnknownPathException();
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
