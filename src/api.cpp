#include "api.h"

Api::Api(QObject *parent) :
    QObject(parent),
    configurationLanguagesWorker(&networkManager, &configurationLanguagesInfo)
{
    baseUrl = "https://api.themoviedb.org/3/";
    token = "";
}

Api::~Api()
{
}

void Api::loadConfigurationLanguages()
{
    configurationLanguagesWorker.get(buildRequest("configuration/languages"));
}

QNetworkRequest Api::buildRequest(const QString &path)
{
    QNetworkRequest request(QUrl(baseUrl + path));
    request.setRawHeader(QByteArray("Authorization"), QString("Bearer %1").arg(token).toUtf8());
    request.setRawHeader(QByteArray("accept"), QByteArray("application/json"));

    return request;
}

RequestInfo &Api::getConfigurationLanguagesInfo()
{
    return configurationLanguagesInfo;
}

const ApiWorker &Api::getConfigurationLanguagesWorker() const
{
    return configurationLanguagesWorker;
}
