#include "personslistservice.h"

PersonsListService::PersonsListService(Api &api, FileCache &cache, QObject *parent) :
    QObject(parent),
    api(api),
    cache(cache),
    key("search", "persons", "1"),
    searchPersonListModel(this),
    anyRoleList(this),
    castRoleList(this),
    crewRoleList(this),
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

    if (form.getQuery().isEmpty() || initialized) {
        return;
    }

    if (cache.exists(key)) {
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

PeopleListModel *PersonsListService::getAnyRoleList()
{
    return &anyRoleList;
}

PeopleListModel *PersonsListService::getCastRoleList()
{
    return &castRoleList;
}

PeopleListModel *PersonsListService::getCrewRoleList()
{
    return &crewRoleList;
}

bool PersonsListService::isInitialized()
{
    return initialized;
}

void PersonsListService::select(int id)
{
    qDebug() << "select the person" << id;
    const QList<SearchPersonListItem> &persons = searchPersonListModel.getItems();
    for (QList<SearchPersonListItem>::const_iterator it = persons.constBegin(); it != persons.constEnd(); it++) {
        if (id == it->getId()) {
            qDebug() << "found a person to select in search list";
            qDebug() << "role" << it->getRole();
            if (it->getRole() == SearchPersonListItem::AnyRole) {
                anyRoleList.add(*it);
                castRoleList.remove(id);
                crewRoleList.remove(id);
                return;
            }
            if (it->getRole() == SearchPersonListItem::CastRole) {
                anyRoleList.remove(id);
                castRoleList.add(*it);
                crewRoleList.remove(id);
                return;
            }
            if (it->getRole() == SearchPersonListItem::CrewRole) {
                anyRoleList.remove(id);
                castRoleList.remove(id);
                crewRoleList.add(*it);
                return;
            }
            return;
        }
    }
}

void PersonsListService::remove(int id)
{
    qDebug() << "remove the person" << id;
    if (anyRoleList.getIds().contains(id))
        anyRoleList.remove(id);
    else if (castRoleList.getIds().contains(id))
        castRoleList.remove(id);
    else if (crewRoleList.getIds().contains(id))
        crewRoleList.remove(id);
    searchPersonListModel.resetRole(id);
}

void PersonsListService::apiRequestDone(const QByteArray &data)
{
    QJsonDocument apiJson = QJsonDocument::fromJson(data);
    QMap<SearchPersonListItem::PersonRole, QList<int>> selectedPeoplePerRole;
    selectedPeoplePerRole.insert(SearchPersonListItem::AnyRole, anyRoleList.getIds());
    selectedPeoplePerRole.insert(SearchPersonListItem::CastRole, castRoleList.getIds());
    selectedPeoplePerRole.insert(SearchPersonListItem::CrewRole, crewRoleList.getIds());
    QJsonDocument newJson = searchPersonListModel.fillFromAPI(apiJson, selectedPeoplePerRole);
    cache.save(key, newJson);
    initialized = true;
    emit initializedChanged();
}
