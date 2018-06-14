#ifndef SHELL_INTERPRETER_LEXER_H
#define SHELL_INTERPRETER_LEXER_H


#include <string>
#include <memory>
#include "Token.h"
#include "../Statements/Statement.h"
#include "../Environment.h"

class Lexer {
public:
    Lexer() = default;

    std::vector<Token> getTokens(const std::string &);
private:
    std::vector<Token> readTokens(const std::string &);
    void addTokenAndClean(std::vector<Token> &, std::string &);

    std::vector<Token> refactorTokens(const std::vector<Token> &);

    std::vector<std::string> getEnv(const std::vector<Token>&,int&);
    std::string getQuote(std::vector<Token>,int&);
    std::string getDoubleQuote(std::vector<Token>,int&);

};
#endif //SHELL_INTERPRETER_LEXER_H
