#include "movieprovidersmanager.h"

MovieProvidersManager::MovieProvidersManager(Api &api, FileCache &cache, Settings &settings, MovieProvidersListModel *model, QObject *parent) :
    QObject(parent),
    api(api),
    cache(cache),
    settings(settings),
    key("watch-providers", "movie-providers", "1"),
    model(model),
    initialized(false)
{
    connect(&api, &Api::watchMovieProvidersDone, this, &MovieProvidersManager::apiRequestDone);
}

void MovieProvidersManager::initialize(const QString &region)
{
    QString newKey = settings.getLanguage() + "|" + region;
    qDebug() << "MovieProvidersManager: initialize" << newKey;
    if (key.key != newKey) {
        key.key = newKey;
        model->clear();
        setInitialized(false);
    }

    if (region.isEmpty()) {
        return;
    }

    if (initialized) {
        return;
    }

    if (cache.exists(key)) {
        qDebug() << "MovieProvidersManager: initialize using cache";
        model->fillFromCache(cache.load(key));
        setInitialized(true);
        return;
    }

    qDebug() << "MovieProvidersManager: initialize using API - start";
    api.loadWatchMovieProviders(region);
}

void MovieProvidersManager::setInitialized(bool newInitialized)
{
    if (initialized == newInitialized)
        return;
    initialized = newInitialized;
    emit initializedChanged();
}

bool MovieProvidersManager::isInitialized()
{
    return initialized;
}

void MovieProvidersManager::apiRequestDone(const QByteArray &data)
{
    qDebug() << "MovieProvidersManager: initialize using API - got data";
    QJsonDocument newJson = model->fillFromAPI(QJsonDocument::fromJson(data));
    cache.save(key, newJson);
    setInitialized(true);
    qDebug() << "MovieProvidersManager: initialize using API - done";
}
