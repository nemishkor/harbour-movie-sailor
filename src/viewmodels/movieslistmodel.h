#ifndef MOVIESLISTMODEL_H
#define MOVIESLISTMODEL_H

#include <QAbstractListModel>
#include <QDebug>
#include <QList>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "src/models/movielistitem.h"
#include "src/models/genre.h"

class MoviesListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
    Q_PROPERTY(int totalPages READ getTotalPages WRITE setTotalPages NOTIFY totalPagesChanged)

public:
    explicit MoviesListModel(QObject *parent);
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void add(const MovieListItem &item);
    Q_INVOKABLE void clear();
    void fillFromAPI(const QJsonDocument &json, const QList<Genre> &genres);

    int getTotalPages() const;
    void setTotalPages(int newTotalPages);

    const QList<MovieListItem> &getItems() const;

    bool getDirty() const;
    void setDirty(bool newDirty);

protected:
    enum DiscoveryMovieResultsRoles {
        IdRole = Qt::UserRole + 1,
        AdultRole,
        BackdropPathRole,
        GenresRole,
        OriginalTitleRole,
        OverviewRole,
        PosterPathRole,
        ReleaseYearRole,
        TitleRole,
        VoteAvarageRole,
        VoteCountRole
    };
    int totalPages;
    QList<MovieListItem> items;
    QHash<int, QByteArray> roleNames() const override;
    bool dirty;

signals:
    void countChanged();
    void totalPagesChanged();
};

#endif // MOVIESLISTMODEL_H
