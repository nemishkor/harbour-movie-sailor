#ifndef CONFIGURATIONLISTITEM_H
#define CONFIGURATIONLISTITEM_H

#include <QString>
#include <QJsonObject>
#include <QJsonValue>


class ConfigurationListItem
{
public:
    ConfigurationListItem(const QString &id, const QString &label, bool isPrimary);
    ConfigurationListItem(const QJsonObject &json);
    ConfigurationListItem(const QJsonObject &json, bool isPrimary);
    ConfigurationListItem(const ConfigurationListItem &configuration);

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

#endif // CONFIGURATIONLISTITEM_H
