#include "api.h"

Api::Api(class Account *account, Settings &settings, QObject *parent) :
    QObject(parent),
    accountIdEnpointRegexp("^/?account/([^/]+)"),
    account(account),
    settings(settings),
    sensitiveQueryParams({"session_id", "api_key"})
{
    baseUrl = "https://api.themoviedb.org/3/";
    #if defined(TMDB_API_TOKEN)
        token = QString(TMDB_API_TOKEN);
        qDebug() << "Api: token is defined";
    #else
        qCritical() << "TMDB API token is not defined";
    #endif

    qDebug() << "Api: is token exists" << (token.isEmpty() ? "no" : "yes");

    setupWorker(Account, SIGNAL(loadAccountDone(QByteArray &)));
    setupWorker(ConfigurationCountries, SIGNAL(configurationCountriesDone(QByteArray &)));
    setupWorker(ConfigurationDetails, SIGNAL(configurationDetailsDone(QByteArray &)));
    setupWorker(ConfigurationLanguages, SIGNAL(configurationLanguagesDone(QByteArray &)));
    setupWorker(DiscoverMovies, SIGNAL(discoverMoviesDone(QByteArray &)));
    setupWorker(DiscoverTv, SIGNAL(discoverTvDone(QByteArray &)));
    setupWorker(Genres, SIGNAL(genresDone(QByteArray &)));
    setupWorker(Keywords, SIGNAL(keywordsDone(QByteArray &)));
    setupWorker(LoadMovie, SIGNAL(movieDone(QByteArray &)));
    setupWorker(LoadTv, SIGNAL(loadTvDone(QByteArray &)));
    setupWorker(LoadPerson, SIGNAL(loadPersonDone(QByteArray &)));
    setupWorker(WatchMovieProviders, SIGNAL(watchMovieProvidersDone(QByteArray &)));
    setupWorker(WatchTvProviders, SIGNAL(watchTvProvidersDone(QByteArray &)));
    setupWorker(SearchCompanies, SIGNAL(searchCompaniesDone(QByteArray &)));
    setupWorker(SearchPeople, SIGNAL(searchPersonsDone(QByteArray &)));
    setupWorker(RequestRefreshToken, SIGNAL(requestRefreshTokenDone(QByteArray &)));
    setupWorker(CreateSession, SIGNAL(createSessionDone(QByteArray &)));

    setupWorker(ToggleFavoriteMovie, SIGNAL(favoriteDone(QByteArray &)));
    setupWorker(ToggleWatchlistMovie, SIGNAL(toggleWatchlistDone(QByteArray &)));
    setupWorker(AddRatingMovie, SIGNAL(addRatingDone(QByteArray &)));
    setupWorker(RemoveRatingMovie, SIGNAL(removeRatingDone(QByteArray &)));

    setupWorker(ToggleFavoriteTv, SIGNAL(toggleFavoriteTvDone(QByteArray &)));
    setupWorker(ToggleWatchlistTv, SIGNAL(toggleWatchlistTvDone(QByteArray &)));
    setupWorker(AddRatingTv, SIGNAL(addRatingTvDone(QByteArray &)));
    setupWorker(RemoveRatingTv, SIGNAL(removeRatingTvDone(QByteArray &)));

    setupWorker(SearchMedia, SIGNAL(searchMediaDone(QByteArray &)));

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

void Api::loadMovie(int id)
{
    QUrlQuery query;
    query.addQueryItem("language", getLanguage());
    QString appendToResponse = "credits";

    if (!settings.getSessionId().isEmpty()) {
        query.addQueryItem("session_id", settings.getSessionId());
        appendToResponse.append(",account_states");
    }

    query.addQueryItem("append_to_response", appendToResponse);

    getResource(LoadMovie, "movie/" + QString::number(id), query);
}

void Api::loadTv(int id)
{
    QUrlQuery query;
    query.addQueryItem("language", getLanguage());

    if (!settings.getSessionId().isEmpty()) {
        query.addQueryItem("session_id", settings.getSessionId());
        query.addQueryItem("append_to_response", "account_states");
    }

    getResource(LoadTv, "tv/" + QString::number(id), query);
}

void Api::loadPerson(int id, const Form &form)
{
    QUrlQuery query;
    query.addQueryItem("language", getLanguage());
    form.populateQuery(query);
    getResource(LoadPerson, "person/" + QString::number(id), query);
}

void Api::loadMovieGenres()
{
    QUrlQuery query;
    query.addQueryItem("language", getLanguage());

    getResource(Genres, "genre/movie/list", query);
}

void Api::loadTVGenres()
{
    QUrlQuery query;
    query.addQueryItem("language", getLanguage());

    getResource(Genres, "genre/tv/list", query);
}

void Api::createSessionId(const QByteArray &data)
{
    postResource(CreateSession, "authentication/session/new", data);
}

void Api::toggleFavorite(WorkerName workerName, const QString &type, int id, bool newValue)
{
    if (settings.getSessionId().isEmpty() || account->getId() == 0)
        return;

    QString endpoint = "account/" + QString::number(account->getId()) + "/favorite";

    QUrlQuery urlQuery;
    urlQuery.addQueryItem("session_id", settings.getSessionId());

    QJsonObject obj;
    obj.insert("media_type", type);
    obj.insert("media_id", QString::number(id));
    obj.insert("favorite", newValue);

    postResource(workerName, endpoint, urlQuery, obj);
}

void Api::toggleFavorite(const class Movie &movie)
{
    toggleFavorite(ToggleFavoriteMovie, "movie", movie.getId(), !movie.getFavorite());
}

void Api::toggleFavorite(const Tv &tv)
{
    toggleFavorite(ToggleFavoriteTv, "tv", tv.getId(), !tv.getFavorite());
}

void Api::toggleWatchlist(WorkerName workerName, const QString &type, int id, bool newValue)
{
    if (settings.getSessionId().isEmpty() || account->getId() == 0)
        return;

    QString endpoint = "account/" + QString::number(account->getId()) + "/watchlist";

    QUrlQuery urlQuery;
    urlQuery.addQueryItem("session_id", settings.getSessionId());

    QJsonObject obj;
    obj.insert("media_type", type);
    obj.insert("media_id", QString::number(id));
    obj.insert("watchlist", newValue);

    postResource(workerName, endpoint, urlQuery, obj);
}

void Api::toggleWatchlist(const class Movie &movie)
{
    toggleWatchlist(ToggleWatchlistMovie, "movie", movie.getId(), !movie.getWatchlist());
}

void Api::toggleWatchlist(const Tv &tv)
{
    toggleWatchlist(ToggleWatchlistTv, "tv", tv.getId(), !tv.getWatchlist());
}

void Api::addRating(WorkerName workerName, const QString &type, int id, int newValue)
{
    if (settings.getSessionId().isEmpty() || account->getId() == 0)
        return;

    QString endpoint = type + "/" + QString::number(id) + "/rating";

    QUrlQuery urlQuery;
    urlQuery.addQueryItem("session_id", settings.getSessionId());

    QJsonObject obj;
    obj.insert("value", (double)newValue);

    postResource(workerName, endpoint, urlQuery, obj);
}

void Api::addRating(const class Movie &movie, int rating)
{
    addRating(AddRatingMovie, "movie", movie.getId(), rating);
}

void Api::addRating(const Tv &tv, int rating)
{
    addRating(AddRatingTv, "tv", tv.getId(), rating);
}

void Api::removeRating(WorkerName workerName, const QString &type, int id)
{
    if (settings.getSessionId().isEmpty() || account->getId() == 0)
        return;

    QString endpoint = type + "/" + QString::number(id) + "/rating";

    QUrlQuery urlQuery;
    urlQuery.addQueryItem("session_id", settings.getSessionId());

    deleteResource(workerName, endpoint, urlQuery);
}

void Api::removeRating(const class Movie &movie)
{
    removeRating(RemoveRatingMovie, "movie", movie.getId());
}

void Api::removeRating(const Tv &tv)
{
    removeRating(RemoveRatingTv, "tv", tv.getId());
}

void Api::getResource(WorkerName workerName, const Form &form)
{
    QString endpoint;
    QUrlQuery query;
    bool ok = true;

    getEndpointAndQuery(workerName, endpoint, query, &ok);

    if (!ok) {
        qWarning() << "request is not Ok to send";
        return;
    }

    form.populateQuery(query);

    getResource(workerName, endpoint, query);
}

void Api::searchMedia(WorkerName workerName, const SearchForm &form)
{
    QString endpoint;
    QUrlQuery query;

    switch (form.getType()) {
    case SearchForm::Any:
        endpoint = "search/multi";
        break;
    case SearchForm::Movie:
        endpoint = "search/movie";
        break;
    case SearchForm::Tv:
        endpoint = "search/tv";
        break;
    case SearchForm::Person:
        endpoint = "search/person";
        break;
    }

    query.addQueryItem("language", getLanguage());
    query.addQueryItem("include_adult", getIncludeAdult());

    form.populateQuery(query);

    getResource(workerName, endpoint, query);
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
    return workers[name];
}

QString Api::getLanguage() const
{
    if (!account->getLanguage().isEmpty())
        return account->getLanguage();
    if (!settings.getLanguage().isEmpty())
        return settings.getLanguage();
    return "en-US";
}

QString Api::getIncludeAdult() const
{
    if (account->getId() != 0)
        return account->getIncludeAdult() ? "true" : "false";
    return "false";
}

void Api::getEndpointAndQuery(WorkerName workerName, QString &endpoint, QUrlQuery &query, bool *ok)
{
    switch (workerName) {
    case Api::Account:
        if (settings.getSessionId().isEmpty()) {
            *ok = false;
            return;
        }
        endpoint = "account/account_id";
        query.addQueryItem("session_id", settings.getSessionId());
        break;
    case ConfigurationCountries:
        endpoint = "configuration/countries";
        query.addQueryItem("language", getLanguage());
        break;
    case ConfigurationDetails:
        endpoint = "configuration";
        break;
    case ConfigurationLanguages:
        endpoint = "configuration/languages";
        break;
    case Api::DiscoverMovies:
        endpoint = "discover/movie";
        query.addQueryItem("language", getLanguage());
        break;
    case Api::DiscoverTv:
        endpoint = "discover/tv";
        query.addQueryItem("language", getLanguage());
        break;
    case Api::FavoriteMovies:
        endpoint = "account/" + QString::number(account->getId()) + "/favorite/movies";
        query.addQueryItem("language", getLanguage());
        query.addQueryItem("session_id", settings.getSessionId());
        break;
    case Api::FavoriteTv:
        endpoint = "account/" + QString::number(account->getId()) + "/favorite/tv";
        query.addQueryItem("language", getLanguage());
        query.addQueryItem("session_id", settings.getSessionId());
        break;
    case Keywords:
        endpoint = "search/keyword";
        break;
    case Api::RatedMovies:
        endpoint = "account/" + QString::number(account->getId()) + "/rated/movies";
        query.addQueryItem("language", getLanguage());
        query.addQueryItem("session_id", settings.getSessionId());
        break;
    case Api::RatedTv:
        endpoint = "account/" + QString::number(account->getId()) + "/rated/tv";
        query.addQueryItem("language", getLanguage());
        query.addQueryItem("session_id", settings.getSessionId());
        break;
    case RequestRefreshToken:
        endpoint = "authentication/token/new";
        break;
    case SearchPeople:
        endpoint = "search/person";
        query.addQueryItem("language", getLanguage());
        break;
    case WatchMovieProviders:
        endpoint = "watch/providers/movie";
        query.addQueryItem("language", getLanguage());
        break;
    case Api::WatchTvProviders:
        endpoint = "watch/providers/tv";
        query.addQueryItem("language", getLanguage());
        break;
    case Api::WatchlistMovies:
        endpoint = "account/" + QString::number(account->getId()) + "/watchlist/movies";
        query.addQueryItem("language", getLanguage());
        query.addQueryItem("session_id", settings.getSessionId());
        break;
    case Api::WatchlistTv:
        endpoint = "account/" + QString::number(account->getId()) + "/watchlist/tv";
        query.addQueryItem("language", getLanguage());
        query.addQueryItem("session_id", settings.getSessionId());
        break;
    case Api::SearchCompanies:
        endpoint = "search/company";
        query.addQueryItem("language", getLanguage());
        query.addQueryItem("session_id", settings.getSessionId());
        break;
    default:
        qWarning() << "API: Invalid worker name was passed to the getResource method:" << workerName;
        *ok = false;
        return;
    }
}

void Api::getResource(WorkerName workerName, const QString &endpoint)
{
    log(workerName, "GET", endpoint);
    getWorker(workerName)->get(buildRequest(endpoint));
}

void Api::getResource(WorkerName workerName, const QString &endpoint, const QUrlQuery &query)
{
    log(workerName, "GET", endpoint, query);
    getWorker(workerName)->get(buildRequest(endpoint, query));
}

void Api::postResource(WorkerName workerName, const QString &endpoint, const QByteArray &data)
{
    log(workerName, "POST", endpoint);
    getWorker(workerName)->post(buildRequest(endpoint), data);
}

void Api::postResource(WorkerName workerName, const QString &endpoint, const QUrlQuery &query, const QJsonObject &data)
{
    log(workerName, "POST", endpoint, query);
    getWorker(workerName)->post(buildRequest(endpoint, query), QJsonDocument(data).toJson());
}

void Api::postResource(WorkerName workerName, const QString &endpoint, const QUrlQuery &query, const QByteArray &data)
{
    log(workerName, "POST", endpoint, query);
    getWorker(workerName)->post(buildRequest(endpoint, query), data);
}

void Api::deleteResource(WorkerName workerName, const QString &endpoint, const QUrlQuery &query)
{
    log(workerName, "DELETE", endpoint, query);
    getWorker(workerName)->deleteResource(buildRequest(endpoint, query));
}

void Api::log(WorkerName workerName, const QString &method, const QString &endpoint)
{
    qDebug() << "Api:" << workerName << method << "request to" << buildUrl(filterEndpoint(endpoint)).toString();
}

void Api::log(WorkerName workerName, const QString &method, const QString &endpoint, const QUrlQuery &query)
{
    QUrlQuery filteredQuery;
    QList<QPair<QString, QString>> queryItems = query.queryItems();
    for (QList<QPair<QString, QString>>::const_iterator it = queryItems.constBegin(); it != queryItems.constEnd(); it++) {
        if (sensitiveQueryParams.contains(it->first)) {
            filteredQuery.addQueryItem(it->first, "***");
        } else {
            filteredQuery.addQueryItem(it->first, it->second);
        }
    }

    qDebug() << "Api:" << workerName << method << "request to" << buildUrl(filterEndpoint(endpoint), filteredQuery).toString();
}

QString Api::filterEndpoint(const QString &endpoint) const
{
    QRegularExpressionMatch accountIdmatch = accountIdEnpointRegexp.match(endpoint);
    QString filteredEndpoint = endpoint;

    if (accountIdmatch.hasMatch()) {
        QString accountId = accountIdmatch.captured(1);
        if (accountId != "account_id") {
            int accountIdStart = accountIdmatch.capturedStart(1);
            int accountIdEnd = accountIdmatch.capturedEnd(1);
            filteredEndpoint.replace(accountIdStart, accountIdEnd - accountIdStart, "******");
        }
    }

    return filteredEndpoint;
}
