#pragma once

#include <string>

class Command
{
public:

    virtual ~Command() = default;

    virtual std::string name() const = 0;

    virtual void execute() = 0;

    virtual void undo() = 0;
};
