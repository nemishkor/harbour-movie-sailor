#include "country.h"

Country::Country(QObject *parent) :
    QObject(parent),
    id(""),
    name("")
{

}

const QString &Country::getId() const
{
    return id;
}

void Country::setId(const QString &newId)
{
    if (id == newId)
        return;
    id = newId;
    emit idChanged();
}

const QString &Country::getName() const
{
    return name;
}

void Country::setName(const QString &newName)
{
    if (name == newName)
        return;
    name = newName;
    emit nameChanged();
}
