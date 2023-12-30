#include "tvnetwork.h"

TvNetwork::TvNetwork(QObject *parent) : QObject(parent), id(-1)
{

}

int TvNetwork::getId() const
{
    return id;
}

void TvNetwork::setId(int newId)
{
    if (id == newId)
        return;
    id = newId;
    emit idChanged();
}

const QString &TvNetwork::getName() const
{
    return name;
}

void TvNetwork::setName(const QString &newName)
{
    if (name == newName)
        return;
    name = newName;
    emit nameChanged();
}
