#ifndef SHELL_INTERPRETER_EXITEXCEPTION_H
#define SHELL_INTERPRETER_EXITEXCEPTION_H

#include <exception>

class ExitException : public std::exception{
public:
    const char* what() const noexcept override {
        return "Terminal closed\n";
    }
};
#endif //SHELL_INTERPRETER_EXITEXCEPTION_H
