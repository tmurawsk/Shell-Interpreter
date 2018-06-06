//
// Created by dram on 06.06.18.
//

#ifndef SHELL_INTERPRETER_UNKNOWNTOKEN_H
#define SHELL_INTERPRETER_UNKNOWNTOKEN_H
#include <exception>

class UnknownToken : std::exception{
public:

    const char* what() const noexcept override {
        return "UnknownToken";
    }
};
#endif //SHELL_INTERPRETER_UNKNOWNTOKEN_H
