#ifndef CONFIGURATIONDETAILS_H
#define CONFIGURATIONDETAILS_H

#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStringList>

#include "src/apiworker.h"

class ConfigurationDetails : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString imagesSecureBaseUrl READ getImagesSecureBaseUrl NOTIFY imagesSecureBaseUrlChanged)
    Q_PROPERTY(QString imagesLogoSize READ getImagesLogoSize NOTIFY imagesLogoSizeChanged)
public:
    ConfigurationDetails(QObject *parent);

    void fillFromCache(const QJsonDocument &json);
    const QJsonDocument fillFromAPI(const QJsonDocument &json);

    const QString &getImagesSecureBaseUrl() const;
    const QString &getImagesLogoSize() const;

private:
    QString imagesSecureBaseUrl;
    QStringList imagesDropSizes;
    QStringList imagesLogoSizes;
    QString imagesLogoSize;
    QStringList imagesPosterSizes;
    QStringList imagesProfileSizes;
    QStringList imagesStillSizes;
    QStringList changeKeys;

    void jsonArrayToStringList(const QJsonArray& json, QStringList& list);
    void setImagesLogoSize();

signals:
    void imagesSecureBaseUrlChanged();
    void imagesLogoSizeChanged();

};

#endif // CONFIGURATIONDETAILS_H
