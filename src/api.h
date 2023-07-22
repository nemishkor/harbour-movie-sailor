#ifndef API_H
#define API_H

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
    ~Api();

    void loadConfigurationLanguages();
    void loadConfigurationCounries();

    ApiWorker &getConfigurationLanguagesWorker();
    ApiWorker &getConfigurationCountriesWorker();

private:
    QNetworkAccessManager networkManager;
    QNetworkRequest buildRequest(const QString &path);
    QString baseUrl;
    QString token;

    ApiWorker configurationLanguagesWorker;
    ApiWorker configurationCountriesWorker;

};

#endif // API_H
