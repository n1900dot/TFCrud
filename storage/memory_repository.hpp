#pragma once

#include <vector>
#include <stdexcept>

#include "irepository.hpp"

template<typename T>
class MemoryRepository : public IRepository<T>
{
public:

    size_t size() const override
    {
        return data_.size();
    }

    bool empty() const override
    {
        return data_.empty();
    }

    T& at(size_t index) override
    {
        return data_.at(index);
    }

    const T& at(size_t index) const override
    {
        return data_.at(index);
    }

    void insert(const T& obj) override
    {
        data_.push_back(obj);
    }

    void update(size_t index, const T& obj) override
    {
        data_.at(index) = obj;
    }

    void erase(size_t index) override
    {
        data_.erase(data_.begin() + index);
    }

    void clear() override
    {
        data_.clear();
    }

    std::vector<T>& data()
    {
        return data_;
    }

    const std::vector<T>& data() const
    {
        return data_;
    }

private:

    std::vector<T> data_;
};
void insert(
    size_t index,
    const T& obj) override
    {
        data_.insert(
            data_.begin()+index,
                     obj
        );
    }
    void append(
        const T& obj) override
        {
            data_.push_back(obj);
        }
