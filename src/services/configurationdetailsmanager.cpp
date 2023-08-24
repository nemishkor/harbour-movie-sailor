#include "configurationdetailsmanager.h"

ConfigurationDetailsManager::ConfigurationDetailsManager(Api &api, FileCache &cache, QObject *parent) :
    QObject(parent),
    api(api),
    cache(cache),
    key("configuration", "details", "1"),
    model(this),
    initialized(false)
{
    connect(&api, &Api::configurationDetailsDone, this, &ConfigurationDetailsManager::apiRequestDone);
}

void ConfigurationDetailsManager::initialize()
{
    if (initialized) {
        return;
    }

    if (cache.exists(key)) {
        model.fillFromCache(cache.load(key));
        initialized = true;
        emit initializedChanged();
        return;
    }

    api.loadConfigurationDetails();
}

ConfigurationDetails *ConfigurationDetailsManager::getModel()
{
    return &model;
}

bool ConfigurationDetailsManager::isInitialized()
{
    return initialized;
}

void ConfigurationDetailsManager::apiRequestDone(const QByteArray &data)
{
    QJsonDocument newJson = model.fillFromAPI(QJsonDocument::fromJson(data));
    cache.save(key, newJson);
    initialized = true;
    emit initializedChanged();
}

