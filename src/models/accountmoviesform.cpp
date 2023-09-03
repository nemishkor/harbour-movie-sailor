#include "accountmoviesform.h"

AccountMoviesForm::AccountMoviesForm(QObject *parent) :
    QObject(parent),
    page(1),
    sortBy("created_at.asc")
{

}

void AccountMoviesForm::populateQuery(QUrlQuery &urlQuery) const
{
    urlQuery.addQueryItem("sort_by", sortBy);
    urlQuery.addQueryItem("page", QString::number(page));
}

QString AccountMoviesForm::toString() const
{
    return sortBy + "|" + QString::number(page);
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
    setDirty(true);
}
