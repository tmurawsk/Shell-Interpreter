//
// Created by jacek on 13.06.18.
//

#include "Lexer.h"


std::vector<Token> Lexer::getTokens(const std::string & line) {
    auto tokens = readTokens(line);
    tokens = refactorTokens(tokens);
//    for(auto i :tokens){
//        std::cout<<i.type <<" "<<i.value<<std::endl;
//    }
    return tokens;
}

std::vector<Token> Lexer::readTokens(const std::string & line) {
    std::vector<Token> tokens;
    std::string buffer;
    char ch;
    for(auto i : line) {
        ch = i;
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
                tokens.emplace_back(ASSIGNMENT,"=");
                break;
            case '$':
                addTokenAndClean(tokens,buffer);
                tokens.emplace_back(ENV,"$");
                break;
            case ' ':
                addTokenAndClean(tokens,buffer);
                tokens.emplace_back(SPACE," ");
                break;
            case'\'':
                addTokenAndClean(tokens,buffer);
                tokens.emplace_back(QUOTE,"\'");
                break;
            case '\"':
                addTokenAndClean(tokens,buffer);
                tokens.emplace_back(DOUBLE_QUOTE,"\"");
                break;
            default:
                buffer += ch;
        }
        if(buffer == "./")
        {
            tokens.emplace_back(EXEC, buffer);
            buffer = "";
        }
    }
    addTokenAndClean(tokens,buffer);
//    for(auto i :tokens){
//        std::cout<<i.type <<" "<<i.value<<std::endl;
//    }
    std::cin;
    return tokens;
}

void Lexer::addTokenAndClean(std::vector<Token> & to, std::string & from) {
    if (!from.empty()) {
        to.emplace_back(STRING, from);
        from = "";
    }
}

std::vector<Token> Lexer::refactorTokens(const std::vector<Token> &args) {
    enum State{
        argument_s,
        env_s,
        quote_s,
        doubleQuote_s,
    } state = argument_s;

    std::vector<Token> result;

    std::string buffer;
    for(int i = 0; i < args.size() ; ++i){
        std::vector<std::string> str;
        switch (state){
            case argument_s:
                if(args[i].type == TokenType::SPACE) {
                    if (!buffer.empty()){
                        result.emplace_back(TokenType::STRING,buffer);
                        buffer = "";
                    }
                }
                else if(args[i].type == TokenType::QUOTE)
                    state = quote_s;
                else if(args[i].type == TokenType::DOUBLE_QUOTE)
                    state = doubleQuote_s;
                else if(args[i].type == TokenType::ENV)
                    state = env_s;
                else if(args[i].type == TokenType::STRING)
                    buffer+=args[i].value;
                else if(args[i].type == TokenType::EXEC){
                    if(result.empty() || (--result.end())->type == TokenType::PIPE){
                        result.emplace_back(TokenType::STRING,args[i].value);
                    }
                    else{
                        buffer+=args[i].value;
                    }
                }
                else{
                    if (!buffer.empty()){
                        result.emplace_back(TokenType::STRING,buffer);
                        buffer = "";
                    }
                    result.emplace_back(args[i]);
                }
                break;
            case env_s:
                str = getEnv(args,i);
                for( auto & I : str)
                    buffer += I;
                state = argument_s;
                break;
            case quote_s:
                buffer += getQuote(args,i);
                state = argument_s;
                break;
            case doubleQuote_s:
                buffer += getDoubleQuote(args,i);
                state = argument_s;
                break;
        }
    }
    if (!buffer.empty()){
        result.emplace_back(TokenType::STRING,buffer);
        buffer = "";
    }
    return result;
}

std::string Lexer::getQuote(std::vector<Token> args, int & i) {
    std::string result;
    while(i < args.size()){
        if(args[i].type==TokenType::QUOTE)
            return result;
        result+=args[i].value;
        ++i;
    }
    throw MissingSignException('\'');
};

std::string Lexer::getDoubleQuote(std::vector<Token> args, int & i) {
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

std::vector<std::string> Lexer::getEnv(const std::vector<Token>& args, int & i) {
    std::vector<std::string> result;
    std::string str;

    if(args[i].type == TokenType::QUOTE){
        str = getQuote(args,i);
        result.push_back(str);
    }
    else if(args[i].type == TokenType::DOUBLE_QUOTE) {
        str = getDoubleQuote(args, i);
        result.push_back(str);
    }
    else if(args[i].type == TokenType::STRING) {
        str = Environment::find(args[i].value);
        std::string buffer;
        for(auto I : str){
            if(I != ' ')
                buffer += I;
            else{
                if(!buffer.empty())
                    result.push_back(buffer);
                buffer="";
            }
        }
        if(!buffer.empty())
            result.push_back(buffer);
    }
    else {
        str = args[i - 1].value;
        result.push_back(str);
    }
    return result;
}

