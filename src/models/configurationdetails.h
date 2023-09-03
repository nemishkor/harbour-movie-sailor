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
    Q_PROPERTY(QString backdropSize READ getBackdropSize WRITE setBackdropSize NOTIFY backdropSizeChanged)
    Q_PROPERTY(QString backdropSizeInList READ getBackdropSizeInList WRITE setBackdropSizeInList NOTIFY backdropSizeInListChanged)
    Q_PROPERTY(QString logoSize READ getLogoSize WRITE setLogoSize NOTIFY logoSizeChanged)
    Q_PROPERTY(QString posterSize READ getPosterSize WRITE setPosterSize NOTIFY posterSizeChanged)
    Q_PROPERTY(QString profileSize READ getProfileSize NOTIFY profileSizeChanged)
public:
    ConfigurationDetails(QObject *parent);

    void fillFromCache(const QJsonDocument &json);
    const QJsonDocument fillFromAPI(const QJsonDocument &json);

    const QString &getImagesSecureBaseUrl() const;
    void setImagesSecureBaseUrl(const QString &newImagesSecureBaseUrl);

    const QString &getBackdropSizeInList() const;
    void setBackdropSizeInList(const QString &newBackdropSizeInList);

    const QString &getLogoSize() const;
    void setLogoSize(const QString &newLogoSize);

    const QString &getPosterSize() const;
    void setPosterSize(const QString &newPosterSize);

    const QString &getProfileSize() const;
    void setProfileSize(const QString &newProfileSize);

    const QString &getBackdropSize() const;
    void setBackdropSize(const QString &newBackdropSize);

    const QString &getStillSize() const;
    void setStillSize(const QString &newStillSize);

private:
    const QString optimalListSize; // Optimal for list/grid view on Sony 10 II
    const QString optimalPosterSize;
    const QString optimalStillSize;
    QString imagesSecureBaseUrl;
    QString backdropSize;
    QString backdropSizeInList;
    QString logoSize;
    QString posterSize;
    QString profileSize;
    QString stillSize;

    QString findInJsonStringArray(const QJsonArray &haystack, const QString &needle, const QString &defaultValue);

    Q_PROPERTY(QString stillSize READ getStillSize WRITE setStillSize NOTIFY stillSizeChanged)

signals:
    void imagesSecureBaseUrlChanged();
    void backdropSizeInListChanged();
    void logoSizeChanged();
    void posterSizeChanged();
    void profileSizeChanged();
    void backdropSizeChanged();
    void stillSizeChanged();
};

#endif // CONFIGURATIONDETAILS_H
