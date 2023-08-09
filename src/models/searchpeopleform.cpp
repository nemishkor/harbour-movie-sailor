#include "searchpeopleform.h"

SearchPeopleForm::SearchPeopleForm(QObject *parent) :
    QObject(parent),
    query(""),
    withAdult(true),
    language(""),
    page(1)
{

}

const QString &SearchPeopleForm::getQuery() const
{
    return query;
}

void SearchPeopleForm::setQuery(const QString &newQuery)
{
    if (query == newQuery)
        return;
    query = newQuery;
    emit queryChanged();
}

bool SearchPeopleForm::getWithAdult() const
{
    return withAdult;
}

void SearchPeopleForm::setWithAdult(bool newWithAdult)
{
    if (withAdult == newWithAdult)
        return;
    withAdult = newWithAdult;
    emit withAdultChanged();
}

const QString &SearchPeopleForm::getLanguage() const
{
    return language;
}

void SearchPeopleForm::setLanguage(const QString &newLanguage)
{
    if (language == newLanguage)
        return;
    language = newLanguage;
    emit languageChanged();
}

int SearchPeopleForm::getPage() const
{
    return page;
}

void SearchPeopleForm::setPage(int newPage)
{
    if (page == newPage)
        return;
    page = newPage;
    emit pageChanged();
}
