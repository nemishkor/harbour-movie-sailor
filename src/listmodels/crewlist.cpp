#include "crewlist.h"

CrewList::CrewList(QObject *parent) : QAbstractListModel(parent)
{

}

int CrewList::rowCount(const QModelIndex &) const
{
    return items.size();
}

QVariant CrewList::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= items.count())
        return QVariant();
    const CrewListItem &item = items[index.row()];
    if(role == IdRole)
        return item.getId();
    if(role == NameRole)
        return item.getName();
    if(role == OriginalNameRole)
        return item.getOriginalName();
    if(role == ProfilePathRole)
        return item.getProfilePath();
    if(role == DepartmentRole)
        return item.getDepartment();
    if(role == JobRole)
        return item.getJob();
    return QVariant();
}

void CrewList::add(const CrewListItem &item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    items.insert(item.getId(), item);
    endInsertRows();
}

void CrewList::clear()
{
    beginRemoveRows(QModelIndex(), 0, items.count() - 1);
    items.clear();
    endRemoveRows();
}

QHash<int, QByteArray> CrewList::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[NameRole] = "name";
    roles[OriginalNameRole] = "originalName";
    roles[ProfilePathRole] = "profilePath";
    roles[DepartmentRole] = "department";
    roles[JobRole] = "job";
    return roles;
}
