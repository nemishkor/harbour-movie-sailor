#ifndef PERSONSLISTSERVICE_H
#define PERSONSLISTSERVICE_H

#include <QByteArray>
#include <QDebug>
#include <QObject>

#include "src/api.h"
#include "src/cachekey.h"
#include "src/filecache.h"
#include "src/viewmodels/castlistmodel.h"
#include "src/viewmodels/personslistmodel.h"

class PersonsListService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool initialized READ isInitialized NOTIFY initializedChanged)
public:
    PersonsListService(Api &api, FileCache &cache, QObject *parent);

    void initialize(const QString &query, bool includeAdult = true, const QString &language = "", int page = 1);
    PersonsListModel *getModel();
    bool isInitialized();
    CastListModel *getCast();
    Q_INVOKABLE void addSelectedToCastList();

private:
    Api &api;
    FileCache &cache;
    CacheKey key;
    PersonsListModel model;
    CastListModel cast;
    bool initialized;

public slots:
    void apiRequestDone(const QByteArray &data);

signals:
    void initializedChanged();
};

#endif // PERSONSLISTSERVICE_H
