#pragma once

#include <charconv>
#include <sstream>
#include <string>
#include <string_view>
#include <type_traits>

#include "result.hpp"

namespace ftcrud
{

class Converter
{
public:

    template<typename T>
    static std::string toString(const T& value)
    {
        if constexpr(std::is_same_v<T,std::string>)
        {
            return value;
        }
        else if constexpr(std::is_same_v<T,char>)
        {
            return std::string(1,value);
        }
        else if constexpr(std::is_arithmetic_v<T>)
        {
            return std::to_string(value);
        }
        else
        {
            std::ostringstream out;
            out << value;
            return out.str();
        }
    }

    template<typename T>
    static Result<T> tryConvert(std::string_view text)
    {
        if constexpr(std::is_same_v<T,std::string>)
        {
            return std::string(text);
        }

        else if constexpr(std::is_same_v<T,char>)
        {
            if(text.empty())
                return Result<char>("Character expected");

            return text.front();
        }

        else if constexpr(std::is_same_v<T,int>)
        {
            try
            {
                return std::stoi(std::string(text));
            }
            catch(...)
            {
                return Result<int>("Invalid integer");
            }
        }

        else if constexpr(std::is_same_v<T,long>)
        {
            try
            {
                return std::stol(std::string(text));
            }
            catch(...)
            {
                return Result<long>("Invalid long");
            }
        }

        else if constexpr(std::is_same_v<T,float>)
        {
            try
            {
                return std::stof(std::string(text));
            }
            catch(...)
            {
                return Result<float>("Invalid float");
            }
        }

        else if constexpr(std::is_same_v<T,double>)
        {
            try
            {
                return std::stod(std::string(text));
            }
            catch(...)
            {
                return Result<double>("Invalid double");
            }
        }

        else
        {
            return Result<T>("Unsupported type");
        }
    }
};

}
