#include "countrieslistservice.h"

CountriesListService::CountriesListService(
        System &system,
        Api &api,
        FileCache &cache,
        QObject *parent) :
    QObject(parent),
    api(api),
    cache(cache),
    key("configuration", "countries", "1"),
    model(system, this),
    initialized(false)

{
    connect(&api, &Api::configurationCountriesDone, this, &CountriesListService::apiRequestDone);
}

void CountriesListService::initialize()
{
    if (initialized) {
        qDebug() << "model is initialized already";
        return;
    }

    if (cache.exists(key)) {
        qDebug() << "initialize model using cache";
        model.fillFromCache(cache.load(key));
        initialized = true;
        emit initializedChanged();
        return;
    }

    api.loadConfigurationCounries();
}

ConfigurationListModel *CountriesListService::getModel()
{
    return &model;
}

bool CountriesListService::isInitialized()
{
    return initialized;
}

void CountriesListService::apiRequestDone(const QByteArray &data)
{
    qDebug() << "initialize model using API";
    QJsonDocument newJson = model.fillFromAPI(QJsonDocument::fromJson(data));
    cache.save(key, newJson);
    initialized = true;
    emit initializedChanged();
}
