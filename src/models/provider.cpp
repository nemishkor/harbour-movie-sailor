#include "provider.h"

Provider::Provider(int id, const QString &name):
    id(id),
    name(name)
{

}

int Provider::getId() const
{
    return id;
}

const QString &Provider::getName() const
{
    return name;
}
