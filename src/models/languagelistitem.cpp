#include "languagelistitem.h"

LanguageListItem::LanguageListItem()
{

}

LanguageListItem::LanguageListItem(const LanguageListItem &language) :
    id(QString(language.id)),
    englishName(QString(language.englishName)),
    name(QString(language.name)),
    isPrimary(language.isPrimary)
{
//    qDebug() << "copy Language" << id;
}

LanguageListItem::LanguageListItem(LanguageListItem &language, bool isPrimary) :
    id(QString(language.id)),
    englishName(QString(language.englishName)),
    name(QString(language.name)),
    isPrimary(isPrimary)
{

}

LanguageListItem::LanguageListItem(const QJsonObject &json) :
    id(json["iso_639_1"].toString()),
    englishName(json["english_name"].toString()),
    name(json["name"].toString()),
    isPrimary(json["primary"].toBool())
{

}

const QString &LanguageListItem::getId() const
{
    return id;
}

const QString &LanguageListItem::getEnglishName() const
{
    return englishName;
}

const QString &LanguageListItem::getName() const
{
    return name;
}

const QString LanguageListItem::getSection() const
{
    if (isPrimary || englishName.length() == 0 || id == "xx") {
        return "";
    }
    return englishName.at(0);
}

bool LanguageListItem::getIsPrimary() const
{
    return isPrimary;
}

const QJsonObject LanguageListItem::toJson() const
{
    QJsonObject json;
    json.insert("iso_639_1", QJsonValue(id));
    json.insert("english_name", QJsonValue(englishName));
    json.insert("name", QJsonValue(name));
    json.insert("primary", QJsonValue(isPrimary));

    return json;
}

void LanguageListItem::setName(const QString &newName)
{
    name = newName;
}

void LanguageListItem::setIsPrimary(bool newIsPrimary)
{
    isPrimary = newIsPrimary;
}

void LanguageListItem::setEnglishName(const QString &newEnglishName)
{
    englishName = newEnglishName;
}

void LanguageListItem::setId(const QString &newId)
{
    id = newId;
}
