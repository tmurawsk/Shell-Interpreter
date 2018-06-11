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

class InvalidNumberOfParametersException : public Exception {
public:

    std::string what() const noexcept override {
        return "Wrong number of parameters";
    }
};

class InvalidArgumentsException : public Exception {
public:

    std::string what() const noexcept override {
        return "Invalid arguments";
    }
};

class MissingSignException: public Exception{
    char c;
public:
    explicit MissingSignException(char c_):c(c_){}
    std::string what() const noexcept override {
        std::string result = "Missing ";
        result +=c;
        return result;
    }
};

class UnknownVariableException: public Exception{
private:
    std::string name;
public:
    explicit UnknownVariableException(std::string& name_):name(name_){}

    std::string what() const noexcept override {
        return "Undefined variable " + name;
    }
};
/*
class : public Exception{
public:

    std::string what() const noexcept override {
        return "";
    }
};
 */

#endif //SHELL_INTERPRETER_EXCEPTIONS_H
