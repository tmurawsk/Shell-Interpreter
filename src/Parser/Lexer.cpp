//
// Created by jacek on 13.06.18.
//

#include "Lexer.h"


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
        if(buffer == "./" && tokens.empty())
            addTokenAndClean(tokens,buffer);
    }
    addTokenAndClean(tokens,buffer);
//    for(auto i :tokens){
//        std::cout<<i.type <<" "<<i.value<<std::endl;
//    }
//    std::cin;
    return tokens;
}

void Lexer::addTokenAndClean(std::vector<Token> & to, std::string & from) {
    if (!from.empty()) {
        to.emplace_back(STRING, from);
        from = "";
    }
}