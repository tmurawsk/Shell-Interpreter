//
// Created by dram on 06.06.18.
//

#ifndef SHELL_INTERPRETER_UNKNOWNTOKEN_H
#define SHELL_INTERPRETER_UNKNOWNTOKEN_H
#include <exception>

class UnknownToken : public std::exception{
public:

    const char* what() const noexcept override {
        return "UnknownToken\n";
    }
};
#endif //SHELL_INTERPRETER_UNKNOWNTOKEN_H
