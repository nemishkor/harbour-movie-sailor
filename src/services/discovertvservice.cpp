#include "discovertvservice.h"

DiscoverTvService::DiscoverTvService(Api &api,
                                     GenresListModel *genres,
                                     QObject *parent) :
    QObject(parent),
    api(api),
    genres(*genres),
    watchProvidersInitialized(true),
    watchProvidersRequestInfo(api.getRequestInfo(Api::WorkerName::WatchTvProviders)),
    request(api.getRequestInfo(Api::WorkerName::DiscoverTv)),
    model(new MediaListModel(this))
{
    connect(&api, &Api::discoverTvDone, this, &DiscoverTvService::searchDone);
    connect(&api, &Api::watchTvProvidersDone, this, &DiscoverTvService::loadWatchProvidersDone);
}

void DiscoverTvService::loadWatchProviders(DiscoverTvForm *tvDiscovery)
{
    this->form = tvDiscovery;
    qDebug() << "DiscoverTvService: initialize providers";
    if (tvDiscovery->getWatchRegion()->getId().isEmpty())
        return;
    qDebug() << "DiscoverTvService: load providers using API - start";
    setWatchProvidersInitialized(false);
    api.getResource(Api::WorkerName::WatchTvProviders, LoadTVWatchProvidersForm(tvDiscovery->getWatchRegion()->getId()));
}

void DiscoverTvService::loadWatchProvidersDone(const QByteArray &data)
{
    qDebug() << "DiscoverTvService: initialize using API - got data";
    if (form != nullptr) {
        form->getProvidersList()->clear();
        form->getProvidersList()->fillFromAPI(QJsonDocument::fromJson(data));
    }
    setWatchProvidersInitialized(true);
    qDebug() << "DiscoverTvService: initialize using API - done";
}

void DiscoverTvService::search(DiscoverTvForm *tvDiscovery)
{
    if (tvDiscovery != nullptr) {
        this->form = tvDiscovery;
    }
    qDebug() << "DiscoverTvService: search";
    setInitialized(false);
    model->clear();
    api.getResource(Api::WorkerName::DiscoverTv, *form);
}

void DiscoverTvService::loadMore()
{
    form->setPage(form->getPage() + 1);
    qDebug() << "DiscoverTvService: load more";
    setInitialized(false);
    api.getResource(Api::WorkerName::DiscoverTv, *form);
}

void DiscoverTvService::searchDone(const QByteArray &data)
{
    qDebug() << "DiscoverTvService: search - got data";
    model->fillFromAPI(genres.getItems(), QJsonDocument::fromJson(data), MediaListItem::TvType);
    setInitialized(true);
    qDebug() << "DiscoverTvService: search - done";
}

DiscoverTvForm *DiscoverTvService::getForm() const
{
    return form;
}

RequestInfo *DiscoverTvService::getRequest() const
{
    return request;
}

MediaListModel *DiscoverTvService::getModel() const
{
    return model;
}

bool DiscoverTvService::getInitialized() const
{
    return initialized;
}

void DiscoverTvService::setInitialized(bool newInitialized)
{
    if (initialized == newInitialized)
        return;
    initialized = newInitialized;
    emit initializedChanged();
}

RequestInfo *DiscoverTvService::getWatchProvidersRequestInfo() const
{
    return watchProvidersRequestInfo;
}

bool DiscoverTvService::getWatchProvidersInitialized() const
{
    return watchProvidersInitialized;
}

void DiscoverTvService::setWatchProvidersInitialized(bool newWatchProvidersInitialized)
{
    if (watchProvidersInitialized == newWatchProvidersInitialized)
        return;
    watchProvidersInitialized = newWatchProvidersInitialized;
    emit watchProvidersInitializedChanged();
}
