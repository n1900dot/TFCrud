#pragma once

#include "command.hpp"
#include "irepository.hpp"

template<typename T>
class CreateCommand :
public Command
{
public:

    CreateCommand(
        IRepository<T>& repo,
        const T& obj)
    :
    repo_(repo),
    object_(obj)
    {
    }

    std::string name() const override
    {
        return "Create";
    }

    void execute() override
    {
        index_ = repo_.size();

        repo_.append(object_);
    }

    void undo() override
    {
        repo_.erase(index_);
    }

private:

    IRepository<T>& repo_;

    T object_;

    size_t index_ = 0;
};
