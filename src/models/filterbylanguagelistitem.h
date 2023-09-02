#ifndef FILTERBYLANGUAGELISTITEM_H
#define FILTERBYLANGUAGELISTITEM_H

#include <QString>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>


class FilterByLanguageListItem
{
public:
    FilterByLanguageListItem();
    FilterByLanguageListItem(const QString &id);
    FilterByLanguageListItem(const QJsonObject &json);
    FilterByLanguageListItem(const FilterByLanguageListItem &language);
    FilterByLanguageListItem(FilterByLanguageListItem &language, bool isPrimary);

    bool operator==(const FilterByLanguageListItem &other);

    const QString &getId() const;
    void setId(const QString &newId);

    const QString &getEnglishName() const;
    void setEnglishName(const QString &newEnglishName);

    const QString &getName() const;
    void setName(const QString &newName);

    const QString getSection() const;

    bool getIsPrimary() const;
    void setIsPrimary(bool newIsPrimary);

    const QJsonObject toJson() const;

private:
    QString id;
    QString englishName;
    QString name;
    bool isPrimary = false;
};

#endif // FILTERBYLANGUAGELISTITEM_H
