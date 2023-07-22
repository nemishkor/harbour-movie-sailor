#include "configuration.h"

Configuration::Configuration(const QString &id, const QString &label, bool isPrimary) :
    id(id),
    label(label),
    isPrimary(isPrimary)
{

}

Configuration::Configuration(const QJsonObject &json) :
    id(json["id"].toString()),
    label(json["label"].toString()),
    isPrimary(json["primary"].toBool())
{

}

Configuration::Configuration(const QJsonObject &json, bool isPrimary) :
    id(json["id"].toString()),
    label(json["label"].toString()),
    isPrimary(isPrimary)
{

}

Configuration::Configuration(const Configuration &configuration) :
    id(QString(configuration.id)),
    label(QString(configuration.label)),
    isPrimary(configuration.isPrimary)
{

}

const QString &Configuration::getId() const
{
    return id;
}

const QString &Configuration::getLabel() const
{
    return label;
}

const QString Configuration::getSection() const
{
    if (isPrimary || label.length() == 0) {
        return "";
    }
    return label.at(0);
}

bool Configuration::getIsPrimary() const
{
    return isPrimary;
}

const QJsonObject Configuration::toJson() const
{
    QJsonObject json;
    json.insert("id", QJsonValue(id));
    json.insert("label", QJsonValue(label));
    json.insert("primary", QJsonValue(isPrimary));

    return json;
}
