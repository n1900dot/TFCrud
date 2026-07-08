#pragma once

#include <string>

#include "reflection.hpp"
#include "string_utils.hpp"

template<typename T>
class CsvSerializer
{
public:

    static std::string
    serialize(
        const T& obj);
};
