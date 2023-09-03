#include "episode.h"

Episode::Episode(QObject *parent) : QObject(parent)
{

}

void Episode::clear()
{
    setAirDate("");
    setEpisodeNumber(0);
    setEpisodeType("");
    setId(0);
    setName("");
    setOverview("");
    setProductionCode("");
    setRuntime(0);
    setSeasonNumber(0);
    setShowId(0);
    setStillPath("");
    setVoteAvarage(0.0);
    setVoteCount(0);
}

int Episode::getId() const
{
    return id;
}

void Episode::setId(int newId)
{
    if (id == newId)
        return;
    id = newId;
    emit idChanged();
}

const QString &Episode::getName() const
{
    return name;
}

void Episode::setName(const QString &newName)
{
    if (name == newName)
        return;
    name = newName;
    emit nameChanged();
}

const QString &Episode::getOverview() const
{
    return overview;
}

void Episode::setOverview(const QString &newOverview)
{
    if (overview == newOverview)
        return;
    overview = newOverview;
    emit overviewChanged();
}

double Episode::getVoteAvarage() const
{
    return voteAvarage;
}

void Episode::setVoteAvarage(double newVoteAvarage)
{
    if (qFuzzyCompare(voteAvarage, newVoteAvarage))
        return;
    voteAvarage = newVoteAvarage;
    emit voteAvarageChanged();
}

int Episode::getVoteCount() const
{
    return voteCount;
}

void Episode::setVoteCount(int newVoteCount)
{
    if (voteCount == newVoteCount)
        return;
    voteCount = newVoteCount;
    emit voteCountChanged();
}

const QString &Episode::getAirDate() const
{
    return airDate;
}

void Episode::setAirDate(const QString &newAirDate)
{
    if (airDate == newAirDate)
        return;
    airDate = newAirDate;
    emit airDateChanged();
}

int Episode::getEpisodeNumber() const
{
    return episodeNumber;
}

void Episode::setEpisodeNumber(int newEpisodeNumber)
{
    if (episodeNumber == newEpisodeNumber)
        return;
    episodeNumber = newEpisodeNumber;
    emit episodeNumberChanged();
}

const QString &Episode::getEpisodeType() const
{
    return episodeType;
}

void Episode::setEpisodeType(const QString &newEpisodeType)
{
    if (episodeType == newEpisodeType)
        return;
    episodeType = newEpisodeType;
    emit episodeTypeChanged();
}

const QString &Episode::getProductionCode() const
{
    return productionCode;
}

void Episode::setProductionCode(const QString &newProductionCode)
{
    if (productionCode == newProductionCode)
        return;
    productionCode = newProductionCode;
    emit productionCodeChanged();
}

int Episode::getRuntime() const
{
    return runtime;
}

void Episode::setRuntime(int newRuntime)
{
    if (runtime == newRuntime)
        return;
    runtime = newRuntime;
    emit runtimeChanged();
}

int Episode::getSeasonNumber() const
{
    return seasonNumber;
}

void Episode::setSeasonNumber(int newSeasonNumber)
{
    if (seasonNumber == newSeasonNumber)
        return;
    seasonNumber = newSeasonNumber;
    emit seasonNumberChanged();
}

int Episode::getShowId() const
{
    return showId;
}

void Episode::setShowId(int newShowId)
{
    if (showId == newShowId)
        return;
    showId = newShowId;
    emit showIdChanged();
}

const QString &Episode::getStillPath() const
{
    return stillPath;
}

void Episode::setStillPath(const QString &newStillPath)
{
    if (stillPath == newStillPath)
        return;
    stillPath = newStillPath;
    emit stillPathChanged();
}
