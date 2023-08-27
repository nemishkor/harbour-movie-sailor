#ifndef API_H
#define API_H

#include <QByteArray>
#include <QDebug>
#include <QObject>
#include <QMap>
#include <QMetaMethod>
#include <QNetworkRequest>
#include <QString>
#include <QUrl>
#include <QUrlQuery>

#include "apiworker.h"
#include "src/models/searchpeopleform.h"
#include "src/models/discovermovie.h"

class Api : public QObject
{
    Q_OBJECT
public:
    enum WorkerName {
        ConfigurationCountries,
        ConfigurationDetails,
        ConfigurationLanguages,
        DiscoverMovies,
        Genres,
        Keywords,
        WatchMovieProviders,
        SearchCompanies,
        SearchPeople,
    };
    explicit Api(QObject *parent);

    RequestInfo* getRequestInfo(WorkerName name);

    void discoverMovies(const DiscoverMovie &form);
    void loadConfigurationCounries();
    void loadConfigurationDetails();
    void loadConfigurationLanguages();
    void loadMovieGenres(const QString &language);
    void loadTVGenres(const QString &language);
    void loadKeywords(const QString query, int page);
    void loadWatchMovieProviders(const QString &region);
    void loadSearchPersons(const SearchPeopleForm &form);
    void searchCompanies(const QString &query);

private:
    QNetworkAccessManager networkManager;
    QNetworkRequest buildRequest(const QUrl &url);
    QString baseUrl;
    QString token;

    QMap<WorkerName, ApiWorker*> workers;
    void setupWorker(WorkerName name, const char *method);
    ApiWorker* getWorker(WorkerName name) const;

signals:
    void configurationCountriesDone(QByteArray &);
    void configurationDetailsDone(QByteArray &);
    void configurationLanguagesDone(QByteArray &);
    void discoverMoviesDone(QByteArray &);
    void genresDone(QByteArray &);
    void keywordsDone(QByteArray &);
    void watchMovieProvidersDone(QByteArray &);
    void searchCompaniesDone(QByteArray &);
    void searchPersonsDone(QByteArray &);

};

#endif // API_H
