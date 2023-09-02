#ifndef COMPANIESSERVICE_H
#define COMPANIESSERVICE_H

#include <QByteArray>
#include <QDebug>
#include <QObject>

#include "src/api.h"
#include "src/cachekey.h"
#include "src/filecache.h"
#include "src/viewmodels/filterbycompanieslistmodel.h"
#include "src/viewmodels/companiessearchlistmodel.h"

class CompaniesService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool initialized READ isInitialized NOTIFY initializedChanged)
public:
    explicit CompaniesService(Api &api, FileCache &cache, FilterByCompaniesListModel *model, QObject *parent);
    Q_INVOKABLE void search(const QString &query);
    Q_INVOKABLE void addFromSearch(int id);
    CompaniesSearchListModel *getSearchModel();
    bool isInitialized();

private:
    Api &api;
    FileCache &cache;
    CacheKey key;
    FilterByCompaniesListModel *model;
    CompaniesSearchListModel searchModel;
    bool initialized;

public slots:
    void apiRequestDone(const QByteArray &data);

signals:
    void initializedChanged();

};

#endif // COMPANIESSERVICE_H
