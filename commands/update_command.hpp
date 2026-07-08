#pragma once

#include "command.hpp"
#include "irepository.hpp"

template<typename T>
class UpdateCommand :
public Command
{
public:

    UpdateCommand(
        IRepository<T>& repo,
        size_t index,
        const T& value)
    :
    repo_(repo),
    index_(index),
    new_value_(value)
    {
    }

    std::string name() const override
    {
        return "Update";
    }

    void execute() override
    {
        old_value_ =
        repo_.at(index_);

        repo_.update(
            index_,
            new_value_);
    }

    void undo() override
    {
        repo_.update(
            index_,
            old_value_);
    }

private:

    IRepository<T>& repo_;

    size_t index_;

    T old_value_;

    T new_value_;
};
