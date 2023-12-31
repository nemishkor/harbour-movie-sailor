#ifndef TVNETWORKSSERVICE_H
#define TVNETWORKSSERVICE_H

#include <QObject>
#include <QByteArray>
#include <QDataStream>
#include <QDebug>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QProcess>
#include <QSortFilterProxyModel>

#include "src/api.h"
#include "src/cachekey.h"
#include "src/filecache.h"
#include "src/listmodels/tvnetworkslist.h"

class TvNetworksService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(TVNetworksList* model READ getModel CONSTANT)
    Q_PROPERTY(RequestInfo* request READ getRequest CONSTANT)
    Q_PROPERTY(QSortFilterProxyModel* sortFilterModel READ getSortFilterModel CONSTANT)

public:
    TvNetworksService(Api &api, FileCache &cache, QObject *parent);

    Q_INVOKABLE void load();

    RequestInfo *getRequest() const;

    TVNetworksList *getModel() const;

    QSortFilterProxyModel *getSortFilterModel() const;

private:
    Api &api;
    FileCache &cache;
    CacheKey key;
    TVNetworksList *model;
    QSortFilterProxyModel *sortFilterModel;
    RequestInfo *request;
    QString exportsPath;
    QFileInfo actualExportFile;
    const QString exportFileNamePrefix;
    const QString exportFileNameDateFormatSeparator;
    const QString exportFileNameDateFormat;
    const QString exportFileNameFormat;

    QString createFileName();
    void fillModel();

public slots:
    void loadDone(const QByteArray &data);
};

#endif // TVNETWORKSSERVICE_H
