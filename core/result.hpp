#pragma once

#include <string>
#include <utility>

namespace ftcrud
{

template<typename T>
class Result
{
public:

    Result(T value)
        : ok_(true),
          value_(std::move(value))
    {
    }

    Result(std::string message)
        : ok_(false),
          error_(std::move(message))
    {
    }

    explicit operator bool() const
    {
        return ok_;
    }

    bool success() const
    {
        return ok_;
    }

    const T& value() const
    {
        return value_;
    }

    T& value()
    {
        return value_;
    }

    const std::string& error() const
    {
        return error_;
    }

private:

    bool ok_ = false;

    T value_{};

    std::string error_;
};

}
