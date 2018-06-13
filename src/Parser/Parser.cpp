//
// Created by dram on 06.06.18.
//

#include "Parser.h"
const char Parser::nonChangeValue = '\0';

std::shared_ptr<Statement> Parser::parseLine(const std::string & line) {

    auto tokens = lexer.readTokens(line);
    return parseCommand(tokens);
}

std::shared_ptr<Statement> Parser::parseCommand(const std::vector<Token> &tokens) {

    if(tokens.begin()==tokens.end())
        return std::make_shared<Statement>();
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

std::vector<std::string> Parser::refactorArguments(const std::vector<Token> & args, int startingIndex) {
    enum State{
        argument_s,
        env_s,
        quote_s,
        doubleQuote_s,
    } state = argument_s;

    std::vector<std::string> result;

    for(int i = startingIndex; i < args.size() ; ++i){
        switch (state){
            case argument_s:
                if(args[i].type == TokenType::SPACE)
                    continue;
                else if(args[i].type == TokenType::QUOTE)
                    state = quote_s;
                else if(args[i].type == TokenType::DOUBLE_QUOTE)
                    state = doubleQuote_s;
                else if(args[i].type == TokenType::ENV)
                    state = env_s;
                else
                    result.push_back(args[i].value);
                break;
            case env_s:
                result.push_back(getEnv(args,i));
                state = argument_s;
                break;
            case quote_s:
                result.push_back(getQuote(args,i));
                state = argument_s;
                break;
            case doubleQuote_s:
                result.push_back(getDoubleQuote(args,i));
                state = argument_s;
                break;
        }
    }
    return result;
}

std::string Parser::getQuote(std::vector<Token> args, int & i) {
    std::string result;
    while(i < args.size()){
        if(args[i].type==TokenType::QUOTE)
            return result;
        result+=args[i].value;
        ++i;
    }
    throw MissingSignException('\'');
};

std::string Parser::getDoubleQuote(std::vector<Token> args, int & i) {
    std::string result;
    while(i < args.size()){
        if(args[i].type==TokenType::DOUBLE_QUOTE)
            return result;
        if(args[i].type == TokenType::ENV) {
            if(i+1 < args.size() && args[i+1].type == TokenType::STRING){
                std::string envVar = Environment::find(args[i+1].value);
                if(!envVar.empty()){
                    result+=envVar;
                    ++i;
                }
                else
                    result+=args[i].value;
            }
            ++i;
            continue;
        }
        result+=args[i].value;
        ++i;
    }
    throw MissingSignException('\"');
}

std::string Parser::getEnv(std::vector<Token> args, int & i) {
    std::string result;

//    std::cout<<i<<" "<<args[i].type<<" "<<args[i].value<<std::endl;
    if(args[i].type == TokenType::QUOTE)
        return getQuote(args,i);

    if(args[i].type == TokenType::DOUBLE_QUOTE)
        return getDoubleQuote(args,i);

    if(args[i].type == TokenType::STRING)
        return Environment::find(args[i].value);
    else
        return args[i-1].value;
}
