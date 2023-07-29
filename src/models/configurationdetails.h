#ifndef CONFIGURATIONDETAILS_H
#define CONFIGURATIONDETAILS_H

#include <QByteArray>
#include <QDebug>
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
    Q_PROPERTY(QString profileSize READ getProfileSize NOTIFY profileSizeChanged)
public:
    ConfigurationDetails(QObject *parent);

    void fillFromCache(const QJsonDocument &json);
    const QJsonDocument fillFromAPI(const QJsonDocument &json);

    const QString &getImagesSecureBaseUrl() const;
    const QString &getImagesLogoSize() const;
    const QString &getProfileSize() const;

private:
    QString imagesSecureBaseUrl;
    QStringList imagesDropSizes;
    QStringList imagesLogoSizes;
    QString imagesLogoSize;
    QStringList imagesPosterSizes;
    QStringList imagesProfileSizes;
    QString profileSize;
    QStringList imagesStillSizes;
    QStringList changeKeys;

    void jsonArrayToStringList(const QJsonArray& json, QStringList& list);
    void setImagesLogoSize();
    void setProfileSize();

signals:
    void imagesSecureBaseUrlChanged();
    void imagesLogoSizeChanged();
    void profileSizeChanged();

};

#endif // CONFIGURATIONDETAILS_H
