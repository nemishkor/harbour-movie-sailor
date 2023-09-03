#include "personlistmodel.h"

PersonListModel::PersonListModel(QObject *parent) : QAbstractListModel(parent)
{

}

int PersonListModel::rowCount(const QModelIndex &) const
{
    return items.size();
}

QVariant PersonListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= items.count())
        return QVariant();
    const PersonListItem &item = items[index.row()];
    if(role == IdRole)
        return item.getId();
    if(role == CreditIdTole)
        return item.getCreditId();
    if(role == NameRole)
        return item.getName();
    if(role == GenderRole)
        return item.getGender();
    if(role == ProfilePathRole)
        return item.getProfilePath();
    return QVariant();
}

void PersonListModel::add(const PersonListItem &item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    items << item;
    endInsertRows();
}

void PersonListModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, items.count() - 1);
    items.clear();
    endRemoveRows();
}

QHash<int, QByteArray> PersonListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[CreditIdTole] = "creditRole";
    roles[NameRole] = "name";
    roles[GenderRole] = "gender";
    roles[ProfilePathRole] = "profilePath";
    return roles;
}
