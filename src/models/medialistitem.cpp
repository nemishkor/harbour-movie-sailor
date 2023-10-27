#include "medialistitem.h"

MediaListItem::MediaListItem(
        MediaType mediaType,
        bool adult,
        const QString &backdropPath,
        QStringList genres,
        int id,
        const QString &originalTitle,
        const QString &overview,
        const QString &imagePath,
        const QString &releaseYear,
        const QString &title,
        float voteAvarage,
        int voteCount,
        QString knownForDepartment,
        QStringList knownFor) :
    mediaType(mediaType),
    adult(adult),
    backdropPath(backdropPath),
    genres(genres),
    id(id),
    originalName(originalTitle),
    overview(overview),
    imagePath(imagePath),
    releaseYear(releaseYear),
    name(title),
    voteAvarage(voteAvarage),
    voteCount(voteCount),
    knownForDepartment(knownForDepartment),
    knownFor(knownFor)
{
}

bool MediaListItem::getAdult() const
{
    return adult;
}

const QString &MediaListItem::getBackdropPath() const
{
    return backdropPath;
}

const QStringList &MediaListItem::getGenres() const
{
    return genres;
}

int MediaListItem::getId() const
{
    return id;
}

const QString &MediaListItem::getOriginalTitle() const
{
    return originalName;
}

const QString &MediaListItem::getOverview() const
{
    return overview;
}

const QString &MediaListItem::getPosterPath() const
{
    return imagePath;
}

const QString &MediaListItem::getReleaseYear() const
{
    return releaseYear;
}

const QString &MediaListItem::getTitle() const
{
    return name;
}

float MediaListItem::getVoteAvarage() const
{
    return voteAvarage;
}

int MediaListItem::getVoteCount() const
{
    return voteCount;
}

const QString &MediaListItem::getKnownForDepartment() const
{
    return knownForDepartment;
}

const QStringList &MediaListItem::getKnownFor() const
{
    return knownFor;
}

const QString &MediaListItem::getHistoryDateTime() const
{
    return historyDateTime;
}

void MediaListItem::setHistoryDateTime(const QString &newHistoryDateTime)
{
    historyDateTime = newHistoryDateTime;
}

MediaListItem::MediaType MediaListItem::getMediaType() const
{
    return mediaType;
}
