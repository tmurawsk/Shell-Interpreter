//
// Created by dram on 06.06.18.
//

#include "Parser.h"

std::vector<Token> Parser::parseLine(const std::string &line) {

    std::vector<Token> tokens;

    std::string buffer;
    char ch;
    for(auto i : line) {
        ch = i;
        if(isspace(ch))
            ch = ' ';
        switch (ch) {
            case '<':
                addAndTokenClean(tokens,buffer);
                tokens.emplace_back(IN,"<");
                break;
            case '>':
                addAndTokenClean(tokens,buffer);
                tokens.emplace_back(OUT,">");
                break;
            case '|':
                addAndTokenClean(tokens,buffer);
                tokens.emplace_back(PIPE,"|");
                break;
            case ' ':
                addAndTokenClean(tokens,buffer);
                break;
            default:
                buffer += ch;
        }
        if(buffer == "./" && tokens.empty())
            addAndTokenClean(tokens,buffer);
    }
    addAndTokenClean(tokens,buffer);
    return tokens;
}

void Parser::addAndTokenClean(std::vector<Token> & to, std::string & from) {
    if (!from.empty()) {
        to.emplace_back(String, from);
        from = "";
    }
}

void Parser::parseAndExecuteTokens(const std::vector<Token> &tokens) {
    std::vector<Statement> commands;
    auto command = parseCommand(tokens);
    command->execute();
}

std::shared_ptr<Statement> Parser::parseCommand(const std::vector<Token> &tokens) {

    std::string commandName = tokens.begin()->value;
    std::transform(commandName.begin(), commandName.end(), commandName.begin(), ::tolower); //ignore case

    Command command;
    std::shared_ptr<Statement> ptr;

    auto comm = command.map.find(commandName);
    if(comm == command.map.end())
        throw UnknownCommand(commandName);

    switch((*comm).second){
        case CommandType::cd_c:
            ptr = std::make_shared<Cd>();
            break;
        case CommandType::echo_c:
            ptr = std::make_shared<Echo>();
            break;
        case CommandType::exec_c:
            ptr = std::make_shared<Exec>();
            break;
        case CommandType::exit_c:
            ptr = std::make_shared<Exit>();
            break;
        case CommandType::exp_c:
            ptr = std::make_shared<Exp>();
            break;
        case CommandType::grep_c:
            ptr = std::make_shared<Grep>();
            break;
        case CommandType::ls_c:
            ptr = std::make_shared<Ls>();
            break;
        case CommandType::mkfifo_c:
            ptr = std::make_shared<Mkfifo>();
            break;
        case CommandType::pwd_c:
            ptr = std::make_shared<Pwd>();
            break;
    }

    for (int i = 1; i < tokens.size(); ++i)
        ptr->addArgument(tokens[i].value);

    return ptr;
}

