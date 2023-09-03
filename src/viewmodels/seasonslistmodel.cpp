#include "seasonslistmodel.h"

SeasonsListModel::SeasonsListModel(QObject *parent) : QAbstractListModel(parent)
{

}

int SeasonsListModel::rowCount(const QModelIndex &) const
{
    return items.size();
}

QVariant SeasonsListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= items.count())
        return QVariant();
    const SeasonListItem &item = items[index.row()];
    if(role == IdRole)
        return item.getId();
    if(role == AirDateTole)
        return item.getAirDate();
    if(role == EpisodeCountRole)
        return item.getEpisodeCount();
    if(role == NameRole)
        return item.getName();
    if(role == OverviewRole)
        return item.getOverview();
    if(role == PosterPathRole)
        return item.getPosterPath();
    if(role == SeasonNumberRole)
        return item.getSeasonNumber();
    if(role == VoteAvarageRole)
        return item.getVoteAvarage();
    return QVariant();
}

void SeasonsListModel::add(const SeasonListItem &item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    items << item;
    endInsertRows();
}

void SeasonsListModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, items.count() - 1);
    items.clear();
    endRemoveRows();
}

QHash<int, QByteArray> SeasonsListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[AirDateTole] = "airDate";
    roles[EpisodeCountRole] = "episodeCount";
    roles[NameRole] = "name";
    roles[OverviewRole] = "overview";
    roles[PosterPathRole] = "posterPath";
    roles[SeasonNumberRole] = "seasonNumber";
    roles[VoteAvarageRole] = "voteAvarage";
    return roles;
}
