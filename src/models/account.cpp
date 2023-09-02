#include "account.h"

Account::Account(QObject *parent) :
    QObject(parent),
    id(0)
{

}

int Account::getId() const
{
    return id;
}

void Account::setId(int newId)
{
    if (id == newId)
        return;
    id = newId;
    emit idChanged();
}

const QString &Account::getLanguage() const
{
    return language;
}

void Account::setLanguage(const QString &newLanguage)
{
    if (language == newLanguage)
        return;
    language = newLanguage;
    emit languageChanged();
}

const QString &Account::getCountry() const
{
    return country;
}

void Account::setCountry(const QString &newCountry)
{
    if (country == newCountry)
        return;
    country = newCountry;
    emit countryChanged();
}

const QString &Account::getName() const
{
    return name;
}

void Account::setName(const QString &newName)
{
    if (name == newName)
        return;
    name = newName;
    emit nameChanged();
}

bool Account::getIncludeAdult() const
{
    return includeAdult;
}

void Account::setIncludeAdult(bool newIncludeAdult)
{
    if (includeAdult == newIncludeAdult)
        return;
    includeAdult = newIncludeAdult;
    emit includeAdultChanged();
}

const QString &Account::getUsername() const
{
    return username;
}

void Account::setUsername(const QString &newUsername)
{
    if (username == newUsername)
        return;
    username = newUsername;
    emit usernameChanged();
}
