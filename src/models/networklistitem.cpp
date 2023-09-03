#include "networklistitem.h"

NetworkListItem::NetworkListItem(int id,
                 const QString &logoPath,
                 const QString &name,
                 const QString &originCountry) :
    id(id),
    logoPath(logoPath),
    name(name),
    originCountry(originCountry)
{

}

int NetworkListItem::getId() const
{
    return id;
}

const QString &NetworkListItem::getLogoPath() const
{
    return logoPath;
}

const QString &NetworkListItem::getName() const
{
    return name;
}

const QString &NetworkListItem::getOriginCountry() const
{
    return originCountry;
}
