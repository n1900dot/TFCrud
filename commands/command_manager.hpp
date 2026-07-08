#pragma once

#include <memory>
#include <vector>

#include "command.hpp"

class CommandManager
{
public:

    void execute(std::unique_ptr<Command> cmd)
    {
        cmd->execute();

        undo_stack_.push_back(std::move(cmd));

        redo_stack_.clear();
    }

    void undo()
    {
        if(undo_stack_.empty())
            return;

        auto cmd =
        std::move(
            undo_stack_.back());

        undo_stack_.pop_back();

        cmd->undo();

        redo_stack_.push_back(
            std::move(cmd));
    }

    void redo()
    {
        if(redo_stack_.empty())
            return;

        auto cmd =
        std::move(
            redo_stack_.back());

        redo_stack_.pop_back();

        cmd->execute();

        undo_stack_.push_back(
            std::move(cmd));
    }

    bool canUndo() const
    {
        return !undo_stack_.empty();
    }

    bool canRedo() const
    {
        return !redo_stack_.empty();
    }

    void clear()
    {
        undo_stack_.clear();
        redo_stack_.clear();
    }

private:

    std::vector<
    std::unique_ptr<Command>
    > undo_stack_;

    std::vector<
    std::unique_ptr<Command>
    > redo_stack_;
};
