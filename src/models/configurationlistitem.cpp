#include "configurationlistitem.h"

ConfigurationListItem::ConfigurationListItem(const QString &id, const QString &label, bool isPrimary) :
    id(id),
    label(label),
    isPrimary(isPrimary)
{

}

ConfigurationListItem::ConfigurationListItem(const QJsonObject &json) :
    id(json["id"].toString()),
    label(json["label"].toString()),
    isPrimary(json["primary"].toBool())
{

}

ConfigurationListItem::ConfigurationListItem(const QJsonObject &json, bool isPrimary) :
    id(json["id"].toString()),
    label(json["label"].toString()),
    isPrimary(isPrimary)
{

}

ConfigurationListItem::ConfigurationListItem(const ConfigurationListItem &configuration) :
    id(QString(configuration.id)),
    label(QString(configuration.label)),
    isPrimary(configuration.isPrimary)
{

}

const QString &ConfigurationListItem::getId() const
{
    return id;
}

const QString &ConfigurationListItem::getLabel() const
{
    return label;
}

const QString ConfigurationListItem::getSection() const
{
    if (isPrimary || label.length() == 0) {
        return "";
    }
    return label.at(0);
}

bool ConfigurationListItem::getIsPrimary() const
{
    return isPrimary;
}

const QJsonObject ConfigurationListItem::toJson() const
{
    QJsonObject json;
    json.insert("id", QJsonValue(id));
    json.insert("label", QJsonValue(label));
    json.insert("primary", QJsonValue(isPrimary));

    return json;
}
