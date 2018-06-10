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
#include <iostream>
#include <vector>
#include <algorithm>

using namespace Commands;
class Parser {
public:
    Parser() = default;
    std::vector<Token> parseLine(const std::string & line);
    void parseAndExecuteTokens(const std::vector<Token> & tokens);
    /**
     *
     * @return if exit command was typed
     */

private:
    std::shared_ptr<Statement> parseCommand( const std::vector<Token> & tokens);

    void addAndTokenClean(std::vector<Token>&, std::string&);
};


#endif //SHELL_INTERPRETER_PARSER_H
