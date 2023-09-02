#include "countrylistitem.h"

CountryListItem::CountryListItem(const QString &id, const QString &name) :
    id(id),
    name(name)
{

}

const QString &CountryListItem::getId() const
{
    return id;
}

const QString &CountryListItem::getName() const
{
    return name;
}
