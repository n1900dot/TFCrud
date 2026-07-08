#pragma once

#include <cstdint>

namespace ftcrud
{

enum class FieldFlags : uint32_t
{
    None        = 0,

    PrimaryKey  = 1 << 0,
    Required    = 1 << 1,
    ReadOnly    = 1 << 2,
    Hidden      = 1 << 3,

    Searchable  = 1 << 4,
    Sortable    = 1 << 5,

    Unique      = 1 << 6,

    Email       = 1 << 7,
    Password    = 1 << 8,

    Currency    = 1 << 9,
    Date        = 1 << 10,
    Time        = 1 << 11,

    MultiLine   = 1 << 12
};

constexpr FieldFlags operator|(
    FieldFlags a,
    FieldFlags b)
{
    return static_cast<FieldFlags>(
        static_cast<uint32_t>(a) |
        static_cast<uint32_t>(b)
    );
}

constexpr FieldFlags operator&(
    FieldFlags a,
    FieldFlags b)
{
    return static_cast<FieldFlags>(
        static_cast<uint32_t>(a) &
        static_cast<uint32_t>(b)
    );
}

constexpr bool has_flag(
    FieldFlags value,
    FieldFlags flag)
{
    return (value & flag) != FieldFlags::None;
}

}
