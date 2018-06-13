#ifndef SHELL_INTERPRETER_LEXER_H
#define SHELL_INTERPRETER_LEXER_H


#include <string>
#include <memory>
#include "Token.h"
#include "../Statements/Statement.h"

class Lexer {
public:
    Lexer() = default;

    std::vector<Token> readTokens(const std::string &);
private:
    void addTokenAndClean(std::vector<Token> &, std::string &);

};
#endif //SHELL_INTERPRETER_LEXER_H
