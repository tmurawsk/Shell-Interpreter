#ifndef SHELL_INTERPRETER_PATHREADEXCEPTION_H
#define SHELL_INTERPRETER_PATHREADEXCEPTION_H

#include <exception>

class PathReadException : public std::exception{
public:
    const char* what() const noexcept override {
        return "PathReadException: can't read current path\n";
    }
};
#endif //SHELL_INTERPRETER_PATHREADEXCEPTION_H
