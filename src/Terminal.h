#ifndef SHELL_INTERPRETER_TERMINAL_H
#define SHELL_INTERPRETER_TERMINAL_H

#include <string>
#include <iostream>
#include <unistd.h>
#include <vector>

#include "System.h"
#include "Exceptions.h"
#include "Parser/Parser.h"

using namespace System;
class Terminal{
public:
    void start(){

        while(true){
            try{
                std::cout << "[" << getDate() << "]" << getUser() << "@" << getHost() << ":" << getDir() << ">";
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
