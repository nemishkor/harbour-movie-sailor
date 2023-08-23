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

class Api : public QObject
{
    Q_OBJECT
public:
    enum WorkerName {
        ConfigurationCountries,
        ConfigurationDetails,
        ConfigurationLanguages,
        Genres,
        WatchMovieProviders,
        SearchCompanies,
        SearchPeople,
    };
    explicit Api(QObject *parent);

    RequestInfo* getRequestInfo(WorkerName name);

    void loadConfigurationCounries();
    void loadConfigurationDetails();
    void loadConfigurationLanguages();
    void loadMovieGenres(const QString &language);
    void loadTVGenres(const QString &language);
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
    void configurationCountriesDone(QByteArray &data);
    void configurationDetailsDone(QByteArray &data);
    void configurationLanguagesDone(QByteArray &data);
    void genresDone(QByteArray &data);
    void watchMovieProvidersDone(QByteArray &data);
    void searchCompaniesDone(QByteArray &data);
    void searchPersonsDone(QByteArray &data);

};

#endif // API_H
