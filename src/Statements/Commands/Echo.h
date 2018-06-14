#ifndef SHELL_INTERPRETER_ECHO_H
#define SHELL_INTERPRETER_ECHO_H

#include <sstream>
#include "../Statement.h"

namespace Commands {
    class Echo : public Statement {
    public:
        void execute() override {
//            if(fork() == 0) {
                std::stringstream stream;

//                std::cout<<"echo in file: "<<inFile<<std::endl;
                if(inFile != ""){
//                    std::cout<<"in"<<std::endl;
//                    std::string fn = readFromPipe();
                    std::string fn = readFromPipe();
//                    std::cout<<fn<<std::endl;
                    arguments.emplace_back(fn);
                }

                for (auto &I : arguments) {
                    stream << I << " ";
                }
                stream << "\n";

                if(outFile == "")
                    std::cout << stream.str();
                else
                    writeToPipe(stream.str());

//                exit(0);
//            }
//            else{
//                wait(NULL);
//            }
        }
    };
}
#endif //SHELL_INTERPRETER_ECHO_H
