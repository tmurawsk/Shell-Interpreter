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

class UnknownCommand: public std::exception{
private:
    std::string command;
public:
    
    explicit UnknownCommand(std::string & command_):command(command_){}
    const char* what() const noexcept override {
        return std::string("Unknown command: " + command).c_str();
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
