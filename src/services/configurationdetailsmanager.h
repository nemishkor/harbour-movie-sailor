#ifndef CONFIGURATIONDETAILSMANAGER_H
#define CONFIGURATIONDETAILSMANAGER_H

#include <QByteArray>
#include <QObject>

#include "src/api.h"
#include "src/cachekey.h"
#include "src/filecache.h"
#include "src/models/configurationdetails.h"

class ConfigurationDetailsManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool initialized READ isInitialized NOTIFY initializedChanged)
    Q_PROPERTY(RequestInfo* request READ getRequest CONSTANT)
    Q_PROPERTY(ConfigurationDetails* model READ getModel CONSTANT)

public:
    ConfigurationDetailsManager(Api &api, FileCache &cache, QObject *parent);

    void initialize();
    ConfigurationDetails *getModel();
    bool isInitialized();
    RequestInfo *getRequest() const;

private:
    Api &api;
    RequestInfo *request;
    FileCache &cache;
    CacheKey key;
    ConfigurationDetails *model;
    bool initialized;

public slots:
    void apiRequestDone(const QByteArray &data);

signals:
    void initializedChanged();

};

#endif // CONFIGURATIONDETAILSMANAGER_H
