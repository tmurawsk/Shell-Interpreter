//
// Created by dram on 14.06.18.
//

#ifndef SHELL_INTERPRETER_COMMANDHISTORY_H
#define SHELL_INTERPRETER_COMMANDHISTORY_H

#include <string>
#include <utility>
#include <fstream>
#include <iostream>

class CommandHistory {
private:
    std::string filePath;

    std::fstream fp;
public:
    explicit CommandHistory(std::string filePath) : filePath(std::move(filePath)) {
        if (this->filePath.empty())
            throw std::runtime_error("Could not pass empty file!");

        //create
        fp.open(this->filePath, std::fstream::out);

        if (!fp.is_open()) {
            throw std::runtime_error("Could not open file");
        }
        fp.close();

        //open normal

        fp.open(this->filePath, std::fstream::out | std::fstream::in | std::fstream::ate | std::fstream::binary);
        if (!fp.is_open()) {
            throw std::runtime_error("Could not open file");
        }

    };

    void addCommand(const std::string &command) {
        //add new line
        fp << command;

        if (command[command.size() - 1] != '\n') {
            fp << std::endl;
        }
        fp.flush();
    }

    std::string getLastComand() {
        char ch;
        fp.seekg(-1, std::ios::end); // go before eof

        ch = static_cast<char>(fp.get());

        std::cout << (int) ch;
        //omit last \n
        if(ch == '\n'){
            fp.seekg(-2, std::ios::end);
        } else {
            fp.seekg(0, std::ios::end);
        }
        int buf = 0;
        while (true) {
            ch = static_cast<char>(fp.get());
            if ((int) fp.tellg() <= 1) {
                break;
            } else if (ch == '\n' ) {
                break;
            } else {
                fp.seekg(-2, std::ios_base::cur); //move back
            }
        }
        std::string lastLine;
        getline(fp, lastLine);                      // Read the current line

        fp.seekg(-1, std::ios::end); //go back to the end

        std::cout << lastLine <<std::endl;
        return lastLine;
    }

    ~CommandHistory() {
        fp.close();
    }

};

#endif //SHELL_INTERPRETER_COMMANDHISTORY_H
