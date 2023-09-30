#include "apiworker.h"

ApiWorker::ApiWorker(QNetworkAccessManager* networkManager, QObject *parent) :
    QObject(parent),
    networkManager(networkManager),
    requestInfo(this)
{

}

ApiWorker::~ApiWorker()
{
    if (reply) {
        reply->deleteLater();
    }
}

void ApiWorker::get(const QNetworkRequest &request)
{
    if (reply != nullptr && requestInfo.getState() == RequestInfo::Running) {
        qDebug() << "ApiWorker: abort previous request";
        reply->abort();
    }

    requestInfo.start();

    reply = networkManager->get(request);
    connect(reply, &QNetworkReply::downloadProgress, this, &ApiWorker::downloadProgress);
    connect(reply, static_cast<void(QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &ApiWorker::error);
    connect(reply, &QNetworkReply::finished, this, &ApiWorker::finished);
}

void ApiWorker::deleteResource(const QNetworkRequest &request)
{
    if (reply != nullptr && requestInfo.getState() == RequestInfo::Running) {
        qDebug() << "ApiWorker: Abort previous request";
        reply->abort();
    }

    requestInfo.start();

    reply = networkManager->deleteResource(request);
    connect(reply, &QNetworkReply::downloadProgress, this, &ApiWorker::downloadProgress);
    connect(reply, static_cast<void(QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &ApiWorker::error);
    connect(reply, &QNetworkReply::finished, this, &ApiWorker::finished);
}

RequestInfo *ApiWorker::getRequestInfo()
{
    return &requestInfo;
}

void ApiWorker::post(const QNetworkRequest &request, const QByteArray &data)
{
    if (reply != nullptr && requestInfo.getState() == RequestInfo::Running) {
        qDebug() << "ApiWorker: Abort previous request";
        reply->abort();
    }

    requestInfo.start();

    reply = networkManager->post(request, data);
    connect(reply, &QNetworkReply::downloadProgress, this, &ApiWorker::downloadProgress);
    connect(reply, static_cast<void(QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &ApiWorker::error);
    connect(reply, &QNetworkReply::finished, this, &ApiWorker::finished);
}

void ApiWorker::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    requestInfo.setProgress((int) (bytesTotal / bytesReceived));
}

void ApiWorker::error(QNetworkReply::NetworkError code)
{
    qWarning() << "ApiWorker: failed request";
    if (code == QNetworkReply::OperationCanceledError) {
        requestInfo.setState(RequestInfo::StandBy);
        return;
    }

    requestInfo.setState(RequestInfo::Failed);

    if (code == QNetworkReply::TimeoutError) {
        requestInfo.setError("Opps. Timeout error");
    } else if (code == QNetworkReply::SslHandshakeFailedError) {
        requestInfo.setError("Opps. SSL error");
    } else if (code == QNetworkReply::TemporaryNetworkFailureError || code == QNetworkReply::NetworkSessionFailedError) {
        requestInfo.setError("The connection was broken due to disconnection from the network. Please, check your internet connection");
    } else if (code == QNetworkReply::BackgroundRequestNotAllowedError) {
        requestInfo.setError("The background request is not currently allowed due to platform policy");
    } else if (code == QNetworkReply::AuthenticationRequiredError) {
        requestInfo.setError("Opps. Authentication failed. Missing API token or the token is invalid");
    } else {
        qWarning() << "ApiWorker: failed request with unknown error code" << code;
        requestInfo.setError("Opps. Something went wrong. Failed request to the server");
    }

    reply->deleteLater();
}

void ApiWorker::finished()
{
    if (reply->error() != QNetworkReply::NoError) {
        qWarning() << "ApiWorker: finished request with error";
        return;
    }

    qWarning() << "ApiWorker: finished request without error";
    requestInfo.setState(RequestInfo::Success);
    QByteArray data(reply->readAll());
    reply->deleteLater();
    emit done(data);
}
