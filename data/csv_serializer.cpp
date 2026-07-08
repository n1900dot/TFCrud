template<typename Tuple,size_t... I>
static std::string
serializeImpl(
    const T& obj,
    Tuple tuple,
    std::index_sequence<I...>)
{
    std::string line;

    (
        (
            line +=
            to_string_ex(
                obj.*(
                    std::get<I>(tuple).member
                )
            ),

            line +=
            I + 1 ==
            sizeof...(I)
            ? ""
            : ","
        ),
     ...
    );

    return line;
}
static std::string
serialize(
    const T& obj)
{
    auto meta =
    Meta<T>::fields();

    return serializeImpl(
        obj,
        meta,
        std::make_index_sequence<
        std::tuple_size_v<
        decltype(meta)
        >
        >{}
    );
}
