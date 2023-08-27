#ifndef DISCOVERMOVIERESULTLISTMODEL_H
#define DISCOVERMOVIERESULTLISTMODEL_H

#include <QAbstractListModel>
#include <QDebug>
#include <QList>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "src/models/discovermovieresultitem.h"
#include "src/models/genre.h"

class DiscoverMovieResultListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
    Q_PROPERTY(int totalPages READ getTotalPages WRITE setTotalPages NOTIFY totalPagesChanged)

public:
    explicit DiscoverMovieResultListModel(QObject *parent);
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void add(const DiscoverMovieResultItem &item);
    Q_INVOKABLE void clear();
    void fillFromAPI(const QJsonDocument &json, const QList<Genre> &genres);

    int getTotalPages() const;
    void setTotalPages(int newTotalPages);

protected:
    enum DiscoveryMovieResultsRoles {
        IdRole = Qt::UserRole + 1,
        AdultRole,
        BackdropPathRole,
        GenresRole,
        OriginalTitleRole,
        OverviewRole,
        PosterPathRole,
        ReleaseDateRole,
        TitleRole,
        VoteAvarageRole,
        VoteCountRole
    };
    int totalPages;
    QList<DiscoverMovieResultItem> items;
    QHash<int, QByteArray> roleNames() const override;

signals:
    void countChanged();
    void totalPagesChanged();
};

#endif // DISCOVERMOVIERESULTLISTMODEL_H
