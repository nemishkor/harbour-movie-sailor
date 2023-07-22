#ifndef APIWORKER_H
#define APIWORKER_H

#include <QByteArray>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QString>
#include <QUrl>
#include <QUrlQuery>
#include <QDebug>

#include "src/models/requestinfo.h"

class ApiWorker : public QObject
{
    Q_OBJECT
public:
    explicit ApiWorker(QNetworkAccessManager* networkManager, QObject *parent = nullptr);
    ~ApiWorker();
    void post(const QNetworkRequest &request, const QByteArray &data);
    void get(const QNetworkRequest &request);

    RequestInfo *getRequestInfo();

private:
    QNetworkAccessManager* networkManager;
    RequestInfo requestInfo;
    QNetworkReply *reply;

signals:
    void done(QByteArray &data);

private slots:
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void error(QNetworkReply::NetworkError code);
    void finished();

};

#endif // APIWORKER_H
