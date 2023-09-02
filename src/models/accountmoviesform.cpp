#include "accountmoviesform.h"

AccountMoviesForm::AccountMoviesForm(QObject *parent) :
    QObject(parent),
    page(1),
    sortBy("created_at.asc"),
    dirty(true)
{

}

int AccountMoviesForm::getPage() const
{
    return page;
}

void AccountMoviesForm::setPage(int newPage)
{
    if (page == newPage)
        return;
    page = newPage;
    emit pageChanged();
}

const QString &AccountMoviesForm::getSortBy() const
{
    return sortBy;
}

void AccountMoviesForm::setSortBy(const QString &newSortBy)
{
    if (sortBy == newSortBy)
        return;
    sortBy = newSortBy;
    emit sortByChanged();
    dirty = true;
}

bool AccountMoviesForm::getDirty() const
{
    return dirty;
}

void AccountMoviesForm::setDirty(bool newDirty)
{
    dirty = newDirty;
}
