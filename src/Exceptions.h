//
// Created by jacek on 09.06.18.
//

#ifndef SHELL_INTERPRETER_EXCEPTIONS_H
#define SHELL_INTERPRETER_EXCEPTIONS_H

#include <exception>
#include <string>

class Exception : std::exception{
public:
    virtual std::string What() const noexcept{}
};

class ExitException : public Exception{
public:
    std::string What() const noexcept override {
        return "Terminal closed";
    }
};


class UnknownCommandException: public Exception{
private:
    std::string command;
public:
    explicit UnknownCommandException(std::string & command_):command(command_){}
    std::string What() const noexcept override {

        return "Unknown command: " + command;
    }
};

class NoSuchPathException : public Exception {
public:

    std::string What() const noexcept override {
        return "No such file or directory";
    }
};

class InvalidNumberOfParametersException : public Exception {
public:

    std::string What() const noexcept override {
        return "Wrong number of parameters";
    }
};

class InvalidArgumentsException : public Exception {
public:

    std::string What() const noexcept override {
        return "Invalid arguments";
    }
};

class MissingSignException: public Exception{
    char c;
public:
    explicit MissingSignException(char c_):c(c_){}
    std::string What() const noexcept override {
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

    std::string What() const noexcept override {
        return "Undefined variable " + name;
    }
};

class UnknownUserException : public Exception {
public:

    std::string What() const noexcept override {
        return "Invalid arguments";
    }
};
class UnknownHostException : public Exception {
public:

    std::string What() const noexcept override {
        return "Invalid arguments";
    }
};
class UnknownPathException : public Exception {
public:

    std::string What() const noexcept override {
        return "Invalid arguments";
    }
};

class TooManyPipesException: public Exception{
private:
    int maxNum;
    int curNum;

public:

    TooManyPipesException(int max,int cur):maxNum(max), curNum(cur){}

    std::string What() const noexcept override {
        std::string msg;
        msg += "Too many pipes. Maximum number is ";
        msg += std::to_string(maxNum);
        msg += " and currently there are ";
        msg += std::to_string(curNum);
        msg += ".";
        return msg;
    }
};

class MissingCommandException: public Exception{
public:
    std::string What() const noexcept override {
        return "Missing command";
    }
};

class MissingFileNameException: public Exception{
public:

    std::string What() const noexcept override {
        return "Missing file";
    }
};
/*
class : public Exception{
public:

    std::string What() const noexcept override {
        return "";
    }
};
 */

#endif //SHELL_INTERPRETER_EXCEPTIONS_H
