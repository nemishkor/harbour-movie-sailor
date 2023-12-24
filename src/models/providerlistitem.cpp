#include "providerlistitem.h"

ProviderListItem::ProviderListItem(int id, const QString &logo, const QString &name):
    id(id),
    state(0),
    logo(logo),
    name(name),
    priority(0)
{

}

ProviderListItem::ProviderListItem(int id, const QString &logo, const QString &name, int priority):
    id(id),
    state(0),
    logo(logo),
    name(name),
    priority(priority)
{

}

int ProviderListItem::getId() const
{
    return id;
}

void ProviderListItem::setId(int newId)
{
    id = newId;
}

int ProviderListItem::getState() const
{
    return state;
}

void ProviderListItem::setState(int newState)
{
    state = newState;
}

const QString &ProviderListItem::getLogo() const
{
    return logo;
}

void ProviderListItem::setLogo(const QString &newLogo)
{
    logo = newLogo;
}

const QString &ProviderListItem::getName() const
{
    return name;
}

void ProviderListItem::setName(const QString &newName)
{
    name = newName;
}

int ProviderListItem::getPriority() const
{
    return priority;
}

void ProviderListItem::setPriority(int newPriority)
{
    priority = newPriority;
}
