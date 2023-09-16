#include "person.h"

Person::Person(QObject *parent) : QObject(parent)
{

}

const QStringList &Person::getAlsoKnownAs() const
{
    return alsoKnownAs;
}

void Person::setAlsoKnownAs(const QStringList &newAlsoKnownAs)
{
    if (alsoKnownAs == newAlsoKnownAs)
        return;
    alsoKnownAs = newAlsoKnownAs;
    emit alsoKnownAsChanged();
}

const QString &Person::getBiography() const
{
    return biography;
}

void Person::setBiography(const QString &newBiography)
{
    if (biography == newBiography)
        return;
    biography = newBiography;
    emit biographyChanged();
}

const QString &Person::getBirthday() const
{
    return birthday;
}

void Person::setBirthday(const QString &newBirthday)
{
    if (birthday == newBirthday)
        return;
    birthday = newBirthday;
    emit birthdayChanged();
}

const QString &Person::getHomepage() const
{
    return homepage;
}

void Person::setHomepage(const QString &newHomepage)
{
    if (homepage == newHomepage)
        return;
    homepage = newHomepage;
    emit homepageChanged();
}

int Person::getId() const
{
    return id;
}

void Person::setId(int newId)
{
    if (id == newId)
        return;
    id = newId;
    emit idChanged();
}

const QString &Person::getImdbId() const
{
    return imdbId;
}

void Person::setImdbId(const QString &newImdbId)
{
    if (imdbId == newImdbId)
        return;
    imdbId = newImdbId;
    emit imdbIdChanged();
}

const QString &Person::getKnownForDepartment() const
{
    return knownForDepartment;
}

void Person::setKnownForDepartment(const QString &newKnownForDepartment)
{
    if (knownForDepartment == newKnownForDepartment)
        return;
    knownForDepartment = newKnownForDepartment;
    emit knownForDepartmentChanged();
}

const QString &Person::getName() const
{
    return name;
}

void Person::setName(const QString &newName)
{
    if (name == newName)
        return;
    name = newName;
    emit nameChanged();
}

const QString &Person::getPlaceOfBirth() const
{
    return placeOfBirth;
}

void Person::setPlaceOfBirth(const QString &newPlaceOfBirth)
{
    if (placeOfBirth == newPlaceOfBirth)
        return;
    placeOfBirth = newPlaceOfBirth;
    emit placeOfBirthChanged();
}

const QString &Person::getProfilePath() const
{
    return profilePath;
}

void Person::setProfilePath(const QString &newProfilePath)
{
    if (profilePath == newProfilePath)
        return;
    profilePath = newProfilePath;
    emit profilePathChanged();
}

const QString &Person::getWikidataId() const
{
    return wikidataId;
}

void Person::setWikidataId(const QString &newWikidataId)
{
    if (wikidataId == newWikidataId)
        return;
    wikidataId = newWikidataId;
    emit wikidataIdChanged();
}

const QString &Person::getFacebookId() const
{
    return facebookId;
}

void Person::setFacebookId(const QString &newFacebookId)
{
    if (facebookId == newFacebookId)
        return;
    facebookId = newFacebookId;
    emit facebookIdChanged();
}

const QString &Person::getInstagramId() const
{
    return instagramId;
}

void Person::setInstagramId(const QString &newInstagramId)
{
    if (instagramId == newInstagramId)
        return;
    instagramId = newInstagramId;
    emit instagramIdChanged();
}

const QString &Person::getTiktokId() const
{
    return tiktokId;
}

void Person::setTiktokId(const QString &newTiktokId)
{
    if (tiktokId == newTiktokId)
        return;
    tiktokId = newTiktokId;
    emit tiktokIdChanged();
}

const QString &Person::getTwitterId() const
{
    return twitterId;
}

void Person::setTwitterId(const QString &newTwitterId)
{
    if (twitterId == newTwitterId)
        return;
    twitterId = newTwitterId;
    emit twitterIdChanged();
}

const QString &Person::getYoutubeId() const
{
    return youtubeId;
}

void Person::setYoutubeId(const QString &newYoutubeId)
{
    if (youtubeId == newYoutubeId)
        return;
    youtubeId = newYoutubeId;
    emit youtubeIdChanged();
}

const QStringList &Person::getImages() const
{
    return images;
}

void Person::setImages(const QStringList &newImages)
{
    if (images == newImages)
        return;
    images = newImages;
    emit imagesChanged();
}

const QString &Person::getDeathday() const
{
    return deathday;
}

void Person::setDeathday(const QString &newDeathday)
{
    if (deathday == newDeathday)
        return;
    deathday = newDeathday;
    emit deathdayChanged();
}
