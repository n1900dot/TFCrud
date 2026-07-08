#pragma once

#include <string>

class Action
{
public:

    virtual ~Action() = default;

    virtual std::string text() const = 0;

    virtual bool enabled() const
    {
        return true;
    }

    virtual void execute() = 0;
};
