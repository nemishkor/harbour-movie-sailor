#include "companiesservice.h"

CompaniesService::CompaniesService(Api &api, FileCache &cache, QObject *parent) :
    QObject(parent),
    api(api),
    cache(cache),
    key("search", "company", "1"),
    model(this),
    searchModel(model, this)
{
    connect(&api, &Api::searchCompaniesDone, this, &CompaniesService::apiRequestDone);
}

void CompaniesService::search(const QString &query)
{
    qDebug() << "search companies";
    if (key.key != query) {
        key.key = query;
        searchModel.clear();
        initialized = false;
        emit initializedChanged();
    }

    if (query == "") {
        qDebug() << "search companies query is empty";
        return;
    }

    if (initialized) {
        return;
    }

    if (cache.exists(key)) {
        qDebug() << "load companies from cache for the query" << query;
        searchModel.fillFromCache(cache.load(key));
        initialized = true;
        emit initializedChanged();
        return;
    }

    qDebug() << "search companies API call";
    api.searchCompanies(query);
}

void CompaniesService::addFromSearch(int id)
{
    Company item = searchModel.findById(id);
    qDebug() << "found item" << item.getId();
    if (item.getId() != -1) {
        model.add(item);
        searchModel.removeOneById(item.getId());
    }
}

CompaniesListModel *CompaniesService::getModel()
{
    return &model;
}

CompaniesSearchListModel *CompaniesService::getSearchModel()
{
    return &searchModel;
}

bool CompaniesService::isInitialized()
{
    return initialized;
}

void CompaniesService::apiRequestDone(const QByteArray &data)
{
    qDebug() << "search companies API request done";
    QJsonDocument newJson = searchModel.fillFromAPI(QJsonDocument::fromJson(data));
    cache.save(key, newJson);
    initialized = true;
    emit initializedChanged();
}
