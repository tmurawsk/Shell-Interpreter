#include <sys/stat.h>
#include <unistd.h>
#include "Redirector.h"

void Redirector::execute() {
    if (pipes.size() == 1) {
        pipes[0]->execute();
        return;
    }

    std::vector<std::string> fifos = initializeFifos();

    for(int i = 0; i < pipes.size() - 1; i++) {
        pipes[i]->setOutFile(fifos[i]);
        pipes[i+1]->setInFile(fifos[i]);
    }

    for(int i = 0; i < pipes.size(); i++) {
        if(fork() == 0) {
            pipes[i]->execute();
        }
        else if(i == pipes.size() - 1)
            wait(NULL);
    }
}

void Redirector::addPipe(const std::shared_ptr<Statement> & newPipe) {
    pipes.push_back(newPipe);
}

std::vector<std::string> Redirector::initializeFifos() {
    std::vector<std::string> fifos = std::vector<std::string>();

    for(int i = 0; i < pipes.size() - 1; i++) {
        fifos.emplace_back("/tmp/myfifo" + i);
        mkfifo(fifos[i].c_str(), 0666);
    }

    return fifos;
}
