#pragma once

#include <vector>
#include <tuple>
#include <string>

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>

#include "reflection.hpp"
#include "from_string.hpp"
#include "string_utils.hpp"

using namespace ftxui;

struct FormField
{
    std::string label;
    std::string value;
};

template<typename T>
class FormGenerator
{
public:

    FormGenerator()
    {
        buildFields();

        for(auto& field : fields)
        {
            inputs.push_back(
                Input(
                    &field.value,
                    field.label
                )
            );
        }

        container =
            Container::Vertical(inputs);

        renderer =
            Renderer(
                container,
                [&]
                {
                    Elements rows;

                    for(size_t i=0;i<fields.size();i++)
                    {
                        rows.push_back(
                            hbox({
                                text(fields[i].label + ": "),
                                inputs[i]->Render()
                            })
                        );
                    }

                    return vbox({
                        text("Record") | bold,
                        separator(),
                        vbox(std::move(rows))
                    }) | border;
                }
            );
    }

    Component component()
    {
        return renderer;
    }

    T buildObject()
    {
        T obj{};

        auto meta =
            Meta<T>::fields();

        assignImpl(
            obj,
            meta,
            std::make_index_sequence<
                std::tuple_size_v<
                    decltype(meta)
                >
            >{}
        );

        return obj;
    }

    void load(const T& obj)
    {
        auto meta =
            Meta<T>::fields();

        loadImpl(
            obj,
            meta,
            std::make_index_sequence<
                std::tuple_size_v<
                    decltype(meta)
                >
            >{}
        );
    }

private:

    std::vector<FormField> fields;
    std::vector<Component> inputs;

    Component container;
    Component renderer;

    void buildFields()
    {
        auto meta =
            Meta<T>::fields();

        buildImpl(
            meta,
            std::make_index_sequence<
                std::tuple_size_v<
                    decltype(meta)
                >
            >{}
        );
    }

    template<typename Tuple,size_t... I>
    void buildImpl(
        Tuple tuple,
        std::index_sequence<I...>)
    {
        (
            fields.push_back({
                std::get<I>(tuple).name,
                ""
            }),
            ...
        );
    }

    template<typename Tuple,size_t... I>
    void assignImpl(
        T& obj,
        Tuple tuple,
        std::index_sequence<I...>)
    {
        (
            assignField<I>(
                obj,
                std::get<I>(tuple)
            ),
            ...
        );
    }

    template<size_t Index,
             typename FieldType>
    void assignField(
        T& obj,
        FieldType field)
    {
        using Member =
            typename FieldType::member_type;

        obj.*(
            field.member
        ) =
            from_string<Member>(
                fields[Index].value
            );
    }

    template<typename Tuple,size_t... I>
    void loadImpl(
        const T& obj,
        Tuple tuple,
        std::index_sequence<I...>)
    {
        (
            (
                fields[I].value =
                    to_string_ex(
                        obj.*(
                            std::get<I>(tuple).member
                        )
                    )
            ),
            ...
        );
    }
};
