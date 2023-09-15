#ifndef CONFIGURATIONLISTMODEL_H
#define CONFIGURATIONLISTMODEL_H

#include <QAbstractListModel>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QMutableListIterator>

#include "src/models/configurationlistitem.h"
#include "src/system.h"

class ConfigurationListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
public:
    enum ConfigurationRoles {
        IdRole = Qt::UserRole + 1,
        LabelRole,
        SectionRole,
        PrimaryRole
    };
    explicit ConfigurationListModel(System &system, QObject *parent);
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void add(const ConfigurationListItem &item);
    void prepend(const ConfigurationListItem &item);
    void removeOneById(const QString &id);

    void fillFromCache(const QJsonDocument &json);
    const QJsonDocument fillFromAPI(const QJsonDocument &json);

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    System &system;
    QList<ConfigurationListItem> items;

signals:
    void countChanged();
};

#endif // CONFIGURATIONLISTMODEL_H
