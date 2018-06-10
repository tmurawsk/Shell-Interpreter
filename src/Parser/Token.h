//
// Created by dram on 06.06.18.
//

#ifndef SHELL_INTERPRETER_TOKEN_H
#define SHELL_INTERPRETER_TOKEN_H

#include <string>
#include <map>

enum TokenType {
    String,
    IN,
    OUT,
    PIPE,
    UNDEFINED
};

class Token {
public:
    explicit Token(TokenType type, std::string & value ) : type(type), value(value) {}

    TokenType type = UNDEFINED;
    std::string value;
};



#endif //SHELL_INTERPRETER_TOKEN_H
