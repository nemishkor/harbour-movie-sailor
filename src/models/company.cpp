#include "company.h"

Company::Company(int id, const QString &logo, const QString &name, const QString &country):
    id(id),
    logo(logo),
    name(name),
    country(country)
{

}

Company::Company(const QJsonObject &json) :
    id(json["id"].toInt()),
    logo(json["logo"].toString()),
    name(json["name"].toString()),
    country(json["country"].toString())
{

}

int Company::getId() const
{
    return id;
}

void Company::setId(int newId)
{
    id = newId;
}

const QString &Company::getLogo() const
{
    return logo;
}

void Company::setLogo(const QString &newLogo)
{
    logo = newLogo;
}

const QString &Company::getName() const
{
    return name;
}

void Company::setName(const QString &newName)
{
    name = newName;
}

const QString &Company::getCountry() const
{
    return country;
}

void Company::setCountry(const QString &newCountry)
{
    country = newCountry;
}
