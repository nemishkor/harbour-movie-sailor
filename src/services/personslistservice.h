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

    Q_INVOKABLE void addSelectedToCastList();

    void search(const SearchPeopleForm &form);

    SearchPersonListModel *getSearchPersonListModel();
    PeopleListModel *getPeopleListModel();
    PeopleListModel *getCastListModel();
    PeopleListModel *getCrewListModel();
    bool isInitialized();

private:
    Api &api;
    FileCache &cache;
    CacheKey key;
    SearchPersonListModel searchPersonListModel;
    PeopleListModel peopleListModel;
    PeopleListModel castListModel;
    PeopleListModel crewListModel;
    bool initialized;

public slots:
    void apiRequestDone(const QByteArray &data);

signals:
    void initializedChanged();
};

#endif // PERSONSLISTSERVICE_H
