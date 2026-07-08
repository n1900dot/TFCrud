#pragma once

#include <tuple>
#include <utility>

#include "reflection.hpp"

template<typename T,
         typename F,
         size_t... I>
void for_each_field_impl(
    F&& func,
    std::index_sequence<I...>)
{
    auto meta = Meta<T>::fields();

    (
        func(
            std::get<I>(meta)
        ),
        ...
    );
}

template<typename T,
         typename F>
void for_each_field(
    F&& func)
{
    constexpr size_t N =
        std::tuple_size_v<
            decltype(
                Meta<T>::fields()
            )
        >;

    for_each_field_impl<T>(
        std::forward<F>(func),
        std::make_index_sequence<N>{}
    );
}
