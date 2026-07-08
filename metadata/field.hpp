#pragma once

#include <string_view>

#include "field_flags.hpp"

namespace ftcrud
{

template<class Class,class Member>
struct Field
{
    using class_type  = Class;
    using member_type = Member;

    std::string_view name;

    std::string_view caption;

    Member Class::*member;

    FieldFlags flags =
        FieldFlags::Searchable |
        FieldFlags::Sortable;

    std::size_t width = 15;
};

}
