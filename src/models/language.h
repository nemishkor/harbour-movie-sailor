#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <QString>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>


class Language
{
public:
    Language(const QString &id, const QString &englishName, const QString &name, bool isPrimary);
    Language(const QJsonObject &json);
    Language(const QJsonObject &json, bool isPrimary);
    Language(const Language &language);

    bool operator <(const Language& other) const;

    const QString &getId() const;

    const QString &getEnglishName() const;

    const QString &getName() const;

    const QString getSection() const;

    bool getIsPrimary() const;

    const QJsonObject toJson() const;

private:
    QString id;
    QString englishName;
    QString name;
    bool isPrimary = false;
};

#endif // LANGUAGE_H
