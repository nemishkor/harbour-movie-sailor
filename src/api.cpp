#include "api.h"

Api::Api(QObject *parent) : QObject(parent)
{
    baseUrl = "https://api.themoviedb.org/3/";
    token = "";

    setupWorker(ConfigurationCountries, SIGNAL(configurationCountriesDone(QByteArray &)));
    setupWorker(ConfigurationDetails, SIGNAL(configurationDetailsDone(QByteArray &)));
    setupWorker(ConfigurationLanguages, SIGNAL(configurationLanguagesDone(QByteArray &)));
    setupWorker(DiscoverMovies, SIGNAL(discoverMoviesDone(QByteArray &)));
    setupWorker(Genres, SIGNAL(genresDone(QByteArray &)));
    setupWorker(Keywords, SIGNAL(keywordsDone(QByteArray &)));
    setupWorker(WatchMovieProviders, SIGNAL(watchMovieProvidersDone(QByteArray &)));
    setupWorker(SearchCompanies, SIGNAL(searchCompaniesDone(QByteArray &)));
    setupWorker(SearchPeople, SIGNAL(searchPersonsDone(QByteArray &)));
}

RequestInfo *Api::getRequestInfo(WorkerName name)
{
    return workers[name]->getRequestInfo();
}

void Api::discoverMovies(const DiscoverMovie &form)
{
    QUrl url(baseUrl + "discover/movie");
    QUrlQuery query;
    query.addQueryItem("page", QString::number(form.getPage()));
    url.setQuery(query);

    getWorker(DiscoverMovies)->get(buildRequest(url));
}

void Api::loadConfigurationCounries()
{
    getWorker(ConfigurationCountries)->get(buildRequest(QUrl(baseUrl + "configuration/countries")));
}

void Api::loadConfigurationDetails()
{
    getWorker(ConfigurationDetails)->get(buildRequest(QUrl(baseUrl + "configuration")));
}

void Api::loadConfigurationLanguages()
{
    getWorker(ConfigurationLanguages)->get(buildRequest(QUrl(baseUrl + "configuration/languages")));
}

void Api::loadMovieGenres(const QString &language)
{
    QUrl url(baseUrl + "genre/movie/list");
    QUrlQuery query;
    query.addQueryItem("language", language);
    url.setQuery(query);

    getWorker(Genres)->get(buildRequest(url));
}

void Api::loadTVGenres(const QString &language)
{
    QUrl url(baseUrl + "genre/tv/list");
    QUrlQuery query;
    query.addQueryItem("language", language);
    url.setQuery(query);

    getWorker(Genres)->get(buildRequest(url));
}

void Api::loadKeywords(const QString query, int page)
{
    QUrlQuery urlQuery;
    urlQuery.addQueryItem("query", query);
    urlQuery.addQueryItem("page", QString::number(page));

    QUrl url(baseUrl + "search/keyword");
    url.setQuery(urlQuery);

    getWorker(Keywords)->get(buildRequest(url));
}

void Api::loadWatchMovieProviders(const QString &region)
{
    QUrl url(baseUrl + "watch/providers/movie");

    if (!region.isEmpty()) {
        QUrlQuery query;
        query.addQueryItem("watch_region", region);
        url.setQuery(query);
    }

    getWorker(WatchMovieProviders)->get(buildRequest(url));
}

void Api::loadSearchPersons(const SearchPeopleForm &form)
{
    QUrlQuery urlQuery;
    urlQuery.addQueryItem("query", form.getQuery());
    urlQuery.addQueryItem("include_adult", form.getWithAdult() ? "true" : "false");
    urlQuery.addQueryItem("page", QString::number(form.getPage()));

    if (!form.getLanguage().isEmpty()) {
        urlQuery.addQueryItem("language", form.getLanguage());
    }

    QUrl url(baseUrl + "search/person");
    url.setQuery(urlQuery);

    getWorker(SearchPeople)->get(buildRequest(url));
}

void Api::searchCompanies(const QString &query)
{
    QUrlQuery urlQuery;
    urlQuery.addQueryItem("query", query);
    urlQuery.addQueryItem("page", QString::number(1));

    QUrl url(baseUrl + "search/company");
    url.setQuery(urlQuery);

    getWorker(SearchCompanies)->get(buildRequest(url));
}

QNetworkRequest Api::buildRequest(const QUrl &url)
{
    QNetworkRequest request(url);
    request.setRawHeader(QByteArray("Authorization"), QString("Bearer %1").arg(token).toUtf8());
    request.setRawHeader(QByteArray("accept"), QByteArray("application/json"));

    return request;
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
