#ifndef SHELL_INTERPRETER_TERMINAL_H
#define SHELL_INTERPRETER_TERMINAL_H

#include <string>
#include <iostream>
#include <unistd.h>
#include <vector>

#include "Environment.h"
#include "Exceptions.h"
#include "Parser/Parser.h"

using namespace Environment;
class Terminal{
public:
    void start(){

        while(true){
            try{
                std::string host;
                std::string user;
                std::string dir;
                try {
                    host = getHost();
                } catch(UnknownHostException &e) {
                    host = "UnknownHost";
                }
                try {
                    user = getUser();
                } catch(UnknownUserException &e){
                    user = "UnknownUser";
                }
                try {
                    dir = getDir();
                } catch(UnknownPathException &e){
                    dir = "UnknownPath";
                }
                std::cout << "[" << getDate() << "]" << user << "@" << host << ":" << dir << ">";
                std::getline(std::cin,terminalInput);
                auto command =  parser.parseLine(terminalInput);
                command->execute();
            }
            catch (ExitException & e)
            {
                break;
            }
            catch (Exception & e){
                    std::cout << e.what() << std::endl;
            }
        }
    }

    static Terminal& create(){
        static Terminal terminal;
        return terminal;
    }

    Terminal(const Terminal& ) = delete;
    Terminal& operator=(Terminal&) = delete;

private:
    Terminal() {
        chdir(getpwuid(getuid())->pw_dir);
        system("clear");
    }

    Parser parser;

    std::string terminalInput;
};
#endif //SHELL_INTERPRETER_TERMINAL_H
