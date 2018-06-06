#ifndef SHELL_INTERPRETER_TERMINAL_H
#define SHELL_INTERPRETER_TERMINAL_H

#include <string>
#include <iostream>
#include <unistd.h>
#include <vector>

#include "Environment.h"
#include "Exceptions/ExitException.h"
#include "Parser/Parser.h"

using namespace Environment;
class Terminal{
public:
    void start(){
        Parser parser;
        while(!parser.wasExit()){
            try{
                std::cout << "[" << getDate() << "]" << getUser() << "@" << getHost() << ":" << getDir() << ">";
                std::getline(std::cin,terminalInput);
                std::vector<Token> tokens = parser.parseLine(terminalInput);
                parser.parseAndExecuteTokens(tokens);

            }
            catch (ExitException& e){
                std::cout << e.what() << "\n";
                std::cin.get();
                system("clear");
                break;
            }
            catch (std::exception& e){
                std::cout << e.what();
            }
        }
        //exit typed
        std::cin.get();
        system("clear");
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

    std::string terminalInput;
};
#endif //SHELL_INTERPRETER_TERMINAL_H
