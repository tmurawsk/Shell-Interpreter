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

    int pid;
    for(int i = 0; i < pipes.size(); i++) {
            pid = fork();
            if (pid == 0) {
                pipes[i]->execute();
                exit(0);
            }
            else if (i == pipes.size() - 1)
                wait(NULL);
    }
}

void Redirector::addPipe(const std::shared_ptr<Statement> & newPipe) {
    pipes.push_back(newPipe);
}

std::vector<std::string> Redirector::initializeFifos() {
    std::vector<std::string> fifos = std::vector<std::string>();

    for(int i = 0; i < pipes.size() - 1; i++) {
        std::string fifoname = "/tmp/myfifo";
        fifoname+=std::to_string(i);
        fifos.emplace_back(fifoname);
        mkfifo(fifos[i].c_str(), 0666);
    }

    return fifos;
}
