#pragma once

#include <string>

#include "irepository.hpp"
#include "row_view.hpp"
#include "search.hpp"
#include "paginator.hpp"

template<typename T>
class ViewModel
{
public:

    explicit ViewModel(
        IRepository<T>& repo)
    :
    repo_(repo),
    rows_(repo)
    {
        refresh();
    }

    //---------------- Search ----------------

    void setSearch(
        const std::string& text)
    {
        if(search_ == text)
            return;

        search_ = text;

        page_ = 0;
        selected_ = 0;

        refresh();
    }

    const std::string&
    search() const
    {
        return search_;
    }

    //---------------- Refresh ----------------

    void refresh()
    {
        rows_ =
        SearchEngine<T>::filter(
            repo_,
            search_
        );

        normalize();
    }

    //---------------- Navigation ----------------

    void up()
    {
        if(selected_ > 0)
            --selected_;
    }

    void down()
    {
        if(selected_ + 1 < pageRows())
            ++selected_;
    }

    void pageUp()
    {
        if(page_ > 0)
        {
            --page_;
            selected_ = 0;
        }
    }

    void pageDown()
    {
        if(page_ + 1 < pages())
        {
            ++page_;
            selected_ = 0;
        }
    }

    //---------------- Data ----------------

    const RowView<T>&
    rows() const
    {
        return rows_;
    }

    size_t selectedRow() const
    {
        return selected_;
    }

    size_t page() const
    {
        return page_;
    }

    size_t pages() const
    {
        return Paginator::pages(
            rows_.size()
        );
    }

    PageRange currentPage() const
    {
        return
        Paginator::page(
            rows_.size(),
                        page_
        );
    }

    size_t currentIndex() const
    {
        return rows_.index(
            page_ * Paginator::PageSize
            + selected_
        );
    }

    T& current()
    {
        return repo_.at(
            currentIndex()
        );
    }

    const T& current() const
    {
        return repo_.at(
            currentIndex()
        );
    }

    bool empty() const
    {
        return rows_.empty();
    }

private:

    void normalize()
    {
        if(page_ >= pages())
            page_ = pages() - 1;

        if(selected_ >= pageRows())
            selected_ = 0;
    }

    size_t pageRows() const
    {
        auto r = currentPage();

        return r.end - r.start;
    }

private:

    IRepository<T>& repo_;

    RowView<T> rows_;

    std::string search_;

    size_t page_ = 0;

    size_t selected_ = 0;
};
