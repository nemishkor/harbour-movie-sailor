#ifndef SEASON_H
#define SEASON_H

#include <QString>

class SeasonListItem
{
public:
    SeasonListItem(const QString &airDate,
                   int episodeCount,
                   int id,
                   const QString &name,
                   const QString &overview,
                   const QString &posterPath,
                   int seasonNumber,
                   int voteAvarage);

    const QString &getAirDate() const;
    int getEpisodeCount() const;
    int getId() const;
    const QString &getName() const;
    const QString &getOverview() const;
    const QString &getPosterPath() const;
    int getSeasonNumber() const;
    int getVoteAvarage() const;

private:
    QString airDate;
    int episodeCount;
    int id;
    QString name;
    QString overview;
    QString posterPath;
    int seasonNumber;
    int voteAvarage;

};

#endif // SEASON_H
