#include "tvnetworkslist.h"

TVNetworksList::TVNetworksList(QObject *parent) : QAbstractListModel(parent)
{

}

int TVNetworksList::rowCount(const QModelIndex &) const
{
    return items.size();
}

QVariant TVNetworksList::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= items.count())
        return QVariant();
    const TVNetworkListItem &item = items[index.row()];
    if(role == IdRole)
        return item.getId();
    if(role == NameRole)
        return item.getName();
    return QVariant();
}

void TVNetworksList::add(const TVNetworkListItem &item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    items.append(item);
    endInsertRows();
}

QHash<int, QByteArray> TVNetworksList::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[NameRole] = "name";
    return roles;
}
