#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QString>
#include <QJsonObject>
#include <QJsonValue>


class Configuration
{
public:
    Configuration(const QString &id, const QString &label, bool isPrimary);
    Configuration(const QJsonObject &json);
    Configuration(const QJsonObject &json, bool isPrimary);
    Configuration(const Configuration &configuration);

    const QString &getId() const;
    const QString &getLabel() const;
    const QString getSection() const;
    bool getIsPrimary() const;

    const QJsonObject toJson() const;


private:
    QString id;
    QString label;
    bool isPrimary = false;
};

#endif // CONFIGURATION_H
