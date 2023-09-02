#ifndef MOVIELISTITEM_H
#define MOVIELISTITEM_H

#include <QDebug>
#include <QList>
#include <QString>

class MovieListItem
{
public:
    MovieListItem(
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
            int voteCount);

    bool getAdult() const;
    const QString &getBackdropPath() const;
    const QStringList &getGenres() const;
    int getId() const;
    const QString &getOriginalTitle() const;
    const QString &getOverview() const;
    const QString &getPosterPath() const;
    const QString &getReleaseYear() const;
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
    QString releaseYear;
    QString title;
    float voteAvarage;
    int voteCount;
};

#endif // MOVIELISTITEM_H
