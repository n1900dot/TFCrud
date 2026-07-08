#pragma once

#include <vector>

#include "irepository.hpp"

template<typename T>
class MemoryRepository :
public IRepository<T>
{
public:

    size_t size() const override
    {
        return records_.size();
    }

    const T& at(size_t index) const override
    {
        return records_.at(index);
    }

    T& at(size_t index) override
    {
        return records_.at(index);
    }

    void append(const T& obj) override
    {
        records_.push_back(obj);
    }

    void insert(
        size_t index,
        const T& obj) override
        {
            records_.insert(
                records_.begin() + index,
                            obj
            );
        }

        void update(
            size_t index,
            const T& obj) override
            {
                records_.at(index) = obj;
            }

            void erase(size_t index) override
            {
                records_.erase(
                    records_.begin() + index
                );
            }

            void clear() override
            {
                records_.clear();
            }

private:

    std::vector<T> records_;
};
