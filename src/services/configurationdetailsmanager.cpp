#include "configurationdetailsmanager.h"

ConfigurationDetailsManager::ConfigurationDetailsManager(Api &api, FileCache &cache, QObject *parent) :
    QObject(parent),
    api(api),
    request(api.getRequestInfo(Api::ConfigurationDetails)),
    cache(cache),
    key("configuration", "details", "1"),
    model(new ConfigurationDetails(this)),
    initialized(false)
{
    connect(&api, &Api::configurationDetailsDone, this, &ConfigurationDetailsManager::apiRequestDone);
}

void ConfigurationDetailsManager::initialize()
{
    qInfo() << "ConfigurationDetailsManager: initialize";
    if (initialized) {
        return;
    }

    if (cache.exists(key)) {
        qDebug() << "ConfigurationDetailsManager: initialize using cache";
        model->fillFromCache(cache.load(key));
        initialized = true;
        emit initializedChanged();
        return;
    }

    qDebug() << "ConfigurationDetailsManager: initialize using API - start";
    api.loadConfigurationDetails();
}

ConfigurationDetails *ConfigurationDetailsManager::getModel()
{
    return model;
}

bool ConfigurationDetailsManager::isInitialized()
{
    return initialized;
}

RequestInfo *ConfigurationDetailsManager::getRequest() const
{
    return request;
}

void ConfigurationDetailsManager::apiRequestDone(const QByteArray &data)
{
    qDebug() << "ConfigurationDetailsManager: initialize using API - got data";
    QJsonDocument newJson = model->fillFromAPI(QJsonDocument::fromJson(data));
    cache.save(key, newJson);
    initialized = true;
    emit initializedChanged();
    qDebug() << "ConfigurationDetailsManager: initialize using API - done";
}

