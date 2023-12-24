#ifndef PROVIDERSLIST_H
#define PROVIDERSLIST_H

#include <QAbstractListModel>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>

#include "src/models/providerlistitem.h"

class ProvidersList : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)

public:
    enum ProviderRoles {
        IdRole = Qt::UserRole + 1,
        StateRole,
        NameRole,
        LogoRole
    };
    ProvidersList(QObject *parent);

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    Q_INVOKABLE bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    void add(const ProviderListItem &item);
    void clear();
    void fillFromCache(const QJsonDocument &json);
    const QJsonDocument fillFromAPI(const QJsonDocument &json);

    const QList<ProviderListItem> &getItems() const;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<ProviderListItem> items;

signals:
    void countChanged();
};

#endif // PROVIDERSLIST_H
