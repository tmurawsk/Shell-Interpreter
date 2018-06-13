//
// Created by dram on 06.06.18.
//

#ifndef SHELL_INTERPRETER_PARSER_H
#define SHELL_INTERPRETER_PARSER_H


#include <string>
#include "Token.h"
#include "Command.h"
#include <memory>
#include "../Statements/Statement.h"
#include "../Statements/Commands/Exp.h"
#include "../Statements/Commands/Cd.h"
#include "../Exceptions.h"
#include "../Statements/Statement.h"
#include "../Statements/Commands/Pwd.h"
#include "../Statements/Commands/Echo.h"
#include "../Statements/Commands/Exit.h"
#include "../Statements/Commands/Grep.h"
#include "../Statements/Commands/Ls.h"
#include "../Statements/Commands/Mkfifo.h"
#include "../Statements/Commands/Exec.h"
#include "../Statements/Commands/SetEnv.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "../Environment.h"

using namespace Commands;
class Parser {
public:
    Parser() = default;
    std::shared_ptr<Statement> parseLine(const std::string & line);

    const static char nonChangeValue;
private:
    std::shared_ptr<Statement> parseCommand( const std::vector<Token> & tokens);
    std::vector<std::string> refactorArguments(const std::vector<Token> &, int);

    std::vector<Token> readTokens(const std::string &);
    void skipSpaces(const std::string&, int&);
    void addTokenAndClean(std::vector<Token>&, std::string&);
    std::string readTo(const std::string &,int &, char);
};


#endif //SHELL_INTERPRETER_PARSER_H
