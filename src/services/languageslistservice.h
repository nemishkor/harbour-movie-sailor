#ifndef LANGUAGESLISTSERVICE_H
#define LANGUAGESLISTSERVICE_H

#include <QByteArray>
#include <QDebug>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QVector>

#include "src/api.h"
#include "src/cachekey.h"
#include "src/filecache.h"
#include "src/viewmodels/languageslistmodel.h"
#include "src/system.h"


class LanguagesListService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool initialized READ isInitialized NOTIFY initializedChanged)
public:
    LanguagesListService(System& system, Api &api, FileCache &cache, QObject *parent);

    void initialize();
    LanguagesListModel *getModel();
    bool isInitialized();

private:
    Api &api;
    FileCache &cache;
    CacheKey key;
    LanguagesListModel model;
    bool initialized;

public slots:
    void apiRequestDone(const QByteArray &data);

signals:
    void initializedChanged();
};

#endif // LANGUAGESLISTSERVICE_H
