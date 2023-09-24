#include "movieprovider.h"

MovieProvider::MovieProvider() :
    priority(0),
    checked(false)
{

}

const QString &MovieProvider::getLogo() const
{
    return logo;
}

void MovieProvider::setLogo(const QString &newLogo)
{
    logo = newLogo;
}

const QString &MovieProvider::getName() const
{
    return name;
}

void MovieProvider::setName(const QString &newName)
{
    name = newName;
}

int MovieProvider::getId() const
{
    return id;
}

void MovieProvider::setId(int newId)
{
    id = newId;
}

int MovieProvider::getPriority() const
{
    return priority;
}

void MovieProvider::setPriority(int newPriority)
{
    priority = newPriority;
}

bool MovieProvider::getChecked() const
{
    return checked;
}

void MovieProvider::setChecked(bool newChecked)
{
    checked = newChecked;
}
