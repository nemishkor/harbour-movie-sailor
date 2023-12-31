#include "videoslist.h"

VideosList::VideosList(QObject *parent) : QAbstractListModel(parent)
{

}

int VideosList::rowCount(const QModelIndex &) const
{
    return items.size();
}

QVariant VideosList::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= items.count())
        return QVariant();
    const VideoListItem &item = items[index.row()];
    if(role == NameRole)
        return item.getName();
    if(role == KeyRole)
        return item.getKey();
    if(role == SiteRole)
        return item.getSite();
    if(role == TypeRole)
        return item.getType();
    if(role == OfficialRole)
        return item.getOfficial();
    return QVariant();
}

void VideosList::add(const VideoListItem &item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    items.append(item);
    endInsertRows();
    emit countChanged();
}

QHash<int, QByteArray> VideosList::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[KeyRole] = "key";
    roles[SiteRole] = "site";
    roles[TypeRole] = "type";
    roles[OfficialRole] = "official";
    return roles;
}
