#include "discovermovieresultitem.h"

DiscoverMovieResultItem::DiscoverMovieResultItem(
        bool adult,
        const QString &backdropPath,
        QStringList genres,
        int id,
        const QString &originalTitle,
        const QString &overview,
        const QString &posterPath,
        const QString &releaseDate,
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
    releaseDate(releaseDate),
    title(title),
    voteAvarage(voteAvarage),
    voteCount(voteCount)
{
}

bool DiscoverMovieResultItem::getAdult() const
{
    return adult;
}

const QString &DiscoverMovieResultItem::getBackdropPath() const
{
    return backdropPath;
}

const QStringList &DiscoverMovieResultItem::getGenres() const
{
    return genres;
}

int DiscoverMovieResultItem::getId() const
{
    return id;
}

const QString &DiscoverMovieResultItem::getOriginalTitle() const
{
    return originalTitle;
}

const QString &DiscoverMovieResultItem::getOverview() const
{
    return overview;
}

const QString &DiscoverMovieResultItem::getPosterPath() const
{
    return posterPath;
}

const QString &DiscoverMovieResultItem::getReleaseDate() const
{
    return releaseDate;
}

const QString &DiscoverMovieResultItem::getTitle() const
{
    return title;
}

float DiscoverMovieResultItem::getVoteAvarage() const
{
    return voteAvarage;
}

int DiscoverMovieResultItem::getVoteCount() const
{
    return voteCount;
}
