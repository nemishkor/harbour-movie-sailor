#include "personlistitem.h"

PersonListItem::PersonListItem() : checked(false)
{

}

int PersonListItem::getId() const
{
    return id;
}

void PersonListItem::setId(int newId)
{
    id = newId;
}

const QString &PersonListItem::getName() const
{
    return name;
}

void PersonListItem::setName(const QString &newName)
{
    name = newName;
}

bool PersonListItem::getChecked() const
{
    return checked;
}

void PersonListItem::setChecked(bool newChecked)
{
    checked = newChecked;
}

const QString &PersonListItem::getKnownForDepartment() const
{
    return knownForDepartment;
}

void PersonListItem::setKnownForDepartment(const QString &newKnownForDepartment)
{
    knownForDepartment = newKnownForDepartment;
}

const QString &PersonListItem::getProfilePath() const
{
    return profilePath;
}

void PersonListItem::setProfilePath(const QString &newProfilePath)
{
    profilePath = newProfilePath;
}
