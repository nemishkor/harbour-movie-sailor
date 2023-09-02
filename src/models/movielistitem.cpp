#include "movielistitem.h"

MovieListItem::MovieListItem(
        bool adult,
        const QString &backdropPath,
        QStringList genres,
        int id,
        const QString &originalTitle,
        const QString &overview,
        const QString &posterPath,
        const QString &releaseYear,
        const QString &title,
        float voteAvarage,
        int voteCount) :
    adult(adult),
    backdropPath(backdropPath),
    genres(genres),
    id(id),
    originalTitle(originalTitle),
    overview(overview),
    posterPath(posterPath),
    releaseYear(releaseYear),
    title(title),
    voteAvarage(voteAvarage),
    voteCount(voteCount)
{
}

bool MovieListItem::getAdult() const
{
    return adult;
}

const QString &MovieListItem::getBackdropPath() const
{
    return backdropPath;
}

const QStringList &MovieListItem::getGenres() const
{
    return genres;
}

int MovieListItem::getId() const
{
    return id;
}

const QString &MovieListItem::getOriginalTitle() const
{
    return originalTitle;
}

const QString &MovieListItem::getOverview() const
{
    return overview;
}

const QString &MovieListItem::getPosterPath() const
{
    return posterPath;
}

const QString &MovieListItem::getReleaseYear() const
{
    return releaseYear;
}

const QString &MovieListItem::getTitle() const
{
    return title;
}

float MovieListItem::getVoteAvarage() const
{
    return voteAvarage;
}

int MovieListItem::getVoteCount() const
{
    return voteCount;
}
