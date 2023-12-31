#include "castslist.h"

CastsList::CastsList(QObject *parent) : QAbstractListModel(parent)
{

}

int CastsList::rowCount(const QModelIndex &) const
{
    return items.size();
}

QVariant CastsList::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= items.count())
        return QVariant();
    const CastListItem &item = items[index.row()];
    if(role == IdRole)
        return item.getId();
    if(role == NameRole)
        return item.getName();
    if(role == OriginalNameRole)
        return item.getOriginalName();
    if(role == ProfilePathRole)
        return item.getProfilePath();
    if(role == CharacterRole)
        return item.getCharacter();
    return QVariant();
}

void CastsList::add(const CastListItem &item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    items.insert(item.getId(), item);
    endInsertRows();
    emit countChanged();
}

void CastsList::clear()
{
    beginRemoveRows(QModelIndex(), 0, items.count() - 1);
    items.clear();
    endRemoveRows();
    emit countChanged();
}

const QList<CastListItem> &CastsList::getItems() const
{
    return items;
}

QHash<int, QByteArray> CastsList::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[NameRole] = "name";
    roles[OriginalNameRole] = "originalName";
    roles[ProfilePathRole] = "profilePath";
    roles[CharacterRole] = "character";
    return roles;
}
