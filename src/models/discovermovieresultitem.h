#ifndef DISCOVERMOVIESEARCHRESULTITEM_H
#define DISCOVERMOVIESEARCHRESULTITEM_H

#include <QDebug>
#include <QList>
#include <QString>

class DiscoverMovieResultItem
{
public:
    DiscoverMovieResultItem(
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
            int voteCount);

    bool getAdult() const;
    const QString &getBackdropPath() const;
    const QStringList &getGenres() const;
    int getId() const;
    const QString &getOriginalTitle() const;
    const QString &getOverview() const;
    const QString &getPosterPath() const;
    const QString &getReleaseDate() const;
    const QString &getTitle() const;
    float getVoteAvarage() const;
    int getVoteCount() const;

private:
    bool adult;
    QString backdropPath;
    QStringList genres;
    int id;
    QString originalTitle;
    QString overview;
    QString posterPath;
    QString releaseDate;
    QString title;
    float voteAvarage;
    int voteCount;
};

#endif // DISCOVERMOVIESEARCHRESULTITEM_H
