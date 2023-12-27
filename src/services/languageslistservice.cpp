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
    initialize();
}

void LanguagesListService::initialize()
{
    qDebug() << "LanguagesListService: initialize";
    if (initialized) {
        qDebug() << "LanguagesListService: model is initialized already";
        return;
    }

    if (cache.exists(key)) {
        qDebug() << "LanguagesListService: initialize using cache";
        model.fillFromCache(cache.load(key));
        initialized = true;
        emit initializedChanged();
        return;
    }

    qDebug() << "LanguagesListService: initialize using API - start";
    api.getResource(Api::ConfigurationLanguages);
}

FilterByLanguagesListModel *LanguagesListService::getModel()
{
    return &model;
}

bool LanguagesListService::isInitialized()
{
    return initialized;
}

void LanguagesListService::apiRequestDone(const QByteArray &data)
{
    qDebug() << "LanguagesListService: initialize using API - got data";
    QJsonDocument newJson = model.fillFromAPI(QJsonDocument::fromJson(data));
    cache.save(key, newJson);
    initialized = true;
    emit initializedChanged();
    qDebug() << "LanguagesListService: initialize using API - done";
}
