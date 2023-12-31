#ifndef PERSON_H
#define PERSON_H

#include <QObject>

#include "src/viewmodels/medialistmodel.h"

class Person : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList alsoKnownAs READ getAlsoKnownAs WRITE setAlsoKnownAs NOTIFY alsoKnownAsChanged)
    Q_PROPERTY(QString biography READ getBiography WRITE setBiography NOTIFY biographyChanged)
    Q_PROPERTY(QString birthday READ getBirthday WRITE setBirthday NOTIFY birthdayChanged)
    Q_PROPERTY(QString deathday READ getDeathday WRITE setDeathday NOTIFY deathdayChanged)
    Q_PROPERTY(QString homepage READ getHomepage WRITE setHomepage NOTIFY homepageChanged)
    Q_PROPERTY(QString imdbId READ getImdbId WRITE setImdbId NOTIFY imdbIdChanged)
    Q_PROPERTY(QString knownForDepartment READ getKnownForDepartment WRITE setKnownForDepartment NOTIFY knownForDepartmentChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString placeOfBirth READ getPlaceOfBirth WRITE setPlaceOfBirth NOTIFY placeOfBirthChanged)
    Q_PROPERTY(QString profilePath READ getProfilePath WRITE setProfilePath NOTIFY profilePathChanged)
    Q_PROPERTY(QString wikidataId READ getWikidataId WRITE setWikidataId NOTIFY wikidataIdChanged)
    Q_PROPERTY(QString facebookId READ getFacebookId WRITE setFacebookId NOTIFY facebookIdChanged)
    Q_PROPERTY(QString instagramId READ getInstagramId WRITE setInstagramId NOTIFY instagramIdChanged)
    Q_PROPERTY(QString tiktokId READ getTiktokId WRITE setTiktokId NOTIFY tiktokIdChanged)
    Q_PROPERTY(QString twitterId READ getTwitterId WRITE setTwitterId NOTIFY twitterIdChanged)
    Q_PROPERTY(QString youtubeId READ getYoutubeId WRITE setYoutubeId NOTIFY youtubeIdChanged)
    Q_PROPERTY(QStringList images READ getImages WRITE setImages NOTIFY imagesChanged)
    Q_PROPERTY(MediaListModel* cast READ getCast CONSTANT)
    Q_PROPERTY(MediaListModel* crew READ getCrew CONSTANT)

public:
    Person(QObject *parent = nullptr);

    void reset();

    const QStringList &getAlsoKnownAs() const;
    void setAlsoKnownAs(const QStringList &newAlsoKnownAs);

    const QString &getBiography() const;
    void setBiography(const QString &newBiography);

    const QString &getBirthday() const;
    void setBirthday(const QString &newBirthday);

    const QString &getDeathday() const;
    void setDeathday(const QString &newDeathday);

    const QString &getHomepage() const;
    void setHomepage(const QString &newHomepage);

    const QString &getImdbId() const;
    void setImdbId(const QString &newImdbId);

    const QString &getKnownForDepartment() const;
    void setKnownForDepartment(const QString &newKnownForDepartment);

    const QString &getName() const;
    void setName(const QString &newName);

    const QString &getPlaceOfBirth() const;
    void setPlaceOfBirth(const QString &newPlaceOfBirth);

    const QString &getProfilePath() const;
    void setProfilePath(const QString &newProfilePath);

    const QString &getWikidataId() const;
    void setWikidataId(const QString &newWikidataId);

    const QString &getFacebookId() const;
    void setFacebookId(const QString &newFacebookId);

    const QString &getInstagramId() const;
    void setInstagramId(const QString &newInstagramId);

    const QString &getTiktokId() const;
    void setTiktokId(const QString &newTiktokId);

    const QString &getTwitterId() const;
    void setTwitterId(const QString &newTwitterId);

    const QString &getYoutubeId() const;
    void setYoutubeId(const QString &newYoutubeId);

    const QStringList &getImages() const;
    void setImages(const QStringList &newImages);

    MediaListModel *getCast() const;

    MediaListModel *getCrew() const;

signals:
    void alsoKnownAsChanged();
    void biographyChanged();
    void birthdayChanged();
    void homepageChanged();
    void imdbIdChanged();
    void knownForDepartmentChanged();
    void nameChanged();
    void placeOfBirthChanged();
    void profilePathChanged();
    void wikidataIdChanged();
    void facebookIdChanged();
    void instagramIdChanged();
    void tiktokIdChanged();
    void twitterIdChanged();
    void youtubeIdChanged();
    void imagesChanged();
    void deathdayChanged();

private:
    QStringList alsoKnownAs;
    QString biography;
    QString deathday;
    QString birthday;
    QString homepage;
    QString imdbId;
    QString knownForDepartment;
    QString name;
    QString placeOfBirth;
    QString profilePath;
    QString wikidataId;
    QString facebookId;
    QString instagramId;
    QString tiktokId;
    QString twitterId;
    QString youtubeId;
    QStringList images;
    MediaListModel *cast;
    MediaListModel *crew;

};

#endif // PERSON_H
