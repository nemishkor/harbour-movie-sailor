#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <QString>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>


class Language
{
public:
    Language();
    Language(const QJsonObject &json);
    Language(const Language &language);
    Language(Language &language, bool isPrimary);

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

#endif // LANGUAGE_H
