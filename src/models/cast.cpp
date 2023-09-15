#include "cast.h"

Cast::Cast(int id,
           const QString &name,
           const QString &originalName,
           const QString &profilePath,
           const QString &character) :
    id(id),
    name(name),
    originalName(originalName),
    profilePath(profilePath),
    character(character)
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

const QString &Cast::getCharacter() const
{
    return character;
}
