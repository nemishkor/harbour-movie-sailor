#include "configurationdetails.h"

ConfigurationDetails::ConfigurationDetails(QObject *parent) :
    QObject(parent),
    imagesLogoSize("original")
{
}

void ConfigurationDetails::fillFromCache(const QJsonDocument &json)
{
    fillFromAPI(json);
}

const QJsonDocument ConfigurationDetails::fillFromAPI(const QJsonDocument &json)
{
    QJsonObject root = json.object();

    QJsonObject images = root["images"].toObject();
    imagesSecureBaseUrl = images["secure_base_url"].toString();
    emit imagesSecureBaseUrlChanged();
    jsonArrayToStringList(images["backdrop_sizes"].toArray(), imagesDropSizes);
    jsonArrayToStringList(images["logo_sizes"].toArray(), imagesLogoSizes);
    setImagesLogoSize();
    jsonArrayToStringList(images["poster_sizes"].toArray(), imagesLogoSizes);
    jsonArrayToStringList(images["profile_sizes"].toArray(), imagesProfileSizes);
    setProfileSize();
    jsonArrayToStringList(images["still_sizes"].toArray(), imagesStillSizes);

    jsonArrayToStringList(root["change_keys"].toArray(), changeKeys);

    return json;
}

const QString &ConfigurationDetails::getImagesSecureBaseUrl() const
{
    return imagesSecureBaseUrl;
}

const QString &ConfigurationDetails::getImagesLogoSize() const
{
    return imagesLogoSize;
}

const QString &ConfigurationDetails::getProfileSize() const
{
    return profileSize;
}

void ConfigurationDetails::jsonArrayToStringList(const QJsonArray &json, QStringList &list)
{
    for (QJsonValue item : json) {
        list.append(item.toString());
    }
}

void ConfigurationDetails::setImagesLogoSize()
{
    for (QString size : imagesLogoSizes) {
        if (size == "w185") { // Optimal for grid view on Sony 10 II
            imagesLogoSize = size;
            emit imagesLogoSizeChanged();
            return;
        }
    }

    imagesLogoSize = "original";
    emit imagesLogoSizeChanged();
}

void ConfigurationDetails::setProfileSize()
{
    qDebug() << "setProfileSize";
    for (QString size : imagesProfileSizes) {
        if (size == "w185") { // Optimal for list view onSony 10 II
            qDebug() << "found optimal ProfileSize";
            profileSize = size;
            emit profileSizeChanged();
            return;
        }
    }

    profileSize = "original";
    emit profileSizeChanged();
}


