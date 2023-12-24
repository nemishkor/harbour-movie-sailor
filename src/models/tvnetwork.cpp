#include "tvnetwork.h"

TVNetwork::TVNetwork(int id, const QString &name):
    id(id),
    name(name)
{

}

int TVNetwork::getId() const
{
    return id;
}

const QString &TVNetwork::getName() const
{
    return name;
}
