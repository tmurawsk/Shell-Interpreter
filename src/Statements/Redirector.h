#ifndef SHELL_INTERPRETER_REDIRECTOR_H
#define SHELL_INTERPRETER_REDIRECTOR_H

#include <tuple>
#include <memory>
#include "Statement.h"

class Redirector{
private:
    std::vector<std::shared_ptr<Statement> > pipe;
public:
    void execute();
    void addPipe(const std::shared_ptr<Statement> &);
    explicit Redirector() = default;
};

#endif //SHELL_INTERPRETER_REDIRECTOR_H
