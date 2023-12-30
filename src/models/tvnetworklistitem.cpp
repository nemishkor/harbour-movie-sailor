#include "tvnetworklistitem.h"

TVNetworkListItem::TVNetworkListItem(int id, const QString &name):
    id(id),
    name(name)
{

}

int TVNetworkListItem::getId() const
{
    return id;
}

const QString &TVNetworkListItem::getName() const
{
    return name;
}
