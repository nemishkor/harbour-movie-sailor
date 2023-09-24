#include "languageslistservice.h"

LanguagesListService::LanguagesListService(
        System& system,
        Api &api,
        FileCache &cache,
        QObject *parent) :
    QObject(parent),
    api(api),
    cache(cache),
    key("configuration", "languages", "1"),
    model(system, this),
    initialized(false)
{
    connect(&api, &Api::configurationLanguagesDone, this, &LanguagesListService::apiRequestDone);
}

void LanguagesListService::initialize()
{
    if (initialized) {
        qDebug() << "model is initialized already";
        return;
    }

    if (cache.exists(key, "json")) {
        qDebug() << "initialize model using cache";
        model.fillFromCache(cache.load(key));
        initialized = true;
        emit initializedChanged();
        return;
    }

    api.loadConfigurationLanguages();
}

LanguagesListModel *LanguagesListService::getModel()
{
    return &model;
}

bool LanguagesListService::isInitialized()
{
    return initialized;
}

void LanguagesListService::apiRequestDone(const QByteArray &data)
{
    qDebug() << "initialize model using API";
    QJsonDocument newJson = model.fillFromAPI(QJsonDocument::fromJson(data));
    cache.save(key, newJson);
    initialized = true;
    emit initializedChanged();
}
