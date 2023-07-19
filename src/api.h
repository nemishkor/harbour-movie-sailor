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

    const ApiWorker &getConfigurationLanguagesWorker() const;

    RequestInfo &getConfigurationLanguagesInfo();

private:
    QNetworkAccessManager networkManager;
    QNetworkRequest buildRequest(const QString &path);
    QString baseUrl;
    QString token;

    RequestInfo configurationLanguagesInfo;
    ApiWorker configurationLanguagesWorker;

};

#endif // API_H
