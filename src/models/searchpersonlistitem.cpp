#include "searchpersonlistitem.h"

SearchPersonListItem::SearchPersonListItem() :
    checked(false),
    role(AnyRole)
{

}

int SearchPersonListItem::getId() const
{
    return id;
}

void SearchPersonListItem::setId(int newId)
{
    id = newId;
}

const QString &SearchPersonListItem::getName() const
{
    return name;
}

void SearchPersonListItem::setName(const QString &newName)
{
    name = newName;
}

bool SearchPersonListItem::getChecked() const
{
    return checked;
}

void SearchPersonListItem::setChecked(bool newChecked)
{
    checked = newChecked;
}

const QString &SearchPersonListItem::getKnownForDepartment() const
{
    return knownForDepartment;
}

void SearchPersonListItem::setKnownForDepartment(const QString &newKnownForDepartment)
{
    knownForDepartment = newKnownForDepartment;
}

const QString &SearchPersonListItem::getProfilePath() const
{
    return profilePath;
}

void SearchPersonListItem::setProfilePath(const QString &newProfilePath)
{
    profilePath = newProfilePath;
}

SearchPersonListItem::PersonRole SearchPersonListItem::getRole() const
{
    return role;
}

void SearchPersonListItem::setRole(PersonRole newRole)
{
    role = newRole;
}
