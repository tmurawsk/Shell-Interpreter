//
// Created by jacek on 09.06.18.
//

#ifndef SHELL_INTERPRETER_EXCEPTIONS_H
#define SHELL_INTERPRETER_EXCEPTIONS_H

#include <exception>
#include <string>

class Exception{
public:
    virtual std::string what() const noexcept{}
};

class ExitException : public Exception{
public:
    std::string what() const noexcept override {
        return "Terminal closed";
    }
};

class UnknownTokenException : public Exception{
public:

    std::string what() const noexcept override {
        return "Unknown Token";
    }
};

class UnknownCommandException: public Exception{
private:
    std::string command;
public:
    explicit UnknownCommandException(std::string & command_):command(command_){}
    std::string what() const noexcept override {

        return "Unknown command: " + command;
    }
};

class NoSuchPathException : public Exception {
public:

    std::string what() const noexcept override {
        return "No such file or directory";
    }
};

/*
class : public Exception{
public:

    const char* what() const noexcept override {
        return "";
    }
};
 */

#endif //SHELL_INTERPRETER_EXCEPTIONS_H
