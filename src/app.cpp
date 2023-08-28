#include "app.h"

App::App(QQmlContext *context) :
    QObject(nullptr),
    api(this),
    configurationDetailsManager(api, cache, this),
    countriesListService(system, api, cache, this),
    discoverMovieService(api, cache, system, this),
    languagesListService(system, api, cache, this),
    searchPeopleForm(this)
{
    context->setContextProperty("countriesService", &countriesListService);
    context->setContextProperty("countriesListModel", countriesListService.getModel());
    context->setContextProperty("countriesRequestInfo", api.getRequestInfo(Api::ConfigurationCountries));

    context->setContextProperty("configurationDetailsService", &configurationDetailsManager);
    context->setContextProperty("configurationDetailsModel", configurationDetailsManager.getModel());
    context->setContextProperty("configurationDetailsRequestInfo", api.getRequestInfo(Api::ConfigurationDetails));

    // Begin discovery movie
    context->setContextProperty("discoverMovieService", &discoverMovieService);
    context->setContextProperty("discoverMovieRequestInfo", api.getRequestInfo(Api::DiscoverMovies));

    context->setContextProperty("genresMovieService", discoverMovieService.getGenresService());
    context->setContextProperty("genresMovieModel", discoverMovieService.getForm()->getGenres());
    context->setContextProperty("genresRequestInfo", api.getRequestInfo(Api::Genres));

    context->setContextProperty("movieProvidersService", discoverMovieService.getMovieProviders());
    context->setContextProperty("movieProvidersListModel", discoverMovieService.getForm()->getProviders());
    context->setContextProperty("movieProvidersRequestInfo", api.getRequestInfo(Api::WatchMovieProviders));

    context->setContextProperty("searchPersonsRequestInfo", api.getRequestInfo(Api::SearchPeople));
    context->setContextProperty("peopleListModel", discoverMovieService.getForm()->getAnyRoleList());
    context->setContextProperty("castListModel", discoverMovieService.getForm()->getCastRoleList());
    context->setContextProperty("crewListModel", discoverMovieService.getForm()->getCrewRoleList());
    context->setContextProperty("searchPeopleForm", &searchPeopleForm);

    context->setContextProperty("companiesModel", discoverMovieService.getForm()->getCompanies());
    context->setContextProperty("companiesSearchModel", discoverMovieService.getCompaniesService()->getSearchModel());
    context->setContextProperty("companiesRequestInfo", api.getRequestInfo(Api::SearchCompanies));

    context->setContextProperty("keywordsService", discoverMovieService.getKeywordsService());
    context->setContextProperty("keywordsModel", discoverMovieService.getForm()->getKeywords());
    context->setContextProperty("keywordsSearchModel", discoverMovieService.getKeywordsService()->getSearchModel());
    context->setContextProperty("keywordsRequestInfo", api.getRequestInfo(Api::Keywords));
    // End discovery movie

    context->setContextProperty("languagesService", &languagesListService);
    context->setContextProperty("languagesListModel", languagesListService.getModel());
    context->setContextProperty("languagesRequestInfo", api.getRequestInfo(Api::ConfigurationLanguages));

    context->setContextProperty("app", this);
    qDebug() << "app build is done";
}

void App::initializeConfigurationDetails()
{
    qDebug() << "initializeConfigurationDetails()";
    configurationDetailsManager.initialize();
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
    discoverMovieService.getPersonsListService()->search(searchPeopleForm);
}
