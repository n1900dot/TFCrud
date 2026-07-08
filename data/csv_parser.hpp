#pragma once

#include <string>
#include <vector>

class CsvParser
{
public:

    static std::vector<std::string>
    split(
        const std::string& line,
        char delimiter = ',');
};
