#pragma once

#include "result.hpp"

namespace ftcrud
{

template<typename T>
class Validator
{
public:

    static Result<T> validate(const T& object)
    {
        return object;
    }
};

}
