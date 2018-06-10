//
// Created by jacek on 09.06.18.
//

#ifndef SHELL_INTERPRETER_EXCEPTIONS_H
#define SHELL_INTERPRETER_EXCEPTIONS_H

#include <exception>
#include <string>

class ExitException : public std::exception{
public:
    const char* what() const noexcept override {
        return "Terminal closed";
    }
};

class UnknownTokenException : public std::exception{
public:

    const char* what() const noexcept override {
        return "Unknown Token";
    }
};

class UnknownCommandException: public std::exception{
private:
    std::string command;
public:

    explicit UnknownCommandException(std::string & command_):command(command_){}
    const char* what() const noexcept override {
        return std::string("Unknown command: " + command).c_str();
        /*std::string msg = "Unknown command";
        std::cout<<msg<<std::endl;
        msg+="\0";
        std::cout<<msg<<std::endl;
        const char* msg_c =  msg.c_str();
        std::cout<<msg_c<<std::endl;
        return msg_c;*/
    }
};

/*
class : public std::exception{
public:

    const char* what() const noexcept override {
        return "";
    }
};
 */

#endif //SHELL_INTERPRETER_EXCEPTIONS_H
