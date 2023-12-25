#ifndef MOVIESLISTMODEL_H
#define MOVIESLISTMODEL_H

#include <QAbstractListModel>
#include <QDateTime>
#include <QDebug>
#include <QList>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLocale>

#include "src/models/medialistitem.h"
#include "src/models/genre.h"
#include "src/models/searchform.h"

class MediaListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
    Q_PROPERTY(int totalPages READ getTotalPages WRITE setTotalPages NOTIFY totalPagesChanged)

public:
    MediaListModel(QObject *parent);
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void add(const MediaListItem &item);
    void add(QList<Genre> &allGenres, const QJsonObject &jsonObj, MediaListItem::MediaType defaultMediaType);
    void add(QList<Genre> &allGenres, const QJsonObject &jsonObj, MediaListItem::MediaType defaultMediaType, QDateTime historyDateTime);
    Q_INVOKABLE void clear();
    void fillFromAPI(QList<Genre> &allGenres, const QJsonDocument &json, MediaListItem::MediaType defaultMediaType = MediaListItem::MovieType);

    int getTotalPages() const;
    void setTotalPages(int newTotalPages);

    const QList<MediaListItem> &getItems() const;

    bool getDirty() const;
    void setDirty(bool newDirty);

protected:
    enum DiscoveryMovieResultsRoles {
        IdRole = Qt::UserRole + 1,
        MediaTypeRole,
        AdultRole,
        BackdropPathRole,
        GenresRole,
        OriginalNameRole,
        OverviewRole,
        ImagePathRole,
        ReleaseYearRole,
        NameRole,
        VoteAvarageRole,
        VoteCountRole,
        KnownForDepartmentRole,
        KnownForRole,
        FirstAirDateRole,
        HistoryDateTimeRole,
    };
    QLocale locale;
    int totalPages;
    QList<MediaListItem> items;
    QHash<int, QByteArray> roleNames() const override;
    bool dirty;
    QString historyDateTimeFormat;
    MediaListItem createListItem(QList<Genre> &allGenres, const QJsonObject &jsonObj, MediaListItem::MediaType defaultMediaType);

signals:
    void countChanged();
    void totalPagesChanged();
};

#endif // MOVIESLISTMODEL_H
