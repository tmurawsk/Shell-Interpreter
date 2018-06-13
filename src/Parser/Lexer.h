//
// Created by jacek on 13.06.18.
//

#ifndef SHELL_INTERPRETER_LEXER_H
#define SHELL_INTERPRETER_LEXER_H


#include <string>
#include <memory>
#include "Token.h"
#include "../Statements/Statement.h"

class Lexer {
public:
    Lexer() = default;

private:
    std::vector<Token> readTokens(const std::string &);

    void skipSpaces(const std::string &, int &);

    void addTokenAndClean(std::vector<Token> &, std::string &);

    std::string readTo(const std::string &, int &, char);

};
#endif //SHELL_INTERPRETER_LEXER_H
