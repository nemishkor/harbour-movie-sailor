#include "filterbylanguagelistitem.h"

FilterByLanguageListItem::FilterByLanguageListItem()
{

}

FilterByLanguageListItem::FilterByLanguageListItem(const QString &id) :
    id(id)
{

}

FilterByLanguageListItem::FilterByLanguageListItem(const FilterByLanguageListItem &language) :
    id(QString(language.id)),
    englishName(QString(language.englishName)),
    name(QString(language.name)),
    isPrimary(language.isPrimary)
{
//    qDebug() << "copy Language" << id;
}

FilterByLanguageListItem::FilterByLanguageListItem(FilterByLanguageListItem &language, bool isPrimary) :
    id(QString(language.id)),
    englishName(QString(language.englishName)),
    name(QString(language.name)),
    isPrimary(isPrimary)
{

}

bool FilterByLanguageListItem::operator==(const FilterByLanguageListItem &other)
{
    return id == other.id;
}

FilterByLanguageListItem::FilterByLanguageListItem(const QJsonObject &json) :
    id(json["iso_639_1"].toString()),
    englishName(json["english_name"].toString()),
    name(json["name"].toString()),
    isPrimary(json["primary"].toBool())
{

}

const QString &FilterByLanguageListItem::getId() const
{
    return id;
}

const QString &FilterByLanguageListItem::getEnglishName() const
{
    return englishName;
}

const QString &FilterByLanguageListItem::getName() const
{
    return name;
}

const QString FilterByLanguageListItem::getSection() const
{
    if (isPrimary || englishName.length() == 0 || id == "xx") {
        return "";
    }
    return englishName.at(0);
}

bool FilterByLanguageListItem::getIsPrimary() const
{
    return isPrimary;
}

const QJsonObject FilterByLanguageListItem::toJson() const
{
    QJsonObject json;
    json.insert("iso_639_1", QJsonValue(id));
    json.insert("english_name", QJsonValue(englishName));
    json.insert("name", QJsonValue(name));
    json.insert("primary", QJsonValue(isPrimary));

    return json;
}

void FilterByLanguageListItem::setName(const QString &newName)
{
    name = newName;
}

void FilterByLanguageListItem::setIsPrimary(bool newIsPrimary)
{
    isPrimary = newIsPrimary;
}

void FilterByLanguageListItem::setEnglishName(const QString &newEnglishName)
{
    englishName = newEnglishName;
}

void FilterByLanguageListItem::setId(const QString &newId)
{
    id = newId;
}
