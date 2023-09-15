#ifndef MOVIEPROVIDERSMANAGER_H
#define MOVIEPROVIDERSMANAGER_H

#include <QByteArray>
#include <QDebug>
#include <QObject>

#include "src/api.h"
#include "src/cachekey.h"
#include "src/filecache.h"
#include "src/settings.h"
#include "src/viewmodels/movieproviderslistmodel.h"

class MovieProvidersManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool initialized READ isInitialized NOTIFY initializedChanged)
public:
    MovieProvidersManager(Api &api, FileCache &cache, Settings &settings, MovieProvidersListModel *model, QObject *parent);

    void initialize(const QString &region);

    void setInitialized(bool newInitialized);
    bool isInitialized();

private:
    Api &api;
    FileCache &cache;
    Settings &settings;
    CacheKey key;
    MovieProvidersListModel *model;
    bool initialized;

public slots:
    void apiRequestDone(const QByteArray &data);

signals:
    void initializedChanged();
};

#endif // MOVIEPROVIDERSMANAGER_H
