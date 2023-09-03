#ifndef PERSONSLISTSERVICE_H
#define PERSONSLISTSERVICE_H

#include <QByteArray>
#include <QDebug>
#include <QObject>

#include "src/api.h"
#include "src/cachekey.h"
#include "src/filecache.h"
#include "src/models/searchpeopleform.h"
#include "src/viewmodels/searchpeoplelistmodel.h"
#include "src/viewmodels/searchpersonlistmodel.h"

class PersonsListService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool initialized READ isInitialized NOTIFY initializedChanged)
    Q_PROPERTY(SearchPersonListModel * searchPersonListModel READ getSearchPersonListModel CONSTANT)

public:
    PersonsListService(
            Api &api,
            FileCache &cache,
            Settings &settings,
            SearchPeopleListModel *anyRoleList,
            SearchPeopleListModel *castRoleList,
            SearchPeopleListModel *crewRoleList,
            QObject *parent);

    Q_INVOKABLE void select(int id);
    Q_INVOKABLE void remove(int id);
    Q_INVOKABLE void search();

    SearchPersonListModel *getSearchPersonListModel();

    void setInitialized(bool newInitialized);
    bool isInitialized();

    SearchPeopleForm *getForm() const;

private:
    Api &api;
    FileCache &cache;
    Settings &settings;
    CacheKey key;
    SearchPeopleForm *form;
    SearchPersonListModel *searchPersonListModel;
    SearchPeopleListModel *anyRoleList;
    SearchPeopleListModel *castRoleList;
    SearchPeopleListModel *crewRoleList;
    bool initialized;

    Q_PROPERTY(SearchPeopleForm * form READ getForm CONSTANT)

public slots:
    void apiRequestDone(const QByteArray &data);

signals:
    void initializedChanged();
};

#endif // PERSONSLISTSERVICE_H
