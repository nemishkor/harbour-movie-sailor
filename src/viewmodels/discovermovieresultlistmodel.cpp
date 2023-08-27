#include "discovermovieresultlistmodel.h"

DiscoverMovieResultListModel::DiscoverMovieResultListModel(QObject *parent) :
    QAbstractListModel(parent),
    totalPages(-1)
{

}

int DiscoverMovieResultListModel::rowCount(const QModelIndex &) const
{
    return items.size();
}

QVariant DiscoverMovieResultListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= items.count())
        return QVariant();
    const DiscoverMovieResultItem &item = items[index.row()];
    if(role == IdRole)
        return item.getId();
    if(role == AdultRole)
        return item.getAdult();
    if(role == BackdropPathRole)
        return item.getBackdropPath();
    if(role == GenresRole)
        return item.getGenres();
    if(role == OriginalTitleRole)
        return item.getTitle();
    if(role == OverviewRole)
        return item.getOverview();
    if(role == PosterPathRole)
        return item.getPosterPath();
    if(role == ReleaseDateRole)
        return item.getReleaseDate();
    if(role == TitleRole)
        return item.getTitle();
    if(role == VoteAvarageRole)
        return item.getVoteAvarage();
    if(role == VoteCountRole)
        return item.getVoteCount();

    return QVariant();
}

void DiscoverMovieResultListModel::add(const DiscoverMovieResultItem &item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    items.insert(item.getId(), item);
    endInsertRows();
    emit countChanged();
}

void DiscoverMovieResultListModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, items.count() - 1);
    items.clear();
    endRemoveRows();
    emit countChanged();
}

void DiscoverMovieResultListModel::fillFromAPI(const QJsonDocument &json, const QList<Genre> &allGenres)
{
    qDebug() << "fill discovery movie results from API";

    QJsonObject object = json.object();

    setTotalPages(object["total_pages"].toInt());

    QJsonArray jsonItems = object["results"].toArray();

    for (QJsonArray::const_iterator it = jsonItems.constBegin(); it != jsonItems.constEnd(); it++) {
        QJsonObject jsonObj = (*it).toObject();
        QStringList genreNames;
        QJsonArray genreIds = jsonObj["genre_ids"].toArray();
        for (QJsonArray::const_iterator genresIt = genreIds.constBegin(); genresIt != genreIds.constEnd(); genresIt++) {
            int pos = allGenres.indexOf(Genre(genresIt->toInt(), ""));
            if (pos != -1) {
                Genre genre = allGenres.at(pos);
                genreNames.append(genre.getName());
            }
        }
        add(DiscoverMovieResultItem(
            jsonObj["adult"].toBool(),
            jsonObj["backdrop_path"].toString(),
            genreNames,
            jsonObj["id"].toInt(),
            jsonObj["original_title"].toString(),
            jsonObj["overview"].toString(),
            jsonObj["poster_path"].toString(),
            jsonObj["release_date"].toString(),
            jsonObj["title"].toString(),
            jsonObj["vote_average"].toDouble(),
            jsonObj["vote_count"].toInt()));
    }
}

int DiscoverMovieResultListModel::getTotalPages() const
{
    return totalPages;
}

void DiscoverMovieResultListModel::setTotalPages(int newTotalPages)
{
    if (totalPages == newTotalPages)
        return;
    totalPages = newTotalPages;
    emit totalPagesChanged();
}

QHash<int, QByteArray> DiscoverMovieResultListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[AdultRole] = "adult";
    roles[BackdropPathRole] = "backdropPath";
    roles[GenresRole] = "genres";
    roles[OriginalTitleRole] = "originalTitle";
    roles[OverviewRole] = "overview";
    roles[PosterPathRole] = "posterPath";
    roles[ReleaseDateRole] = "releaseDate";
    roles[TitleRole] = "title";
    roles[VoteAvarageRole] = "voteAvarage";
    roles[VoteCountRole] = "voteCount";
    return roles;
}
