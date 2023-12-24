#ifndef TVNETWORKSLIST_H
#define TVNETWORKSLIST_H

#include <QAbstractListModel>

#include "src/models/tvnetwork.h"

class TVNetworksList : public QAbstractListModel
{
    Q_OBJECT

public:
    TVNetworksList(QObject *parent);

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

protected:
    enum TVNetworksRoles {
        IdRole = Qt::UserRole + 1,
        NameRole
    };
    QList<TVNetwork> items;
    QHash<int, QByteArray> roleNames() const override;
};

#endif // TVNETWORKSLIST_H
