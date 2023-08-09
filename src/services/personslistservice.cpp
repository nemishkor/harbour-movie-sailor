#include "personslistservice.h"

PersonsListService::PersonsListService(Api &api, FileCache &cache, QObject *parent) :
    QObject(parent),
    api(api),
    cache(cache),
    key("search", "persons", "1"),
    searchPersonListModel(this),
    peopleListModel(this),
    castListModel(this),
    crewListModel(this),
    initialized(false)
{
    connect(&api, &Api::searchPersonsDone, this, &PersonsListService::apiRequestDone);
}

void PersonsListService::search(const SearchPeopleForm &form)
{
    QString newKey = form.getQuery() + "|" + (form.getWithAdult() ? "true" : "false") + "|" + form.getLanguage() + "|" + QString::number(form.getPage());
    qDebug() << "initialize search person list with" << newKey;

    if (key.key != newKey) {
        key.key = newKey;
        searchPersonListModel.clear();
        initialized = false;
        emit initializedChanged();
    }

    if (form.getQuery() == "") {
        return;
    }

    if (initialized) {
        return;
    }

    if (cache.exists(key, "json")) {
        searchPersonListModel.fillFromCache(cache.load(key));
        initialized = true;
        emit initializedChanged();
        return;
    }

    api.loadSearchPersons(form);
}

SearchPersonListModel *PersonsListService::getSearchPersonListModel()
{
    return &searchPersonListModel;
}

PeopleListModel *PersonsListService::getPeopleListModel()
{
    return &peopleListModel;
}

PeopleListModel *PersonsListService::getCastListModel()
{
    return &castListModel;
}

PeopleListModel *PersonsListService::getCrewListModel()
{
    return &crewListModel;
}

bool PersonsListService::isInitialized()
{
    return initialized;
}

void PersonsListService::addSelectedToCastList()
{
    const QList<SearchPersonListItem> &persons = searchPersonListModel.getItems();
    for (QList<SearchPersonListItem>::const_iterator it = persons.constBegin(); it != persons.constEnd(); it++) {
        if (!(*it).getChecked())
            continue;
        if ((*it).getRole() == SearchPersonListItem::AnyRole)
            peopleListModel.add((*it));
        if ((*it).getRole() == SearchPersonListItem::CastRole)
            castListModel.add((*it));
        if ((*it).getRole() == SearchPersonListItem::CrewRole)
            crewListModel.add((*it));
    }
    searchPersonListModel.clear();
}

void PersonsListService::apiRequestDone(const QByteArray &data)
{
    QJsonDocument newJson = searchPersonListModel.fillFromAPI(QJsonDocument::fromJson(data));
    cache.save(key, newJson);
    initialized = true;
    emit initializedChanged();
}
