#pragma once

#include "command.hpp"
#include "irepository.hpp"

template<typename T>
class DeleteCommand :
public Command
{
public:

    DeleteCommand(
        IRepository<T>& repo,
        size_t index)
    :
    repo_(repo),
    index_(index)
    {
    }

    std::string name() const override
    {
        return "Delete";
    }

    void execute() override
    {
        deleted_ =
        repo_.at(index_);

        repo_.erase(index_);
    }

    void undo() override
    {
        repo_.insert(
            index_,
            deleted_);
    }

private:

    IRepository<T>& repo_;

    size_t index_;

    T deleted_;
};
