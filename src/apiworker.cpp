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
    qDebug() << "GET request to" << request.url().toString();
    requestInfo.setError("");
    requestInfo.setState(RequestInfo::Running);
    requestInfo.setProgress(0);

    reply = networkManager->get(request);
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
    qDebug() << "POST request to" << request.url().toString();
    requestInfo.setError("");
    requestInfo.setState(RequestInfo::Running);
    requestInfo.setProgress(0);

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
    } else {
        requestInfo.setError("Opps. Something went wrong. Failed request to the server");
    }

    reply->deleteLater();
}

void ApiWorker::finished()
{
    if (reply->error() != QNetworkReply::NoError) {
        return;
    }

    requestInfo.setState(RequestInfo::Success);
    QByteArray data(reply->readAll());
    qDebug() << "Got response data from API" << data;
    reply->deleteLater();
    emit done(data);
}
