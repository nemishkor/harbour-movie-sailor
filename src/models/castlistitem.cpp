#include "castlistitem.h"

CastListItem::CastListItem(int id,
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

int CastListItem::getId() const
{
    return id;
}
const QString &CastListItem::getName() const
{
    return name;
}

const QString &CastListItem::getOriginalName() const
{
    return originalName;
}

const QString &CastListItem::getProfilePath() const
{
    return profilePath;
}

const QString &CastListItem::getCharacter() const
{
    return character;
}
