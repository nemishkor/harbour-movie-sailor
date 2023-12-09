#include "media.h"

Media::Media(QObject *parent) : QObject(parent), mediaType(MediaType::Unknown), id(0)
{

}

Media::MediaType Media::getMediaType() const
{
    return mediaType;
}

void Media::setMediaType(MediaType newMediaType)
{
    if (mediaType == newMediaType)
        return;
    mediaType = newMediaType;
    emit mediaTypeChanged();
}

int Media::getId() const
{
    return id;
}

void Media::setId(int newId)
{
    if (id == newId)
        return;
    id = newId;
    emit idChanged();
}

const QString &Media::getImagePath() const
{
    return imagePath;
}

void Media::setImagePath(const QString &newImagePath)
{
    if (imagePath == newImagePath)
        return;
    imagePath = newImagePath;
    emit imagePathChanged();
}

const QString &Media::getName() const
{
    return name;
}

void Media::setName(const QString &newName)
{
    if (name == newName)
        return;
    name = newName;
    emit nameChanged();
}

const QString &Media::getHistoryDateTime() const
{
    return historyDateTime;
}

void Media::setHistoryDateTime(const QString &newHistoryDateTime)
{
    if (historyDateTime == newHistoryDateTime)
        return;
    historyDateTime = newHistoryDateTime;
    emit historyDateTimeChanged();
}
