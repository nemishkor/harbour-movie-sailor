#include "networkslistmodel.h"

NetworksListModel::NetworksListModel(QObject *parent) : QAbstractListModel(parent)
{

}

int NetworksListModel::rowCount(const QModelIndex &) const
{
    return items.size();
}

QVariant NetworksListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= items.count())
        return QVariant();
    const NetworkListItem &item = items[index.row()];
    if(role == IdRole)
        return item.getId();
    if(role == LogoPathRole)
        return item.getLogoPath();
    if(role == NameRole)
        return item.getName();
    if(role == OriginCountryRole)
        return item.getOriginCountry();
    return QVariant();
}

void NetworksListModel::add(const NetworkListItem &item)
{
    qDebug() << "NetworksListModel: add";
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    items << item;
    endInsertRows();
}

void NetworksListModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, items.count() - 1);
    items.clear();
    endRemoveRows();
}

QHash<int, QByteArray> NetworksListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[LogoPathRole] = "logoPath";
    roles[NameRole] = "name";
    roles[OriginCountryRole] = "originCountry";
    return roles;
}
