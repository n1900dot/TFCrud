#pragma once

#include <ftxui/component/component.hpp>

class Widget
{
public:

    virtual ~Widget() = default;

    virtual ftxui::Component
    component() = 0;
};
