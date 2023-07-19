#include "language.h"

Language::Language(const QString &id, const QString &englishName, const QString &name, bool isPrimary) :
    id(id),
    englishName(englishName),
    name(name),
    isPrimary(isPrimary)
{

}

Language::Language(const Language &language) :
    id(QString(language.id)),
    englishName(QString(language.englishName)),
    name(QString(language.name)),
    isPrimary(language.isPrimary)
{

}

Language::Language(const QJsonObject &json) :
    id(json["iso_639_1"].toString()),
    englishName(json["english_name"].toString()),
    name(json["name"].toString()),
    isPrimary(json["primary"].toBool())
{

}

Language::Language(const QJsonObject &json, bool isPrimary) :
    id(json["iso_639_1"].toString()),
    englishName(json["english_name"].toString()),
    name(json["name"].toString()),
    isPrimary(isPrimary)
{

}

bool Language::operator <(const Language &other) const
{
    qDebug() << id << "<" << other.id;
    qDebug() << isPrimary << "<" << other.isPrimary;
    if(isPrimary && other.isPrimary){
        return id > other.id;
    }
    if (isPrimary && !other.isPrimary) {
        return false;
    }
    if(id == other.id){
        return true;
    }
    return id > other.id;
}

const QString &Language::getId() const
{
    return id;
}

const QString &Language::getEnglishName() const
{
    return englishName;
}

const QString &Language::getName() const
{
    return name;
}

const QString Language::getSection() const
{
    if (isPrimary || englishName.length() == 0 || id == "xx") {
        return "";
    }
    return englishName.at(0);
}

bool Language::getIsPrimary() const
{
    return isPrimary;
}

const QJsonObject Language::toJson() const
{
    QJsonObject json;
    json.insert("iso_639_1", QJsonValue(id));
    json.insert("english_name", QJsonValue(englishName));
    json.insert("name", QJsonValue(name));
    json.insert("primary", QJsonValue(isPrimary));

    return json;
}
