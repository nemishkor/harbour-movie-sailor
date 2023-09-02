#include "api.h"

Api::Api(class Account *account, Settings &settings, QObject *parent) :
    QObject(parent),
    account(account),
    settings(settings)
{
    baseUrl = "https://api.themoviedb.org/3/";
    token = "";

    setupWorker(Account, SIGNAL(loadAccountDone(QByteArray &)));
    setupWorker(ConfigurationCountries, SIGNAL(configurationCountriesDone(QByteArray &)));
    setupWorker(ConfigurationDetails, SIGNAL(configurationDetailsDone(QByteArray &)));
    setupWorker(ConfigurationLanguages, SIGNAL(configurationLanguagesDone(QByteArray &)));
    setupWorker(DiscoverMovies, SIGNAL(discoverMoviesDone(QByteArray &)));
    setupWorker(Genres, SIGNAL(genresDone(QByteArray &)));
    setupWorker(Keywords, SIGNAL(keywordsDone(QByteArray &)));
    setupWorker(LoadMovie, SIGNAL(movieDone(QByteArray &)));
    setupWorker(WatchMovieProviders, SIGNAL(watchMovieProvidersDone(QByteArray &)));
    setupWorker(SearchCompanies, SIGNAL(searchCompaniesDone(QByteArray &)));
    setupWorker(SearchPeople, SIGNAL(searchPersonsDone(QByteArray &)));
    setupWorker(RequestRefreshToken, SIGNAL(requestRefreshTokenDone(QByteArray &)));
    setupWorker(CreateSession, SIGNAL(createSessionDone(QByteArray &)));
    setupWorker(Favorite, SIGNAL(favoriteDone(QByteArray &)));
    setupWorker(Watchlist, SIGNAL(toggleWatchlistDone(QByteArray &)));
    setupWorker(AddRating, SIGNAL(addRatingDone(QByteArray &)));
    setupWorker(RemoveRating, SIGNAL(removeRatingDone(QByteArray &)));

    setupWorker(FavoriteMovies, SIGNAL(favoriteMoviesDone(QByteArray &)));
    setupWorker(FavoriteTv, SIGNAL(favoriteTvDone(QByteArray &)));
    setupWorker(RatedMovies, SIGNAL(ratedMoviesDone(QByteArray &)));
    setupWorker(RatedTv, SIGNAL(ratedTvDone(QByteArray &)));
    setupWorker(WatchlistMovies, SIGNAL(watchlistMoviesDone(QByteArray &)));
    setupWorker(WatchlistTv, SIGNAL(watchlistTvDone(QByteArray &)));
}

RequestInfo *Api::getRequestInfo(WorkerName name)
{
    return workers[name]->getRequestInfo();
}

void Api::discoverMovies(const DiscoverMovie &form)
{
    QUrlQuery query;

    query.addQueryItem("language", settings.getLanguage());

    query.addQueryItem("page", QString::number(form.getPage()));
    query.addQueryItem("sort_by", form.getSortBy() + "." + form.getOrder());

    QString ids = form.getGenres()->toQueryString();

    if (!ids.isEmpty()) {
        query.addQueryItem("with_genres", ids);
    }

    ids = form.getAnyRoleList()->toQueryString();

    if (!ids.isEmpty()) {
        query.addQueryItem("with_people", ids);
    }

    ids = form.getCastRoleList()->toQueryString();

    if (!ids.isEmpty()) {
        query.addQueryItem("with_cast", ids);
    }

    ids = form.getCrewRoleList()->toQueryString();

    if (!ids.isEmpty()) {
        query.addQueryItem("with_crew", ids);
    }

    ids = form.getCompanies()->toQueryString();

    if (!ids.isEmpty()) {
        query.addQueryItem("with_companies", ids);
    }

    ids = form.getKeywords()->toQueryString();

    if (!ids.isEmpty()) {
        query.addQueryItem("with_keywords", ids);
    }

    if (!form.getWatchRegion().isEmpty()) {
        ids = form.getProviders()->toQueryString();
        if (!ids.isEmpty()) {
            query.addQueryItem("with_watch_providers", ids);
            query.addQueryItem("watch_region", form.getWatchRegion());
        }
    }

    if (form.getRegion()->getId().isEmpty()) {
        if (form.getPrimaryReleaseYear().isEmpty()) {
            if (!form.getPrimaryReleaseDateGte().isEmpty()) {
                query.addQueryItem("primary_release_date.gte", form.getPrimaryReleaseDateGte());
            }
            if (!form.getPrimaryReleaseDateLte().isEmpty()) {
                query.addQueryItem("primary_release_date.lte", form.getPrimaryReleaseDateLte());
            }
        } else {
            query.addQueryItem("primary_release_year", form.getPrimaryReleaseYear());
        }
    } else {
        if (!form.getPrimaryReleaseDateGte().isEmpty()) {
            query.addQueryItem("release_date.gte", form.getPrimaryReleaseDateGte());
        }
        if (!form.getPrimaryReleaseDateLte().isEmpty()) {
            query.addQueryItem("release_date.lte", form.getPrimaryReleaseDateLte());
        }
    }

    if (form.getVoteAverageGte() > 0.0) {
        query.addQueryItem("vote_average.gte", QString::number(form.getVoteAverageGte()));
    }

    if (form.getVoteAverageLte() < 10.0) {
        query.addQueryItem("vote_average.lte", QString::number(form.getVoteAverageLte()));
    }

    if (form.getVoteCountGte() > 0) {
        query.addQueryItem("vote_count.gte", QString::number(form.getVoteCountGte()));
    }

    if (!form.getOriginCountry()->getId().isEmpty()) {
        query.addQueryItem("with_origin_country", form.getOriginCountry()->getId());
    }

    if (!form.getOriginLanguage()->getId().isEmpty()) {
        query.addQueryItem("with_original_language", form.getOriginLanguage()->getId());
    }

    query.addQueryItem("include_video", form.getIncludeVideo() ? "true" : "false");
    query.addQueryItem("include_adult", form.getIncludeAdult() ? "true" : "false");

    getWorker(DiscoverMovies)->get(buildRequest(buildUrl("discover/movie", query)));
}

void Api::loadConfigurationCounries()
{
    QUrlQuery query;
    query.addQueryItem("language", settings.getLanguage());

    getWorker(ConfigurationCountries)->get(buildRequest("configuration/countries", query));
}

void Api::loadConfigurationDetails()
{
    getWorker(ConfigurationDetails)->get(buildRequest(buildUrl("configuration")));
}

void Api::loadConfigurationLanguages()
{
    getWorker(ConfigurationLanguages)->get(buildRequest(QUrl(baseUrl + "configuration/languages")));
}

void Api::loadMovie(int id)
{
    QUrlQuery query;
    query.addQueryItem("language", settings.getLanguage());

    if (!settings.getSessionId().isEmpty()) {
        query.addQueryItem("session_id", settings.getSessionId());
        query.addQueryItem("append_to_response", "account_states");
    }

    getWorker(LoadMovie)->get(buildRequest("movie/" + QString::number(id), query));
}

void Api::loadMovieGenres()
{
    QUrlQuery query;
    query.addQueryItem("language", settings.getLanguage());

    getWorker(Genres)->get(buildRequest("genre/movie/list", query));
}

void Api::loadTVGenres()
{
    QUrlQuery query;
    query.addQueryItem("language", settings.getLanguage());

    getWorker(Genres)->get(buildRequest("genre/tv/list", query));
}

void Api::loadKeywords(const QString query, int page)
{
    QUrlQuery urlQuery;
    urlQuery.addQueryItem("query", query);
    urlQuery.addQueryItem("page", QString::number(page));

    getWorker(Keywords)->get(buildRequest("search/keyword", urlQuery));
}

void Api::loadWatchMovieProviders(const QString &region)
{
    QUrlQuery query;
    query.addQueryItem("language", settings.getLanguage());

    if (!region.isEmpty()) {
        query.addQueryItem("watch_region", region);
    }

    getWorker(WatchMovieProviders)->get(buildRequest("watch/providers/movie", query));
}

void Api::loadSearchPersons(const SearchPeopleForm &form)
{
    QUrlQuery urlQuery;

    urlQuery.addQueryItem("language", settings.getLanguage());

    urlQuery.addQueryItem("query", form.getQuery());
    urlQuery.addQueryItem("include_adult", form.getWithAdult() ? "true" : "false");
    urlQuery.addQueryItem("page", QString::number(form.getPage()));

    getWorker(SearchPeople)->get(buildRequest("search/person", urlQuery));
}

void Api::searchCompanies(const QString &query)
{
    QUrlQuery urlQuery;
    urlQuery.addQueryItem("query", query);
    urlQuery.addQueryItem("page", QString::number(1));

    getWorker(SearchCompanies)->get(buildRequest("search/company", urlQuery));
}

void Api::requestRefreshToken()
{
    getWorker(RequestRefreshToken)->get(buildRequest("authentication/token/new"));
}

void Api::createSessionId(const QByteArray &data)
{
    getWorker(CreateSession)->post(buildRequest("authentication/session/new"), data);
}

void Api::loadAccount()
{
    if (settings.getSessionId().isEmpty())
        return;

    QUrlQuery urlQuery;
    urlQuery.addQueryItem("session_id", settings.getSessionId());

    getWorker(Account)->get(buildRequest("account/account_id", urlQuery));
}

void Api::toggleFavorite(const class Movie &movie)
{
    if (settings.getSessionId().isEmpty() || account->getId() == 0)
        return;

    QUrlQuery urlQuery;
    urlQuery.addQueryItem("session_id", settings.getSessionId());

    QNetworkRequest request = buildRequest("account/" + QString::number(account->getId()) + "/favorite", urlQuery);

    QJsonObject obj;
    obj.insert("media_type", "movie");
    obj.insert("media_id", QString::number(movie.getId()));
    obj.insert("favorite", !movie.getFavorite());

    getWorker(Favorite)->post(request, QJsonDocument(obj).toJson());
}

void Api::toggleWatchlist(const class Movie &movie)
{
    if (settings.getSessionId().isEmpty() || account->getId() == 0)
        return;

    QUrlQuery urlQuery;
    urlQuery.addQueryItem("session_id", settings.getSessionId());

    QNetworkRequest request = buildRequest("account/" + QString::number(account->getId()) + "/watchlist", urlQuery);

    QJsonObject obj;
    obj.insert("media_type", "movie");
    obj.insert("media_id", QString::number(movie.getId()));
    obj.insert("watchlist", !movie.getWatchlist());

    getWorker(Watchlist)->post(request, QJsonDocument(obj).toJson());
}

void Api::addRating(const class Movie &movie, int rating)
{
    if (settings.getSessionId().isEmpty() || account->getId() == 0)
        return;

    QUrlQuery urlQuery;
    urlQuery.addQueryItem("session_id", settings.getSessionId());

    QNetworkRequest request = buildRequest("movie/" + QString::number(movie.getId()) + "/rating", urlQuery);

    QJsonObject obj;
    qDebug() << "value rating" << (double)rating;
    obj.insert("value", (double)rating);

    getWorker(AddRating)->post(request, QJsonDocument(obj).toJson());
}

void Api::removeRating(const class Movie &movie)
{
    if (settings.getSessionId().isEmpty() || account->getId() == 0)
        return;

    QUrlQuery urlQuery;
    urlQuery.addQueryItem("session_id", settings.getSessionId());

    QNetworkRequest request = buildRequest("movie/" + QString::number(movie.getId()) + "/rating", urlQuery);

    getWorker(RemoveRating)->deleteResource(request);
}

void Api::loadAccountMediaList(WorkerName workerName, const AccountMoviesForm &form)
{
    QString endpoint = "account/" + QString::number(account->getId());
    switch (workerName) {
    case Api::FavoriteMovies:
        endpoint.append("/favorite/movies");
        break;
    case Api::FavoriteTv:
        endpoint.append("/favorite/tv");
        break;
    case Api::RatedMovies:
        endpoint.append("/rated/movies");
        break;
    case Api::RatedTv:
        endpoint.append("/rated/tv");
        break;
    case Api::WatchlistMovies:
        endpoint.append("/watchlist/movies");
        break;
    case Api::WatchlistTv:
        endpoint.append("/watchlist/tv");
        break;
    default:
        qWarning() << "Invalid warker name was passed to the loadAccountMediaList method";
        return;
    }
    getWorker(workerName)->get(buildRequest(endpoint, buildFromForm(form)));
}

QUrl Api::buildUrl(const QString &url, const QUrlQuery &query)
{
    QUrl urlObj = buildUrl(url);
    urlObj.setQuery(query);
    return urlObj;
}

QUrl Api::buildUrl(const QString &url)
{
    return QUrl(baseUrl + url);
}

QNetworkRequest Api::buildRequest(const QUrl &url)
{
    QNetworkRequest request(url);
    request.setRawHeader(QByteArray("Authorization"), QString("Bearer %1").arg(token).toUtf8());
    request.setRawHeader(QByteArray("accept"), QByteArray("application/json"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    return request;
}

QNetworkRequest Api::buildRequest(const QString &endpoint)
{
    return buildRequest(buildUrl(endpoint));
}

QNetworkRequest Api::buildRequest(const QString &endpoint, const QUrlQuery &query)
{
    return buildRequest(buildUrl(endpoint, query));
}

void Api::setupWorker(WorkerName name, const char *method)
{
    ApiWorker* worker = new ApiWorker(&networkManager, this);
    workers.insert(name, worker);
    connect(worker, SIGNAL(done(QByteArray &)), this, method);
}

ApiWorker *Api::getWorker(WorkerName name) const
{
    qDebug() << "worker" << name;
    return workers[name];
}

QUrlQuery Api::buildFromForm(const AccountMoviesForm &form)
{
    QUrlQuery query;
    query.addQueryItem("language", settings.getLanguage());
    query.addQueryItem("page", QString::number(form.getPage()));
    query.addQueryItem("sort_by", form.getSortBy());
    query.addQueryItem("session_id", settings.getSessionId());

    return query;
}
