#ifndef SHELL_INTERPRETER_ECHO_H
#define SHELL_INTERPRETER_ECHO_H

#include <sstream>
#include "../Statement.h"

namespace Commands {
    class Echo : public Statement {
    public:
        void execute() override {
            if(fork() == 0) {
                std::stringstream stream;

                if(inFile != "")
                    arguments.emplace_back(readFromPipe());

                for (auto &I : arguments) {
                    stream << I << " ";
                }
                stream << "\n";

                if(outFile == "")
                    std::cout << stream.str();
                else
                    writeToPipe(stream.str());

                exit(1);
            }
            else{
                wait(NULL);
            }
        }
    };
}
#endif //SHELL_INTERPRETER_ECHO_H
