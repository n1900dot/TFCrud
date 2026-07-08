#pragma once

#include <vector>

#include "reflection.hpp"
#include "reflection_utils.hpp"
#include "type_name.hpp"

template<typename T>
class MetadataCache
{
public:

    static const std::vector<FieldInfo>& fields()
    {
        static std::vector<FieldInfo> cache =
            build();

        return cache;
    }

private:

    static std::vector<FieldInfo> build()
    {
        std::vector<FieldInfo> result;

        for_each_field<T>(
            [&](auto field)
            {
                using Member =
                    typename decltype(field)::member_type;

                result.push_back({
                    field.name,
                    type_name<Member>(),
                    0,
                    true,
                    true,
                    true,
                    15
                });
            });

        return result;
    }
};
