#ifndef SHELL_INTERPRETER_TERMINAL_H
#define SHELL_INTERPRETER_TERMINAL_H

#include <string>
#include <iostream>
#include <unistd.h>
#include <vector>

#include "System.h"
#include "Exceptions.h"
#include "Parser/Parser.h"
#include "Statements/Redirector.h"

using namespace System;
class Terminal{
public:
    static int keepRunning;
    static void sigIntHandler(int value){
        std::cout << "SigInt signal! Bye Bye :)" << std::endl;
        keepRunning = 0;
        exit(0);
    }
    static void sigQuitHandler(int val){
        std::cout << "Quit signal! Bye Bye :)" << std::endl;
        keepRunning = 0;
        exit(0);
    }
    void start(){
        signal(SIGINT, Terminal::sigIntHandler); //ctrl + c
        signal(SIGQUIT, Terminal::sigQuitHandler); // ctrl + /

        while(keepRunning){
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
                std::cout << "[" << getDate() << "]" << getUser() << "@" << getHost() << ":" << getDir() << ">";
                std::getline(std::cin,terminalInput);
                auto command =  parser.parseLine(terminalInput);
//                command->execute();
                    command.execute();
            }
            catch (ExitException & e){
                break;
            }
            catch (Exception & e){
                std::cout << e.What() << std::endl;
            }
            catch  (std::exception & e){
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
    Terminal() : parser(){
        chdir(getpwuid(getuid())->pw_dir);
        system("clear");
    }

    Parser parser;

    std::string terminalInput;
};
int Terminal::keepRunning = 1; //init
#endif //SHELL_INTERPRETER_TERMINAL_H
