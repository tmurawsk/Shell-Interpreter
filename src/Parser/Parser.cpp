//
// Created by dram on 06.06.18.
//

#include "Parser.h"
const char Parser::nonChangeValue = '\0';

std::shared_ptr<Statement> Parser::parseLine(const std::string & line) {

    auto tokens = readTokens(line);
    return parseCommand(tokens);
}


std::vector<Token> Parser::readTokens(const std::string & line) {
    std::vector<Token> tokens;

    std::string buffer;
    char ch;
    for(int i = 0; i < line.size() ; ++i) {
        ch = line[i];
        if(isspace(ch))
            ch = ' ';
        switch (ch) {
            case '<':
                addTokenAndClean(tokens,buffer);
                tokens.emplace_back(IN,"<");
                break;
            case '>':
                addTokenAndClean(tokens,buffer);
                tokens.emplace_back(OUT,">");
                break;
            case '|':
                addTokenAndClean(tokens,buffer);
                tokens.emplace_back(PIPE,"|");
                break;
            case '=':
                addTokenAndClean(tokens,buffer);
                tokens.emplace_back(ASSIGMENT,"=");
                break;
            case ' ':
                addTokenAndClean(tokens,buffer);
                tokens.emplace_back(SPACE," ");
                skipSpaces(line,i);
                break;
            case'\'':
                addTokenAndClean(tokens,buffer);
                tokens.emplace_back(QUOTE,readTo(line,i,ch));
                break;
            case '\"':
                addTokenAndClean(tokens,buffer);
                tokens.emplace_back(DOUBLE_QUOTE,readTo(line,i,ch));
                break;
            default:
                buffer += ch;
        }
        if(buffer == "./" && tokens.empty())
            addTokenAndClean(tokens,buffer);
    }
    addTokenAndClean(tokens,buffer);
    for(auto i :tokens){
        std::cout<<i.type <<" "<<i.value<<std::endl;
    }
    std::cin;
    return tokens;
}

void Parser::addTokenAndClean(std::vector<Token> & to, std::string & from) {
    if (!from.empty()) {
        to.emplace_back(STRING, from);
        from = "";
    }
}

std::shared_ptr<Statement> Parser::parseCommand(const std::vector<Token> &tokens) {

    std::string commandName = tokens.begin()->value;

    Command command;
    auto comm = command.map.find(commandName);

    int argIndex;
    std::shared_ptr<Statement> ptr;

    if(comm == command.map.end()) {
        char * env = getenv(commandName.c_str());
        if(env) {
            ptr = std::make_shared<SetEnv>();
            argIndex = 0;
        }
        else
            throw UnknownCommandException(commandName);
    }
    else {
        argIndex = 1;
        switch ((*comm).second) {
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

    }

    std::vector<std::string> args = refactorArguments(tokens,argIndex);
    for (auto & I : args)
        ptr->addArgument(I);

    return ptr;
}

std::string Parser::readTo(const std::string & line, int & i , char c) {
    std::string result;

    ++i;
    while(i < line.size()){
        if(line[i] == c)
            return result;
        result += line[i];
        ++i;
    }
    throw MissingSignException(c);
}

void Parser::skipSpaces(const std::string& line, int& i) {
    while(i+1 < line.size() && isspace(line[i+1]))
        ++i;
}

std::vector<std::string> Parser::refactorArguments(const std::vector<Token> & args, int startingInde) {

}

