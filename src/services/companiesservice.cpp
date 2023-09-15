#include "companiesservice.h"

CompaniesService::CompaniesService(Api &api, FileCache &cache, FilterByCompaniesListModel *model, QObject *parent) :
    QObject(parent),
    apiWorkerName(Api::WorkerName::SearchCompanies),
    api(api),
    request(api.getRequestInfo(apiWorkerName)),
    cache(cache),
    key("search", "company", "1"),
    model(model),
    list(new CompaniesSearchListModel(*this->model, this)),
    form(new SearchForm(this))
{
    connect(&api, &Api::searchCompaniesDone, this, &CompaniesService::apiRequestDone);
}

void CompaniesService::search()
{
    qDebug() << "CompaniesService: search";
    if (form->isDirty()) {
        key.key = form->toString();
        list->clear();
        initialized = false;
        emit initializedChanged();
    }

    if (!form->isValid()) {
        qDebug() << "CompaniesService: form is invalid";
        return;
    }

    if (initialized) {
        return;
    }

    if (cache.exists(key)) {
        list->fillFromCache(cache.load(key));
        initialized = true;
        emit initializedChanged();
        qDebug() << "CompaniesService: search using cache";
        return;
    }

    qDebug() << "CompaniesService: search using API - start";
    api.getResource(apiWorkerName, *form);
}

CompaniesSearchListModel *CompaniesService::getList()
{
    return list;
}

bool CompaniesService::isInitialized()
{
    return initialized;
}

SearchForm *CompaniesService::getForm() const
{
    return form;
}

RequestInfo *CompaniesService::getRequest() const
{
    return request;
}

void CompaniesService::apiRequestDone(const QByteArray &data)
{
    qDebug() << "CompaniesService: search using API - got data";
    QJsonDocument newJson = list->fillFromAPI(QJsonDocument::fromJson(data));
    cache.save(key, newJson);
    initialized = true;
    emit initializedChanged();
    form->setDirty(false);
    qDebug() << "CompaniesService: search using API - done";
}
