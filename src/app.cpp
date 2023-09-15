#include "app.h"

App::App(QQmlContext *context) :
    QObject(nullptr),
    menu(0),
    cache(new FileCache(this)),
    account(new Account(this)),
    settings(new Settings(system, this)),
    api(account, *settings, this),
    genresService(api, *cache, *settings, this),
    configurationDetailsManager(api, *cache, this),
    movieService(new MovieService(api, system, this)),
    tvService(api, this),
    personService(new PersonService(api, this)),
    countriesListService(system, api, *cache, this),
    discoverMovieService(api, *cache, *settings, *movieService, genresService.getModel(), this),
    languagesListService(system, api, *cache, this),
    accountService(new AccountService(account, api, *settings, genresService.getModel(), *movieService, tvService, this)),
    searchService(new SearchService(api, *movieService, tvService, *personService, genresService.getModel(), this))
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

    context->setContextProperty("genresMovieService", &genresService);
    context->setContextProperty("genresMovieModel", discoverMovieService.getForm()->getGenres());
    context->setContextProperty("genresRequestInfo", api.getRequestInfo(Api::Genres));

    context->setContextProperty("movieProvidersService", discoverMovieService.getMovieProviders());
    context->setContextProperty("movieProvidersListModel", discoverMovieService.getForm()->getProviders());
    context->setContextProperty("movieProvidersRequestInfo", api.getRequestInfo(Api::WatchMovieProviders));

    context->setContextProperty("searchPersonsRequestInfo", api.getRequestInfo(Api::SearchPeople));
    context->setContextProperty("peopleListModel", discoverMovieService.getForm()->getAnyRoleList());
    context->setContextProperty("castListModel", discoverMovieService.getForm()->getCastRoleList());
    context->setContextProperty("crewListModel", discoverMovieService.getForm()->getCrewRoleList());

    context->setContextProperty("companiesModel", discoverMovieService.getForm()->getCompanies());
    context->setContextProperty("companiesSearchModel", discoverMovieService.getCompaniesService()->getList());
    context->setContextProperty("companiesRequestInfo", api.getRequestInfo(Api::SearchCompanies));

    context->setContextProperty("keywordsService", discoverMovieService.getKeywordsService());
    context->setContextProperty("keywordsModel", discoverMovieService.getForm()->getKeywords());
    context->setContextProperty("keywordsSearchModel", discoverMovieService.getKeywordsService()->getSearchModel());
    context->setContextProperty("keywordsRequestInfo", api.getRequestInfo(Api::Keywords));
    // End discovery movie

    context->setContextProperty("languagesService", &languagesListService);
    context->setContextProperty("languagesListModel", languagesListService.getModel());
    context->setContextProperty("languagesRequestInfo", api.getRequestInfo(Api::ConfigurationLanguages));

    context->setContextProperty("requestRefreshTokenRequestInfo", api.getRequestInfo(Api::RequestRefreshToken));
    context->setContextProperty("createSessionRequestInfo", api.getRequestInfo(Api::CreateSession));
    context->setContextProperty("accountRequestInfo", api.getRequestInfo(Api::Account));

    context->setContextProperty("tvService", &tvService);
    context->setContextProperty("favoriteRequestInfo", api.getRequestInfo(Api::ToggleFavoriteMovie));
    context->setContextProperty("watchlistRequestInfo", api.getRequestInfo(Api::ToggleWatchlistMovie));
    context->setContextProperty("ratingRequestInfo", api.getRequestInfo(Api::AddRatingMovie));
    context->setContextProperty("removeRatingRequestInfo", api.getRequestInfo(Api::RemoveRatingMovie));

    context->setContextProperty("favoriteMoviesRequestInfo", api.getRequestInfo(Api::FavoriteMovies));
    context->setContextProperty("favoriteTvRequestInfo", api.getRequestInfo(Api::FavoriteTv));
    context->setContextProperty("ratedMoviesRequestInfo", api.getRequestInfo(Api::RatedMovies));
    context->setContextProperty("ratedTvRequestInfo", api.getRequestInfo(Api::RatedTv));
    context->setContextProperty("watchlistMoviesRequestInfo", api.getRequestInfo(Api::WatchlistMovies));
    context->setContextProperty("watchlistTvRequestInfo", api.getRequestInfo(Api::WatchlistTv));

    context->setContextProperty("app", this);

    qInfo() << "app build is done";

    connect(&languagesListService, &LanguagesListService::initializedChanged, this, &App::validateContentLanguage);

    configurationDetailsManager.initialize();
    genresService.initialize();
}

void App::initializeCountries()
{
    qDebug() << "initializeCountries()";
    countriesListService.initialize();
}

Settings *App::getSettings() const
{
    return settings;
}

int App::getMenu() const
{
    return menu;
}

void App::setMenu(int newMenu)
{
    if (menu == newMenu)
        return;
    menu = newMenu;
    emit menuChanged();
}

AccountService *App::getAccountService() const
{
    return accountService;
}

Account *App::getAccount() const
{
    return account;
}

SearchService *App::getSearchService() const
{
    return searchService;
}

FileCache *App::getCache() const
{
    return cache;
}

MovieService *App::getMovieService() const
{
    return movieService;
}

PersonService *App::getPersonService() const
{
    return personService;
}

void App::validateContentLanguage()
{
    if (!languagesListService.isInitialized() || system.getLanguage().isEmpty()) {
        return;
    }

    if (!languagesListService.getModel()->getItems().contains(FilterByLanguageListItem(system.getLanguage()))) {
        qDebug() << "Unable to find system language" << system.getLanguage() << "in the list of available languages. Revert to the default";
        settings->setLanguage("en-US");
    }
}
