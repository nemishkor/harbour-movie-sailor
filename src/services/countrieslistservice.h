#ifndef COUNTRIESLISTSERVICE_H
#define COUNTRIESLISTSERVICE_H

#include <QByteArray>
#include <QDebug>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include "src/api.h"
#include "src/cachekey.h"
#include "src/filecache.h"
#include "src/viewmodels/configurationlistmodel.h"
#include "src/system.h"

class CountriesListService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool initialized READ isInitialized NOTIFY initializedChanged)
public:
    CountriesListService(System &system, Api &api, FileCache &cache, QObject *parent);

    void initialize();
    ConfigurationListModel *getModel();
    bool isInitialized();

private:
    Api &api;
    FileCache &cache;
    CacheKey key;
    ConfigurationListModel model;
    bool initialized;

public slots:
    void apiRequestDone(const QByteArray &data);

signals:
    void initializedChanged();
};

#endif // COUNTRIESLISTSERVICE_H
