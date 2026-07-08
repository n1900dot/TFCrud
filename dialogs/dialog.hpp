#pragma once

#include <functional>

#include <ftxui/component/component.hpp>

class Dialog
{
public:

    virtual ~Dialog() = default;

    virtual ftxui::Component
    component() = 0;

    virtual void
    show() = 0;

    virtual void
    close() = 0;

    bool visible() const
    {
        return visible_;
    }

protected:

    bool visible_ = false;
};
