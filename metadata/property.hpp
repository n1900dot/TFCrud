#pragma once

#include <functional>

template<typename Owner, typename Value>
class Property
{
public:

    using Getter =
        std::function<Value(const Owner&)>;

    using Setter =
        std::function<void(Owner&,const Value&)>;

    Property(
        const char* name,
        Getter getter,
        Setter setter)
        :
        name_(name),
        getter_(std::move(getter)),
        setter_(std::move(setter))
    {
    }

    const char* name() const
    {
        return name_;
    }

    Value get(
        const Owner& obj) const
    {
        return getter_(obj);
    }

    void set(
        Owner& obj,
        const Value& value) const
    {
        setter_(obj,value);
    }

private:

    const char* name_;

    Getter getter_;

    Setter setter_;
};
