#ifndef SHELL_INTERPRETER_EXITEXCEPTION_H
#define SHELL_INTERPRETER_EXITEXCEPTION_H

#include <exception>

class ExitException : std::exception{
public:
    const char* what() const noexcept override {
        return "Terminal closed";
    }
};
#endif //SHELL_INTERPRETER_EXITEXCEPTION_H
