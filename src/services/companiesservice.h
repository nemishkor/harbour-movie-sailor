#ifndef COMPANIESSERVICE_H
#define COMPANIESSERVICE_H

#include <QByteArray>
#include <QDebug>
#include <QObject>

#include "src/api.h"
#include "src/cachekey.h"
#include "src/filecache.h"
#include "src/models/form.h"
#include "src/models/searchform.h"
#include "src/viewmodels/filterbycompanieslistmodel.h"
#include "src/viewmodels/companiessearchlistmodel.h"
#include "src/models/requestinfo.h"

class CompaniesService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool initialized READ isInitialized NOTIFY initializedChanged)
    Q_PROPERTY(SearchForm* form READ getForm CONSTANT)
    Q_PROPERTY(CompaniesSearchListModel* list READ getList CONSTANT)
    Q_PROPERTY(RequestInfo* request READ getRequest CONSTANT)

public:
    explicit CompaniesService(Api &api, FileCache &cache, FilterByCompaniesListModel *model, QObject *parent);
    Q_INVOKABLE void search();
    CompaniesSearchListModel *getList();
    bool isInitialized();
    SearchForm *getForm() const;
    RequestInfo *getRequest() const;

private:
    const Api::WorkerName apiWorkerName;
    Api &api;
    RequestInfo *request;
    FileCache &cache;
    CacheKey key;
    FilterByCompaniesListModel *model;
    CompaniesSearchListModel *list;
    SearchForm *form;
    bool initialized;

public slots:
    void apiRequestDone(const QByteArray &data);

signals:
    void initializedChanged();

};

#endif // COMPANIESSERVICE_H
