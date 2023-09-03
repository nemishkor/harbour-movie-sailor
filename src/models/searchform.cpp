#include "searchform.h"

SearchForm::SearchForm(QObject *parent) :
    QObject(parent),
    type(Any)
{

}

void SearchForm::reset()
{
    setType(Any);
    setQuery("");
    setPrimaryReleaseYear("");
    setPage(1);
    setFirstAirDateYear("");
    setRegion("");
    setYear("");
}

void SearchForm::populateQuery(QUrlQuery &urlQuery) const
{
    urlQuery.addQueryItem("query", query);
    urlQuery.addQueryItem("page", QString::number(page));

    switch (type) {
    case SearchForm::Any:
        break;
    case SearchForm::Movie:
        urlQuery.addQueryItem("primary_release_year", primaryReleaseYear);
        urlQuery.addQueryItem("region", region);
        urlQuery.addQueryItem("year", year);
        break;
    case SearchForm::Tv:
        urlQuery.addQueryItem("first_air_date_year", firstAirDateYear);
        urlQuery.addQueryItem("year", year);
        break;
    case SearchForm::Person:
        break;
    }
}

QString SearchForm::toString() const
{
    return query + "|" + QString::number(page);
}

bool SearchForm::isValid() const
{
    return !query.isEmpty();
}

SearchForm::MediaType SearchForm::getType() const
{
    return type;
}

void SearchForm::setType(SearchForm::MediaType newType)
{
    if (type == newType)
        return;
    qDebug() << "new type" << newType;
    type = newType;
    emit typeChanged();
    setDirty(true);
}

const QString &SearchForm::getQuery() const
{
    return query;
}

void SearchForm::setQuery(const QString &newQuery)
{
    if (query == newQuery)
        return;
    query = newQuery;
    emit queryChanged();
    setDirty(true);
}

const QString &SearchForm::getPrimaryReleaseYear() const
{
    return primaryReleaseYear;
}

void SearchForm::setPrimaryReleaseYear(const QString &newPrimaryReleaseYear)
{
    if (primaryReleaseYear == newPrimaryReleaseYear)
        return;
    primaryReleaseYear = newPrimaryReleaseYear;
    emit primaryReleaseYearChanged();
    setDirty(true);
}

const QString &SearchForm::getFirstAirDateYear() const
{
    return firstAirDateYear;
}

void SearchForm::setFirstAirDateYear(const QString &newFirstAirDateYear)
{
    if (firstAirDateYear == newFirstAirDateYear)
        return;
    firstAirDateYear = newFirstAirDateYear;
    emit firstAirDateYearChanged();
    setDirty(true);
}

const QString &SearchForm::getRegion() const
{
    return region;
}

void SearchForm::setRegion(const QString &newRegion)
{
    if (region == newRegion)
        return;
    region = newRegion;
    emit regionChanged();
    setDirty(true);
}

const QString &SearchForm::getYear() const
{
    return year;
}

void SearchForm::setYear(const QString &newYear)
{
    if (year == newYear)
        return;
    year = newYear;
    emit yearChanged();
    setDirty(true);
}

int SearchForm::getPage() const
{
    return page;
}

void SearchForm::setPage(int newPage)
{
    if (page == newPage)
        return;
    page = newPage;
    emit pageChanged();
}
