#include "Redirector.h"

void Redirector::execute() {
    for(auto & i : pipe){
        std::cout<<i->getInFile()<<std::endl;
        std::cout<<i->getOutFile()<<std::endl;
        i->execute();
    }
}

void Redirector::addPipe(const std::shared_ptr<Statement> & newPipe) {
    pipe.push_back(newPipe);
}
