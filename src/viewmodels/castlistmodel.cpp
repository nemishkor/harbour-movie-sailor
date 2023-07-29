#include "castlistmodel.h"

CastListModel::CastListModel(QObject *parent) : QAbstractListModel(parent)
{

}

int CastListModel::rowCount(const QModelIndex &) const
{
    return items.size();
}

QVariant CastListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= items.count())
        return QVariant();
    const PersonListItem &item = items[index.row()];
    if (role == IdRole)
        return item.getId();
    if (role == NameRole)
        return item.getName();
    if (role == KnownForDepartment)
        return item.getKnownForDepartment();
    if (role == ProfilePath)
        return item.getProfilePath();
    return QVariant();
}

void CastListModel::add(const PersonListItem &item)
{
    for (QList<PersonListItem>::const_iterator it = items.constBegin(); it != items.constEnd(); it++) {
        if (item.getId() == (*it).getId()) {
            return;
        }
    }
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    items.append(item);
    endInsertRows();
    emit countChanged();
}

void CastListModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, items.count() - 1);
    items.clear();
    endRemoveRows();
    emit countChanged();
}

void CastListModel::remove(int id)
{
    for (int row = 0; row < items.count(); row++) {
        if (id == items.at(row).getId()) {
            beginRemoveRows(QModelIndex(), row, row);
            items.removeAt(row);
            endRemoveRows();
            emit countChanged();
            break;
        }
    }
}

QHash<int, QByteArray> CastListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[NameRole] = "name";
    roles[KnownForDepartment] = "knownForDepartment";
    roles[ProfilePath] = "profilePath";
    return roles;
}
