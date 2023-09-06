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
    const Cast &item = items[index.row()];
    if(role == IdRole)
        return item.getId();
    if(role == NameRole)
        return item.getName();
    if(role == OriginalNameRole)
        return item.getOriginalName();
    if(role == ProfilePathRole)
        return item.getProfilePath();
    if(role == CastIdRole)
        return item.getCastId();
    if(role == CharacterRole)
        return item.getCharacter();
    if(role == CreditIdRole)
        return item.getCreditId();
    return QVariant();
}

void CastsList::add(const Cast &item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    items.insert(item.getId(), item);
    endInsertRows();
}

void CastsList::clear()
{
    beginRemoveRows(QModelIndex(), 0, items.count() - 1);
    items.clear();
    endRemoveRows();
}

QHash<int, QByteArray> CastsList::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[NameRole] = "name";
    roles[OriginalNameRole] = "originalName";
    roles[ProfilePathRole] = "profilePath";
    roles[CastIdRole] = "castId";
    roles[CharacterRole] = "character";
    roles[CreditIdRole] = "creditId";
    return roles;
}
