#ifndef SHELL_INTERPRETER_COMMAND_H
#define SHELL_INTERPRETER_COMMAND_H

#include <string>
#include <map>

enum CommandType{
    cd_c,
    echo_c,
    exec_c,
    exit_c,
    exp_c,
    grep_c,
    ls_c,
    mkfifo_c,
    pwd_c
};

class Command{
public:
    std::map<std::string, CommandType> map = {
            std::pair<std::string, CommandType>("cd",cd_c),
            std::pair<std::string, CommandType>("echo",echo_c),
            std::pair<std::string, CommandType>("./",exec_c),
            std::pair<std::string, CommandType>("exit",exit_c),
            std::pair<std::string, CommandType>("export",exp_c),
            std::pair<std::string, CommandType>("grep",grep_c),
            std::pair<std::string, CommandType>("ls",ls_c),
            std::pair<std::string, CommandType>("mkfifo",mkfifo_c),
            std::pair<std::string, CommandType>("pwd",pwd_c),
    };
    Command() = default;
};
#endif //SHELL_INTERPRETER_COMMAND_H
