#ifndef SHELL_INTERPRETER_PARSER_H
#define SHELL_INTERPRETER_PARSER_H


#include <iostream>
#include <vector>
#include <algorithm>

#include "../Environment.h"
#include "Lexer.h"
#include "Command.h"

#include "../Exceptions.h"
#include "../Statements/Statement.h"
#include "../Statements/Commands/Exp.h"
#include "../Statements/Commands/Cd.h"
#include "../Statements/Commands/Pwd.h"
#include "../Statements/Commands/Echo.h"
#include "../Statements/Commands/Exit.h"
#include "../Statements/Commands/Grep.h"
#include "../Statements/Commands/Ls.h"
#include "../Statements/Commands/Mkfifo.h"
#include "../Statements/Commands/Exec.h"
#include "../Statements/Commands/SetEnv.h"
#include "../Statements/Redirector.h"


using namespace Commands;
class Parser {
public:
    Parser() = default;
    Redirector parseLine(const std::string & line);

private:
    Lexer lexer;
    const std::vector<std::vector<Token> > pipeSeparator(const std::vector<Token> &);

    std::shared_ptr<Statement> parseCommand( const std::vector<Token> & tokens);
    std::vector<std::string> refactorArguments(const std::vector<Token> &, int);
//
//    std::string getEnv(std::vector<Token>,int&);
//    std::string getQuote(std::vector<Token>,int&);
//    std::string getDoubleQuote(std::vector<Token>,int&);
};


#endif //SHELL_INTERPRETER_PARSER_H
