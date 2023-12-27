#include "keywordsform.h"

KeywordsForm::KeywordsForm(const QString &query, int page) :
    query(query),
    page(page)
{

}

void KeywordsForm::populateQuery(QUrlQuery &urlQuery) const
{
    urlQuery.addQueryItem("query", query);
    urlQuery.addQueryItem("page", QString::number(page));
}

QString KeywordsForm::toString() const
{
    return query + "|" + QString::number(page);
}
