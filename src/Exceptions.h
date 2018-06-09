//
// Created by jacek on 09.06.18.
//

#ifndef SHELL_INTERPRETER_EXCEPTIONS_H
#define SHELL_INTERPRETER_EXCEPTIONS_H

#include <exception>

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
public:

    const char* what() const noexcept override {
        return "Unknown command";
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
