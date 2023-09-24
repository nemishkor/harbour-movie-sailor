#include "language.h"

Language::Language()
{

}

Language::Language(const Language &language) :
    id(QString(language.id)),
    englishName(QString(language.englishName)),
    name(QString(language.name)),
    isPrimary(language.isPrimary)
{
//    qDebug() << "copy Language" << id;
}

Language::Language(Language &language, bool isPrimary) :
    id(QString(language.id)),
    englishName(QString(language.englishName)),
    name(QString(language.name)),
    isPrimary(isPrimary)
{

}

Language::Language(const QJsonObject &json) :
    id(json["iso_639_1"].toString()),
    englishName(json["english_name"].toString()),
    name(json["name"].toString()),
    isPrimary(json["primary"].toBool())
{

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

void Language::setName(const QString &newName)
{
    name = newName;
}

void Language::setIsPrimary(bool newIsPrimary)
{
    isPrimary = newIsPrimary;
}

void Language::setEnglishName(const QString &newEnglishName)
{
    englishName = newEnglishName;
}

void Language::setId(const QString &newId)
{
    id = newId;
}
