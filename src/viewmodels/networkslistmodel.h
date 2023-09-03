#ifndef NETWORKSLISTMODEL_H
#define NETWORKSLISTMODEL_H

#include <QAbstractListModel>

#include "src/models/networklistitem.h"

class NetworksListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum CountryRoles {
        IdRole = Qt::UserRole + 1,
        LogoPathRole,
        NameRole,
        OriginCountryRole
    };
    NetworksListModel(QObject *parent);
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void add(const NetworkListItem &item);
    void clear();

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<NetworkListItem> items;
};

#endif // NETWORKSLISTMODEL_H
