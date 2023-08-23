#ifndef PERSONSLISTSERVICE_H
#define PERSONSLISTSERVICE_H

#include <QByteArray>
#include <QDebug>
#include <QObject>

#include "src/api.h"
#include "src/cachekey.h"
#include "src/filecache.h"
#include "src/models/searchpeopleform.h"
#include "src/viewmodels/peoplelistmodel.h"
#include "src/viewmodels/searchpersonlistmodel.h"

class PersonsListService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool initialized READ isInitialized NOTIFY initializedChanged)
public:
    PersonsListService(Api &api, FileCache &cache, QObject *parent);

    Q_INVOKABLE void select(int id);
    Q_INVOKABLE void remove(int id);

    void search(const SearchPeopleForm &form);

    SearchPersonListModel *getSearchPersonListModel();
    PeopleListModel *getAnyRoleList();
    PeopleListModel *getCastRoleList();
    PeopleListModel *getCrewRoleList();
    bool isInitialized();

private:
    Api &api;
    FileCache &cache;
    CacheKey key;
    SearchPersonListModel searchPersonListModel;
    PeopleListModel anyRoleList;
    PeopleListModel castRoleList;
    PeopleListModel crewRoleList;
    bool initialized;

public slots:
    void apiRequestDone(const QByteArray &data);

signals:
    void initializedChanged();
};

#endif // PERSONSLISTSERVICE_H
