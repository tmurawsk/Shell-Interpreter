#include "Redirector.h"

void Redirector::execute() {
    for(auto & i : pipe){
        i->execute();
    }
}

void Redirector::addPipe(const std::shared_ptr<Statement> & newPipe) {
    pipe.push_back(newPipe);
}
