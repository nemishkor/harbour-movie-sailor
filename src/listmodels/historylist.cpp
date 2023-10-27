#include "historylist.h"

HistoryList::HistoryList(QObject *parent) :
    QAbstractListModel(parent),
    dirty(true)
{

}

int HistoryList::rowCount(const QModelIndex &) const
{
    return items.size();
}

QVariant HistoryList::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= items.count())
        return QVariant();
    const MediaListItem &item = items[index.row()];
    if(role == MediaTypeRole)
        return item.getMediaType();
    if(role == IdRole)
        return item.getId();
    if(role == AdultRole)
        return item.getAdult();
    if(role == BackdropPathRole)
        return item.getBackdropPath();
    if(role == GenresRole)
        return item.getGenres();
    if(role == OriginalNameRole)
        return item.getOriginalTitle();
    if(role == OverviewRole)
        return item.getOverview();
    if(role == ImagePathRole)
        return item.getPosterPath();
    if(role == ReleaseYearRole)
        return item.getReleaseYear();
    if(role == NameRole)
        return item.getTitle();
    if(role == VoteAvarageRole)
        return item.getVoteAvarage();
    if(role == VoteCountRole)
        return item.getVoteCount();
    if(role == KnownForDepartmentRole)
        return item.getKnownForDepartment();
    if(role == KnownForRole)
        return item.getKnownFor();

    return QVariant();
}

bool HistoryList::getDirty() const
{
    return dirty;
}

void HistoryList::setDirty(bool newDirty)
{
    dirty = newDirty;
}

QHash<int, QByteArray> HistoryList::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[MediaTypeRole] = "mediaType";
    roles[IdRole] = "id";
    roles[AdultRole] = "adult";
    roles[BackdropPathRole] = "backdropPath";
    roles[GenresRole] = "genres";
    roles[OriginalNameRole] = "originalName";
    roles[OverviewRole] = "overview";
    roles[ImagePathRole] = "imagePath";
    roles[ReleaseYearRole] = "releaseYear";
    roles[NameRole] = "name";
    roles[VoteAvarageRole] = "voteAvarage";
    roles[VoteCountRole] = "voteCount";
    roles[KnownForDepartmentRole] = "knownForDepartment";
    roles[KnownForRole] = "knownFor";
    return roles;
}
