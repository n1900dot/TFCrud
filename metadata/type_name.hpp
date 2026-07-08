#pragma once

#include <string>

template<typename T>
std::string type_name()
{
    return "unknown";
}

template<>
inline std::string type_name<int>()
{
    return "int";
}

template<>
inline std::string type_name<double>()
{
    return "double";
}

template<>
inline std::string type_name<float>()
{
    return "float";
}

template<>
inline std::string type_name<char>()
{
    return "char";
}

template<>
inline std::string type_name<std::string>()
{
    return "string";
}
