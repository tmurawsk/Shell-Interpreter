//
// Created by dram on 06.06.18.
//

#ifndef SHELL_INTERPRETER_PARSER_H
#define SHELL_INTERPRETER_PARSER_H


#include <string>
#include "Token.h"
#include <memory>
#include "../Statements/Statement.h"
#include "../Statements/Commands/Exp.h"
#include "../Statements/Commands/Cd.h"
#include "../Exceptions/UnknownToken.h"
#include "../Statements/Statement.h"
#include "../Statements/Commands/Pwd.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace Commands;
class Parser {
public:
    Parser();
    std::vector<Token> parseLine(const std::string & line);
    void parseAndExecuteTokens(const std::vector<Token> & tokens);
    /**
     *
     * @return if exit command was typed
     */
    bool wasExit();

private:
    std::shared_ptr<Statement> parseCommand(int from, const std::vector<Token> & tokens);
    bool _wasExit = false;

};


#endif //SHELL_INTERPRETER_PARSER_H
