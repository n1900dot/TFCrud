#pragma once

#include <cstddef>

template<typename T>
class IRepository
{
public:
    virtual ~IRepository() = default;

    virtual size_t size() const = 0;

    virtual bool empty() const = 0;

    virtual T& at(size_t index) = 0;

    virtual const T& at(size_t index) const = 0;

    virtual void insert(const T& obj) = 0;

    virtual void update(size_t index, const T& obj) = 0;

    virtual void erase(size_t index) = 0;

    virtual void clear() = 0;
    virtual size_t size() const = 0;

    virtual T& at(size_t index) = 0;

    virtual const T& at(size_t index) const = 0;
};
virtual void insert(
    size_t,
    const T&) = 0;

    virtual void append(
        const T&) = 0;
