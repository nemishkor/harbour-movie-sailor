#include "app.h"

App::App(QQmlContext *context, QObject *parent) :
    QObject(parent),
    api(this),
    configurationDetailsManager(api, cache, this),
    movieProvidersManager(api, cache, this),
    languagesListService(system, api, cache, this),
    countriesListService(system, api, cache, this)
{
    context->setContextProperty("configurationDetailsService", &configurationDetailsManager);
    context->setContextProperty("configurationDetailsModel", configurationDetailsManager.getModel());
    context->setContextProperty("configurationDetailsRequestInfo", api.getConfigurationDetailsWorker().getRequestInfo());

    context->setContextProperty("movieProvidersService", &movieProvidersManager);
    context->setContextProperty("movieProvidersListModel", movieProvidersManager.getModel());
    context->setContextProperty("movieProvidersRequestInfo", api.getWatchMovieProvidersWorker().getRequestInfo());

    context->setContextProperty("languagesService", &languagesListService);
    context->setContextProperty("languagesListModel", languagesListService.getModel());
    context->setContextProperty("languagesRequestInfo", api.getConfigurationLanguagesWorker().getRequestInfo());

    context->setContextProperty("countriesService", &countriesListService);
    context->setContextProperty("countriesListModel", countriesListService.getModel());
    context->setContextProperty("countriesRequestInfo", api.getConfigurationCountriesWorker().getRequestInfo());

    context->setContextProperty("app", this);
}

void App::initializeConfigurationDetails()
{
    qDebug() << "initializeConfigurationDetails()";
    configurationDetailsManager.initialize();
}

void App::initializeMovieProviders(const QString &region)
{
    qDebug() << "initializeMovieProviders()";
    movieProvidersManager.initialize(region);
}

void App::initializeLanguages()
{
    qDebug() << "initializeLanguages()";
    languagesListService.initialize();
}

void App::initializeCountries()
{
    qDebug() << "initializeCountries()";
    countriesListService.initialize();
}
