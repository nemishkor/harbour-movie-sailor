#ifndef API_H
#define API_H

#include <QByteArray>
#include <QDebug>
#include <QObject>
#include <QNetworkRequest>
#include <QString>
#include <QUrl>
#include <QUrlQuery>

#include "apiworker.h"

class Api : public QObject
{
    Q_OBJECT
public:
    explicit Api(QObject *parent = nullptr);

    void loadConfigurationDetails();
    void loadConfigurationLanguages();
    void loadConfigurationCounries();
    void loadWatchMovieProviders(const QString &region);
    void loadSearchPersons(const QString &query, bool includeAdults = true, const QString &language = "", int page = 1);

    ApiWorker &getConfigurationDetailsWorker();
    ApiWorker &getConfigurationLanguagesWorker();
    ApiWorker &getConfigurationCountriesWorker();
    ApiWorker &getWatchMovieProvidersWorker();
    ApiWorker &getSearchPersonsWorker();

private:
    QNetworkAccessManager networkManager;
    QNetworkRequest buildRequest(const QUrl &url);
    QString baseUrl;
    QString token;

    ApiWorker configurationDetailsWorker;
    ApiWorker configurationLanguagesWorker;
    ApiWorker configurationCountriesWorker;
    ApiWorker watchMovieProvidersWorker;
    ApiWorker searchPersonsWorker;

signals:
    void configurationDetailsDone(const QByteArray &data);
    void configurationLanguagesDone(const QByteArray &data);
    void configurationCountriesDone(const QByteArray &data);
    void watchMovieProvidersDone(const QByteArray &data);
    void searchPersonsDone(const QByteArray &data);

};

#endif // API_H
