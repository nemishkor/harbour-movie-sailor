#include "app.h"

App::App(QQmlContext *context) :
    QObject(nullptr),
    api(this),
    configurationDetailsManager(api, cache, this),
    companiesService(api, cache, this),
    countriesListService(system, api, cache, this),
    genresMovieService(api, cache, system, this),
    movieProvidersManager(api, cache, this),
    languagesListService(system, api, cache, this),
    personsListService(api, cache, this),
    searchPeopleForm(this)
{
    context->setContextProperty("countriesService", &countriesListService);
    context->setContextProperty("countriesListModel", countriesListService.getModel());
    context->setContextProperty("countriesRequestInfo", api.getRequestInfo(Api::ConfigurationCountries));

    context->setContextProperty("configurationDetailsService", &configurationDetailsManager);
    context->setContextProperty("configurationDetailsModel", configurationDetailsManager.getModel());
    context->setContextProperty("configurationDetailsRequestInfo", api.getRequestInfo(Api::ConfigurationDetails));

    context->setContextProperty("movieProvidersService", &movieProvidersManager);
    context->setContextProperty("movieProvidersListModel", movieProvidersManager.getModel());
    context->setContextProperty("movieProvidersRequestInfo", api.getRequestInfo(Api::WatchMovieProviders));

    context->setContextProperty("languagesService", &languagesListService);
    context->setContextProperty("languagesListModel", languagesListService.getModel());
    context->setContextProperty("languagesRequestInfo", api.getRequestInfo(Api::ConfigurationLanguages));

    context->setContextProperty("companiesService", &companiesService);
    context->setContextProperty("companiesModel", companiesService.getModel());
    context->setContextProperty("companiesSearchModel", companiesService.getSearchModel());
    context->setContextProperty("companiesRequestInfo", api.getRequestInfo(Api::SearchCompanies));

    context->setContextProperty("genresMovieService", &genresMovieService);
    context->setContextProperty("genresMovieModel", genresMovieService.getModel());
    context->setContextProperty("genresRequestInfo", api.getRequestInfo(Api::Genres));

    context->setContextProperty("personsService", &personsListService);
    context->setContextProperty("personsListModel", personsListService.getSearchPersonListModel());
    context->setContextProperty("searchPersonsRequestInfo", api.getRequestInfo(Api::SearchPeople));
    context->setContextProperty("peopleListModel", personsListService.getAnyRoleList());
    context->setContextProperty("castListModel", personsListService.getCastRoleList());
    context->setContextProperty("crewListModel", personsListService.getCrewRoleList());
    context->setContextProperty("searchPeopleForm", &searchPeopleForm);

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

void App::initializePersons()
{
    qDebug() << "initializePersons()";
    personsListService.search(searchPeopleForm);
}
