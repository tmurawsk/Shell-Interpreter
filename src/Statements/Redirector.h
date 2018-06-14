#ifndef SHELL_INTERPRETER_REDIRECTOR_H
#define SHELL_INTERPRETER_REDIRECTOR_H

#include <tuple>
#include <memory>
#include "Statement.h"

class Redirector{
private:
    std::vector<std::shared_ptr<Statement> > pipes;
public:
    void execute();
    void addPipe(const std::shared_ptr<Statement> &);
    explicit Redirector() = default;

private:
    std::vector<std::string> initializeFifos();
};

#endif //SHELL_INTERPRETER_REDIRECTOR_H
