#include "moviecollection.h"

MovieCollection::MovieCollection(QObject *parent) : QObject(parent)
{

}

int MovieCollection::getId() const
{
    return id;
}

void MovieCollection::setId(int newId)
{
    if (id == newId)
        return;
    id = newId;
    emit idChanged();
}

const QString &MovieCollection::getName() const
{
    return name;
}

void MovieCollection::setName(const QString &newName)
{
    if (name == newName)
        return;
    name = newName;
    emit nameChanged();
}

const QString &MovieCollection::getPosterPath() const
{
    return posterPath;
}

void MovieCollection::setPosterPath(const QString &newPosterPath)
{
    if (posterPath == newPosterPath)
        return;
    posterPath = newPosterPath;
    emit posterPathChanged();
}

const QString &MovieCollection::getBackdropPath() const
{
    return backdropPath;
}

void MovieCollection::setBackdropPath(const QString &newBackdropPath)
{
    if (backdropPath == newBackdropPath)
        return;
    backdropPath = newBackdropPath;
    emit backdropPathChanged();
}
