#include "medialistmodel.h"

MediaListModel::MediaListModel(QObject *parent) :
    QAbstractListModel(parent),
    totalPages(-1),
    dirty(true)
{

}

int MediaListModel::rowCount(const QModelIndex &) const
{
    return items.size();
}

QVariant MediaListModel::data(const QModelIndex &index, int role) const
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

void MediaListModel::add(const MediaListItem &item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    items.insert(item.getId(), item);
    endInsertRows();
    emit countChanged();
}

void MediaListModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, items.count() - 1);
    items.clear();
    endRemoveRows();
    emit countChanged();
}

void MediaListModel::fillFromAPI(const QJsonDocument &json, const QList<Genre> &allGenres, MediaListItem::MediaType defaultMediaType)
{
    qDebug() << "MediaListModel: fill media list from API";

    switch (defaultMediaType) {
    case MediaListItem::Unknown:
        qDebug() << "MediaListModel: default media type is unknown";
        break;
    case MediaListItem::MovieType:
        qDebug() << "MediaListModel: default media type is movie";
        break;
    case MediaListItem::TvType:
        qDebug() << "MediaListModel: default media type is TV";
        break;
    case MediaListItem::PersonType:
        qDebug() << "MediaListModel: default media type is person";
        break;

    }

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

        MediaListItem::MediaType mediaType = defaultMediaType;
        QString name = jsonObj["title"].toString();
        QString originalName = jsonObj["original_title"].toString();
        QString imagePath = jsonObj["poster_path"].toString();
        QStringList knownFor;

        if (jsonObj.contains("media_type")) {
            QString apiMediaType = jsonObj["media_type"].toString();
            if (apiMediaType == "movie")
                mediaType = MediaListItem::MovieType;
            else if (apiMediaType == "tv") {
                mediaType = MediaListItem::TvType;
            } else if (apiMediaType == "person") {
                mediaType = MediaListItem::PersonType;
            }
        }

        switch (mediaType) {
        case MediaListItem::Unknown:
            break;
        case MediaListItem::MovieType:
            break;
        case MediaListItem::TvType:
            name = jsonObj["name"].toString();
            originalName = jsonObj["original_name"].toString();
            break;
        case MediaListItem::PersonType:
            name = jsonObj["name"].toString();
            originalName = jsonObj["original_name"].toString();
            imagePath = jsonObj["profile_path"].toString();
            QJsonArray rawKnownFor = jsonObj["known_for"].toArray();
            for (QJsonArray::const_iterator knownForIt = rawKnownFor.constBegin(); knownForIt != rawKnownFor.constEnd(); knownForIt++) {
                QString knownForName = knownForIt->toObject()["title"].toString();
                if (knownForName.isEmpty())
                    knownForName = knownForIt->toObject()["name"].toString();
                knownFor.append(knownForName);
            }
            break;
        }

        add(MediaListItem(
            mediaType,
            jsonObj["adult"].toBool(),
            jsonObj["backdrop_path"].toString(),
            genreNames,
            jsonObj["id"].toInt(),
            originalName,
            jsonObj["overview"].toString(),
            imagePath,
            jsonObj["release_date"].toString().mid(0, 4),
            name,
            jsonObj["vote_average"].toDouble(),
            jsonObj["vote_count"].toInt(),
            jsonObj["known_for_department"].toString(),
            knownFor));
    }
    qDebug() << "MediaListModel: fill media list from API - done";
}

int MediaListModel::getTotalPages() const
{
    return totalPages;
}

void MediaListModel::setTotalPages(int newTotalPages)
{
    if (totalPages == newTotalPages)
        return;
    totalPages = newTotalPages;
    emit totalPagesChanged();
}

const QList<MediaListItem> &MediaListModel::getItems() const
{
    return items;
}

QHash<int, QByteArray> MediaListModel::roleNames() const
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

bool MediaListModel::getDirty() const
{
    return dirty;
}

void MediaListModel::setDirty(bool newDirty)
{
    dirty = newDirty;
}
