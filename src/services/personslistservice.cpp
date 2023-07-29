#include "personslistservice.h"

PersonsListService::PersonsListService(Api &api, FileCache &cache, QObject *parent) :
    QObject(parent),
    api(api),
    cache(cache),
    key("search", "persons", "1"),
    model(this),
    cast(this),
    initialized(false)
{
    connect(&api, &Api::searchPersonsDone, this, &PersonsListService::apiRequestDone);
}

void PersonsListService::initialize(const QString &query, bool includeAdult, const QString &language, int page)
{
    QString newKey = query + "|" + (includeAdult ? "true" : "false") + "|" + language + "|" + QString::number(page);
    qDebug() << "initialize persons list:" << newKey;

    if (key.key != newKey) {
        key.key = newKey;
        model.clear();
        initialized = false;
        emit initializedChanged();
    }

    if (query == "") {
        return;
    }

    if (initialized) {
        return;
    }

    if (cache.exists(key, "json")) {
        model.fillFromCache(cache.load(key));
        initialized = true;
        emit initializedChanged();
        return;
    }

    api.loadSearchPersons(query, includeAdult, language, page);
}

PersonsListModel *PersonsListService::getModel()
{
    return &model;
}

bool PersonsListService::isInitialized()
{
    return initialized;
}

CastListModel *PersonsListService::getCast()
{
    return &cast;
}

void PersonsListService::addSelectedToCastList()
{
    const QList<PersonListItem> &persons = model.getItems();
    for (QList<PersonListItem>::const_iterator it = persons.constBegin(); it != persons.constEnd(); it++) {
        if ((*it).getChecked()) {
            cast.add((*it));
        }
    }
}

void PersonsListService::apiRequestDone(const QByteArray &data)
{
    QJsonDocument newJson = model.fillFromAPI(QJsonDocument::fromJson(data));
    cache.save(key, newJson);
    initialized = true;
    emit initializedChanged();
}
