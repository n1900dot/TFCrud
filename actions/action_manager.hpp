#pragma once

#include <map>
#include <memory>

#include <ftxui/component/event.hpp>

class ActionManager
{
public:

    void bind(
        ftxui::Event event,
        std::shared_ptr<Action> action);

    bool handle(
        const ftxui::Event& event);

private:

    std::map<
    ftxui::Event,
    std::shared_ptr<Action>
    > actions_;
};
void ActionManager::bind(
    Event e,
    std::shared_ptr<Action> action)
{
    actions_[e] = std::move(action);
}
bool ActionManager::handle(
    const Event& e)
{
    auto it = actions_.find(e);

    if(it == actions_.end())
        return false;

    if(!it->second->enabled())
        return true;

    it->second->execute();

    return true;
}
