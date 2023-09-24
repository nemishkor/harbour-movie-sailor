#include "api.h"

Api::Api(QObject *parent) :
    QObject(parent),
    configurationDetailsWorker(&networkManager),
    configurationLanguagesWorker(&networkManager),
    configurationCountriesWorker(&networkManager),
    watchMovieProvidersWorker(&networkManager)
{
    baseUrl = "https://api.themoviedb.org/3/";
    token = "";

    connect(&configurationDetailsWorker, &ApiWorker::done, this, &Api::configurationDetailsDone);
    connect(&configurationLanguagesWorker, &ApiWorker::done, this, &Api::configurationLanguagesDone);
    connect(&configurationCountriesWorker, &ApiWorker::done, this, &Api::configurationCountriesDone);
    connect(&watchMovieProvidersWorker, &ApiWorker::done, this, &Api::watchMovieProvidersDone);
}

void Api::loadConfigurationDetails()
{
    qDebug() << "loadConfigurationDetails()";
    configurationDetailsWorker.get(buildRequest(QUrl(baseUrl + "configuration")));
}

void Api::loadConfigurationLanguages()
{
    qDebug() << "loadConfigurationLanguages()";
    configurationLanguagesWorker.get(buildRequest(QUrl(baseUrl + "configuration/languages")));
}

void Api::loadConfigurationCounries()
{
    qDebug() << "loadConfigurationCounries()";
    configurationCountriesWorker.get(buildRequest(QUrl(baseUrl + "configuration/countries")));
}

void Api::loadWatchMovieProviders(const QString &region)
{
    qDebug() << "loadWatchMovieProviders()";
    QUrl url(baseUrl + "watch/providers/movie");

    if (!region.isEmpty()) {
        QUrlQuery query;
        query.addQueryItem("watch_region", region);
        url.setQuery(query);
    }

    watchMovieProvidersWorker.get(buildRequest(url));
}

ApiWorker &Api::getConfigurationDetailsWorker()
{
    return configurationDetailsWorker;
}

ApiWorker &Api::getConfigurationCountriesWorker()
{
    return configurationCountriesWorker;
}

ApiWorker &Api::getConfigurationLanguagesWorker()
{
    return configurationLanguagesWorker;
}

QNetworkRequest Api::buildRequest(const QUrl &url)
{
    QNetworkRequest request(url);
    request.setRawHeader(QByteArray("Authorization"), QString("Bearer %1").arg(token).toUtf8());
    request.setRawHeader(QByteArray("accept"), QByteArray("application/json"));

    return request;
}

ApiWorker &Api::getWatchMovieProvidersWorker()
{
    return watchMovieProvidersWorker;
}
