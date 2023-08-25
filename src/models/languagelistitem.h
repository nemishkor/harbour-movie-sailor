#ifndef LANGUAGELISTITEM_H
#define LANGUAGELISTITEM_H

#include <QString>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>


class LanguageListItem
{
public:
    LanguageListItem();
    LanguageListItem(const QJsonObject &json);
    LanguageListItem(const LanguageListItem &language);
    LanguageListItem(LanguageListItem &language, bool isPrimary);

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

#endif // LANGUAGELISTITEM_H
