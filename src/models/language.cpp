#include "language.h"

Language::Language(QObject *parent) : QObject(parent)
{

}

const QString &Language::getId() const
{
    return id;
}

void Language::setId(const QString &newId)
{
    if (id == newId)
        return;
    id = newId;
    emit idChanged();
}

const QString &Language::getName() const
{
    return name;
}

void Language::setName(const QString &newName)
{
    if (name == newName)
        return;
    name = newName;
    emit nameChanged();
}
