#pragma once

#include <string>

template<typename T>
class Validator
{
public:

    virtual ~Validator() = default;

    virtual bool validate(
        const T& value) const = 0;

    virtual std::string message() const = 0;
};
