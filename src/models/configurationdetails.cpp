#include "configurationdetails.h"

ConfigurationDetails::ConfigurationDetails(QObject *parent) :
    QObject(parent),
    optimalListSize("w185"),
    optimalPosterSize("w342"),
    optimalStillSize("w300"),
    imagesSecureBaseUrl("https://image.tmdb.org/t/p/"),
    logoSize("original"),
    posterSize("original")
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

    setImagesSecureBaseUrl(images["secure_base_url"].toString());
    setBackdropSizeInList(findInJsonStringArray(images["backdrop_sizes"].toArray(), "w300", "original"));
    setBackdropSize(findInJsonStringArray(images["backdrop_sizes"].toArray(), "w1280", "original"));
    setLogoSize(findInJsonStringArray(images["logo_sizes"].toArray(), optimalListSize, "original"));
    setPosterSize(findInJsonStringArray(images["poster_sizes"].toArray(), optimalPosterSize, "original"));
    setProfileSize(findInJsonStringArray(images["profile_sizes"].toArray(), optimalListSize, "original"));
    setStillSize(findInJsonStringArray(images["still_sizes"].toArray(), optimalStillSize, "original"));

    return json;
}

const QString &ConfigurationDetails::getImagesSecureBaseUrl() const
{
    return imagesSecureBaseUrl;
}

void ConfigurationDetails::setImagesSecureBaseUrl(const QString &newImagesSecureBaseUrl)
{
    if (imagesSecureBaseUrl == newImagesSecureBaseUrl)
        return;
    imagesSecureBaseUrl = newImagesSecureBaseUrl;
    emit imagesSecureBaseUrlChanged();
}

const QString &ConfigurationDetails::getBackdropSizeInList() const
{
    return backdropSizeInList;
}

void ConfigurationDetails::setBackdropSizeInList(const QString &newBackdropSizeInList)
{
    if (backdropSizeInList == newBackdropSizeInList)
        return;
    backdropSizeInList = newBackdropSizeInList;
    emit backdropSizeInListChanged();
}

const QString &ConfigurationDetails::getLogoSize() const
{
    return logoSize;
}

void ConfigurationDetails::setLogoSize(const QString &newLogoSize)
{
    if (logoSize == newLogoSize)
        return;
    logoSize = newLogoSize;
    emit logoSizeChanged();
}

const QString &ConfigurationDetails::getPosterSize() const
{
    return posterSize;
}

void ConfigurationDetails::setPosterSize(const QString &newPosterSize)
{
    if (posterSize == newPosterSize)
        return;
    posterSize = newPosterSize;
    emit posterSizeChanged();
}

const QString &ConfigurationDetails::getProfileSize() const
{
    return profileSize;
}

void ConfigurationDetails::setProfileSize(const QString &newProfileSize)
{
    if (profileSize == newProfileSize)
        return;
    profileSize = newProfileSize;
    emit profileSizeChanged();
}

const QString &ConfigurationDetails::getBackdropSize() const
{
    return backdropSize;
}

void ConfigurationDetails::setBackdropSize(const QString &newBackdropSize)
{
    if (backdropSize == newBackdropSize)
        return;
    backdropSize = newBackdropSize;
    emit backdropSizeChanged();
}

const QString &ConfigurationDetails::getStillSize() const
{
    return stillSize;
}

void ConfigurationDetails::setStillSize(const QString &newStillSize)
{
    if (stillSize == newStillSize)
        return;
    stillSize = newStillSize;
    emit stillSizeChanged();
}

QString ConfigurationDetails::findInJsonStringArray(const QJsonArray &haystack, const QString &needle, const QString &defaultValue)
{
    for (QJsonValue itemJson : haystack) {
        QString str = itemJson.toString();
        if (str == needle) {
            return needle;
        }
    }

    return defaultValue;
}


