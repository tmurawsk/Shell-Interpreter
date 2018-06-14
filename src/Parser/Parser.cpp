#include "Parser.h"


Redirector Parser::parseLine(const std::string &line) {

    auto tokens = lexer.getTokens(line);
    auto commands = pipeSeparator(tokens);
    Redirector redirector;
    for(auto & I : commands)
        redirector.addPipe(parseCommand(I));
    return redirector;
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
        ptr = std::make_shared<SetEnv>();
        argIndex = 0;
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

    std::vector<std::string> args = refactorArguments(getInputOutput(tokens,ptr),argIndex);
    for (auto & I : args)
        ptr->addArgument(I);
    return ptr;
}

std::vector<std::string> Parser::refactorArguments(const std::vector<Token> & args, int startingIndex) {

    std::vector<std::string> result;
    for(int i = startingIndex ; i < args.size(); ++i){
        result.push_back(args[i].value);
    }
    return  result;
}

const std::vector<std::vector<Token> > Parser::pipeSeparator(const std::vector<Token> & tokens) {

    std::vector<int> pipes;
    pipes.push_back(-1);

    for(int i = 0; i < tokens.size() ; ++i){
        if(tokens[i].type == TokenType::PIPE)
            pipes.push_back(i);
    }

    if(pipes.size() > MAX_PIPES)
        throw TooManyPipesException(MAX_PIPES,(int)pipes.size());

    std::vector<std::vector<Token> > result;
    std::vector<Token> singleFunction;

    for(auto & I : pipes) {
        int i = I + 1;
        while (i < tokens.size() && tokens[i].type != TokenType::PIPE) {
            singleFunction.push_back(tokens[i]);
            ++i;
        }
        if (singleFunction.empty())
            throw MissingCommandException();
        result.push_back(singleFunction);

        singleFunction.clear();
    }

//    for(auto &i : result) {
//
//        for(auto &j : i)
//            std::cout << j.value << " ";
//        std::cout << " | ";
//    }

    return result;
}

std::vector<Token> Parser::getInputOutput(const std::vector<Token> & tokens,std::shared_ptr<Statement>& ptr) {
    std::vector<Token> result;
    for(int i = 0 ; i < tokens.size() ; ++i){
        if(tokens[i].type == TokenType::IN){
            if(++i < tokens.size() && tokens[i].type == TokenType::STRING)
                ptr->setInFile(tokens[i].value);
            else
                throw MissingFileNameException();
        }
        else if(tokens[i].type == TokenType::OUT){
            if(++i < tokens.size() && tokens[i].type == TokenType::STRING)
                ptr->setOutFile(tokens[i].value);
            else
                throw MissingFileNameException();
        }
        else
            result.push_back(tokens[i]);
    }
    return result;
}
