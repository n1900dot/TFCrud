#pragma once

#include <string>
#include <algorithm>
#include <vector>

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <memory>
#include "form_generator.hpp"
#include "irepository.hpp"
#include "memory_repository.hpp"
#include "search.hpp"
#include "paginator.hpp"
#include "table_view.hpp"
#include "command_manager.hpp"
#include "delete_command.hpp"

using namespace ftxui;

template<typename T>
class CrudScreen
{
public:

    enum class Focus
    {
        Search,
        Table
    };

    CrudScreen(
        ScreenInteractive& screen,
        Repository<T>& repo)
    :
    screen(screen),
    repo(repo)
    {
        refreshSearch();

        renderer = Renderer([&]
        {
            refreshSearch();

            auto range =
            Paginator::page(
                visible_rows.size(),
                            page
            );

            size_t total_pages =
            std::max(
                size_t(1),
                     Paginator::pages(
                         visible_rows.size()
                     )
            );

            if(page >= total_pages)
                page = total_pages - 1;

            auto search_bar =
            hbox({
                text("Search: "),
                 text(search_text)
            });

            if(focus == Focus::Search)
                search_bar =
                search_bar | inverted;

            return vbox({

                text("CRUD Framework")
                | bold,

                separator(),

                        search_bar,

                        separator(),

                        TableRenderer<T>::render(
                            repo.all(),
                                                 visible_rows,
                                                 range.start,
                                                 range.end,
                                                 page * Paginator::PageSize
                                                 + selected
                        ),

                        separator(),

                        text(
                            "Records: "
                            + std::to_string(
                                visible_rows.size()
                            )
                        ),

                        text(
                            "Page "
                            + std::to_string(page + 1)
                            + "/"
                            + std::to_string(total_pages)
                        ),

                        separator(),

                        text(
                            "[TAB] Focus  "
                            "[/] Search  "
                            "[ESC] Table  "
                            "[↑↓] Select  "
                            "[PgUp/PgDn] Page  "
                            "[D] Delete  "
                            "[Q] Quit"
                            "[F2] New"
                            "[F3] Edit"
                            "[F4] Delete"
                            "[Ctrl+Z] Undo"
                            "[Ctrl+Y] Redo"
                            "[Q] Quit"
                        )

            }) | border;
        });

        component_ =
        CatchEvent(
            renderer,
            [&](Event event)
            {
                return onEvent(event);
            }
        );
    }

    Component component()
    {
        return component_;
    }
    CommandManager commands_;
private:

    void refreshSearch()
    {
        if(!dirty)
            return;

        visible_rows =
        SearchEngine<T>::filter(
            repo.all(),
                                search_text
        );

        dirty = false;
    }

    bool onEvent(Event event)
    {
        if(event == Event::Character('q') ||
            event == Event::Character('Q'))
        {
            screen.ExitLoopClosure()();
            return true;
        }

        if(event == Event::Tab)
        {
            focus =
            focus == Focus::Search
            ? Focus::Table
            : Focus::Search;

            return true;
        }

        if(event == Event::Character('/'))
        {
            focus = Focus::Search;
            return true;
        }

        if(event == Event::Escape)
        {
            focus = Focus::Table;
            return true;
        }

        if(focus == Focus::Search)
        {
            if(event == Event::Backspace)
            {
                if(!search_text.empty())
                {
                    search_text.pop_back();
                    dirty = true;
                    page = 0;
                    selected = 0;
                }

                return true;
            }
            if(event == Event::CtrlZ)
            {
                commands_.undo();

                view_.refresh();

                return true;
            }
            if(event == Event::CtrlY)
            {
                commands_.redo();

                view_.refresh();

                return true;
            }
            if(event.is_character())
            {
                search_text += event.character();
                dirty = true;
                page = 0;
                selected = 0;
                return true;
            }

            return false;
        }

        refreshSearch();

        auto range =
        Paginator::page(
            visible_rows.size(),
                        page
        );

        size_t page_rows =
        range.end - range.start;

        if(event == Event::ArrowDown)
        {
            if(selected + 1 < page_rows)
                selected++;

            return true;
        }

        if(event == Event::ArrowUp)
        {
            if(selected > 0)
                selected--;

            return true;
        }

        if(event == Event::PageDown)
        {
            if(page + 1 <
                Paginator::pages(
                    visible_rows.size()))
            {
                page++;
                selected = 0;
            }

            return true;
        }

        if(event == Event::PageUp)
        {
            if(page > 0)
            {
                page--;
                selected = 0;
            }

            return true;
        }

        if(event == Event::Character('d') ||
            event == Event::Character('D'))
        {
            deleteSelected();
            return true;
        }

        return false;
    }

    commands_.execute(
        std::make_unique<
        DeleteCommand<T>
        >(
            repo,
          view_.currentIndex()
        )
    );

    view_.refresh();

private:

    ScreenInteractive& screen;
    Repository<T>& repo;

    Focus focus =
    Focus::Table;

    std::string search_text;

    size_t page = 0;
    size_t selected = 0;

    bool dirty = true;

    std::vector<size_t> visible_rows;

    Component renderer;
    Component component_;
};
