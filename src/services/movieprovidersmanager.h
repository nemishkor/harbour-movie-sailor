#ifndef MOVIEPROVIDERSMANAGER_H
#define MOVIEPROVIDERSMANAGER_H

#include <QByteArray>
#include <QDebug>
#include <QObject>

#include "src/api.h"
#include "src/cachekey.h"
#include "src/filecache.h"
#include "src/viewmodels/movieproviderslistmodel.h"

class MovieProvidersManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool initialized READ isInitialized NOTIFY initializedChanged)
public:
    explicit MovieProvidersManager(Api &api, FileCache &cache, MovieProvidersListModel *model, QObject *parent);

    void initialize(const QString &region);
    bool isInitialized();

private:
    Api &api;
    FileCache &cache;
    CacheKey key;
    MovieProvidersListModel *model;
    bool initialized;

public slots:
    void apiRequestDone(const QByteArray &data);

signals:
    void initializedChanged();
};

#endif // MOVIEPROVIDERSMANAGER_H
