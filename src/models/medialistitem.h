#ifndef MOVIELISTITEM_H
#define MOVIELISTITEM_H

#include <QDateTime>
#include <QDebug>
#include <QList>
#include <QString>
#include <QStringList>

class MediaListItem
{
public:
    enum MediaType {
        Unknown = 0,
        MovieType,
        TvType,
        PersonType
    };
    MediaListItem(
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
            const QString &knownForDepartment,
            QStringList knownFor,
            const QDateTime &firstAirDate);

    MediaType getMediaType() const;
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
    const QString &getKnownForDepartment() const;
    const QStringList &getKnownFor() const;
    const QDateTime &getFirstAirDate() const;

    const QString &getHistoryDateTime() const;
    void setHistoryDateTime(const QString &newHistoryDateTime);

private:
    MediaType mediaType;
    bool adult;
    QString backdropPath;
    QStringList genres;
    int id;
    QString originalName; // title or name
    QString overview;
    QString imagePath; // poster or person's photo
    QString releaseYear; // for a movie
    QString name; // title or name
    float voteAvarage;
    int voteCount;
    QString knownForDepartment; // for a person
    QStringList knownFor; // for a person
    QDateTime firstAirDate; // for a TV show
    QString historyDateTime; // in case it renders history
};

#endif // MOVIELISTITEM_H
