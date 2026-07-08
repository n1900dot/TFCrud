#pragma once

#include <string>
#include <vector>
#include <functional>

struct FieldInfo
{
    std::string name;

    std::string type;

    size_t offset;

    bool searchable = true;

    bool editable = true;

    bool visible = true;

    int width = 15;
};
