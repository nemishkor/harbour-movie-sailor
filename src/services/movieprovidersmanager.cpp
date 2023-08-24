#include "movieprovidersmanager.h"

MovieProvidersManager::MovieProvidersManager(Api &api, FileCache &cache, QObject *parent) :
    QObject(parent),
    api(api),
    cache(cache),
    key("watch-providers", "movie-providers", "1"),
    model(this),
    initialized(false)
{
    connect(&api, &Api::watchMovieProvidersDone, this, &MovieProvidersManager::apiRequestDone);
}

void MovieProvidersManager::initialize(const QString &region)
{
    qDebug() << "initialize movie providers for the region" << region;
    if (key.key != region) {
        key.key = region;
        model.clear();
        initialized = false;
        emit initializedChanged();
    }

    if (region == "") {
        return;
    }

    if (initialized) {
        return;
    }

    if (cache.exists(key)) {
        model.fillFromCache(cache.load(key));
        initialized = true;
        emit initializedChanged();
        return;
    }

    api.loadWatchMovieProviders(region);
}

MovieProvidersListModel *MovieProvidersManager::getModel()
{
    return &model;
}

bool MovieProvidersManager::isInitialized()
{
    return initialized;
}

void MovieProvidersManager::apiRequestDone(const QByteArray &data)
{
    QJsonDocument newJson = model.fillFromAPI(QJsonDocument::fromJson(data));
    cache.save(key, newJson);
    initialized = true;
    emit initializedChanged();
}
