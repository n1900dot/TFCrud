#pragma once

#include <vector>

#include "irepository.hpp"

template<typename T>
class RowView
{
public:

    explicit RowView(
        const IRepository<T>& repo)
        :
        repo_(repo)
    {
    }

    void assign(
        std::vector<size_t> rows)
    {
        rows_ = std::move(rows);
    }

    size_t size() const
    {
        return rows_.size();
    }

    bool empty() const
    {
        return rows_.empty();
    }

    const T& operator[](size_t i) const
    {
        return repo_.at(rows_[i]);
    }

    size_t index(size_t i) const
    {
        return rows_[i];
    }

    const std::vector<size_t>&
    indices() const
    {
        return rows_;
    }

private:

    const IRepository<T>& repo_;

    std::vector<size_t> rows_;
};
