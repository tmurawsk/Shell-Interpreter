//
// Created by dram on 06.06.18.
//

#ifndef SHELL_INTERPRETER_TOKEN_H
#define SHELL_INTERPRETER_TOKEN_H

#include <string>
#include <map>

enum TokenType {
    STRING,
    IN,
    OUT,
    PIPE,
    ASSIGNMENT,
    ENV,
    SPACE,
    EXEC,
    QUOTE,
    DOUBLE_QUOTE,
    UNDEFINED
};

class Token {
public:
    explicit Token(TokenType type, const std::string & value ) : type(type), value(value) {}

    TokenType type = UNDEFINED;
    std::string value;
};



#endif //SHELL_INTERPRETER_TOKEN_H
