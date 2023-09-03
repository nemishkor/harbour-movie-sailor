#ifndef MOVIELISTITEM_H
#define MOVIELISTITEM_H

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
            QString knownForDepartment,
            QStringList knownFor);

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

private:
    MediaType mediaType;
    bool adult;
    QString backdropPath;
    QStringList genres;
    int id;
    QString originalName;
    QString overview;
    QString imagePath;
    QString releaseYear;
    QString name;
    float voteAvarage;
    int voteCount;
    QString knownForDepartment;
    QStringList knownFor;

};

#endif // MOVIELISTITEM_H
