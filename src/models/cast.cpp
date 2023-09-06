#include "cast.h"

Cast::Cast(int id,
           const QString &name,
           const QString &originalName,
           const QString &profilePath,
           int castId,
           const QString &character,
           const QString &creditId) :
    id(id),
    name(name),
    originalName(originalName),
    profilePath(profilePath),
    castId(castId),
    character(character),
    creditId(creditId)
{

}

int Cast::getId() const
{
    return id;
}
const QString &Cast::getName() const
{
    return name;
}

const QString &Cast::getOriginalName() const
{
    return originalName;
}

const QString &Cast::getProfilePath() const
{
    return profilePath;
}

int Cast::getCastId() const
{
    return castId;
}

const QString &Cast::getCharacter() const
{
    return character;
}

const QString &Cast::getCreditId() const
{
    return creditId;
}
