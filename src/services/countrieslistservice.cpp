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
    qDebug() << "CountriesListService: initialize";
    if (initialized) {
        qDebug() << "CountriesListService: model is initialized already";
        return;
    }

    if (cache.exists(key)) {
        qDebug() << "CountriesListService: initialize using cache";
        model.fillFromCache(cache.load(key));
        initialized = true;
        emit initializedChanged();
        return;
    }

    qDebug() << "CountriesListService: initialize using API - start";
    api.getResource(Api::ConfigurationCountries);
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
    qDebug() << "CountriesListService: initialize using API - got data";
    QJsonDocument newJson = model.fillFromAPI(QJsonDocument::fromJson(data));
    cache.save(key, newJson);
    initialized = true;
    emit initializedChanged();
    qDebug() << "CountriesListService: initialize using API - done";
}
