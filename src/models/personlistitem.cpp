#include "personlistitem.h"

PersonListItem::PersonListItem(int id,
                               const QString &creditId,
                               const QString &name,
                               int gender,
                               const QString &profilePath) :
    id(id),
    creditId(creditId),
    name(name),
    gender(gender),
    profilePath(profilePath)
{

}

int PersonListItem::getId() const
{
    return id;
}

const QString &PersonListItem::getCreditId() const
{
    return creditId;
}

const QString &PersonListItem::getName() const
{
    return name;
}

int PersonListItem::getGender() const
{
    return gender;
}

const QString &PersonListItem::getProfilePath() const
{
    return profilePath;
}
