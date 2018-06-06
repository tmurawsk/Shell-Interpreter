//
// Created by dram on 06.06.18.
//


#include "Parser.h"
#include "../Statements/Commands/Echo.h"
#include "../Statements/Commands/Exit.h"
#include "../Statements/Commands/Grep.h"
#include "../Statements/Commands/Ls.h"
#include "../Statements/Commands/Mkfifo.h"

bool Parser::wasExit() {
    return _wasExit;
}

std::vector<Token> Parser::parseLine(const std::string &line) {

    // ls aaaa | grep ccc | grep xyz ads dasd dsad >> & out < in
    std::vector<Token> tokens;

    std::string buffer;
    char ch;
    for (int i = 0; i < line.size(); i++) {
        ch = line[i];
        if (isalpha(ch)) {
            buffer += ch;
        } else {
            if (!buffer.empty()) {
                tokens.emplace_back(String, buffer);
                buffer = "";
            }

            switch (ch) {
                case '<':
                    tokens.emplace_back(IN, "");
                    break;
                case '>':
                    if (line[i + 1] == '>') {
                        tokens.emplace_back(OUT, "");
                        i++;
                    }
                    else {
                        throw UnknownToken();
                    }
                    break;
                case '|':
                    tokens.emplace_back(PIPE, "");
                    break;
                case '$':
                    tokens.emplace_back(ENV, "");
                    break;
                case ' ':
                    break;
                default:
                    throw UnknownToken();

            }
        }
    }
    if (!buffer.empty()) {
        tokens.emplace_back(String, buffer);
        buffer = "";
    }
    return tokens;
}

Parser::Parser() {

}

void Parser::parseAndExecuteTokens(const std::vector<Token> &tokens) {
    std::vector<Statement> commands;
    auto command = parseCommand(0, tokens);
    command->execute();
}

std::shared_ptr<Statement> Parser::parseCommand(int from, const std::vector<Token> &tokens) {
    std::string commandName = tokens[from].value;
    std::transform(commandName.begin(), commandName.end(), commandName.begin(), ::tolower); //ignore case

    std::shared_ptr<Statement> ptr;
    if(commandName == "cd"){
        ptr = std::make_shared<Cd>();
    } else if(commandName == "echo"){
        ptr = std::make_shared<Echo>();
    } else if(commandName == "exit"){
        ptr = std::make_shared<Exit>();
        _wasExit = true;
    } else if(commandName == "exp"){
        ptr = std::make_shared<Exp>();
    } else if(commandName == "grep"){
        ptr = std::make_shared<Grep>();
    } else if(commandName == "ls"){
        ptr = std::make_shared<Ls>();
    } else if(commandName == "mkfifo"){
        ptr = std::make_shared<Mkfifo>();
    } else if(commandName == "pwd"){
        ptr = std::make_shared<Pwd>();
    }
    else {
        throw std::runtime_error("Unknown command!");
    }

    //add arguments
    for(int i = from+1; i < tokens.size() && tokens[i].type == String; i++){
        ptr->addArgument(tokens[i].value);
    }
    return ptr;
}

