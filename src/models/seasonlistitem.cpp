#include "seasonlistitem.h"

SeasonListItem::SeasonListItem(const QString &airDate,
                               int episodeCount,
                               int id,
                               const QString &name,
                               const QString &overview,
                               const QString &posterPath,
                               int seasonNumber,
                               int voteAvarage) :
    airDate(airDate),
    episodeCount(episodeCount),
    id(id),
    name(name),
    overview(overview),
    posterPath(posterPath),
    seasonNumber(seasonNumber),
    voteAvarage(voteAvarage)
{

}

const QString &SeasonListItem::getAirDate() const
{
    return airDate;
}

int SeasonListItem::getEpisodeCount() const
{
    return episodeCount;
}

int SeasonListItem::getId() const
{
    return id;
}

const QString &SeasonListItem::getName() const
{
    return name;
}

const QString &SeasonListItem::getOverview() const
{
    return overview;
}

const QString &SeasonListItem::getPosterPath() const
{
    return posterPath;
}

int SeasonListItem::getSeasonNumber() const
{
    return seasonNumber;
}

int SeasonListItem::getVoteAvarage() const
{
    return voteAvarage;
}
