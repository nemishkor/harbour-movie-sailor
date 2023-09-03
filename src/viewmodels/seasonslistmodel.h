#ifndef SEASONSLISTMODEL_H
#define SEASONSLISTMODEL_H

#include <QAbstractListModel>

#include "src/models/seasonlistitem.h"

class SeasonsListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum SeasonsRoles {
        IdRole = Qt::UserRole + 1,
        AirDateTole,
        EpisodeCountRole,
        NameRole,
        OverviewRole,
        PosterPathRole,
        SeasonNumberRole,
        VoteAvarageRole
    };
    SeasonsListModel(QObject *parent);
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void add(const SeasonListItem &item);
    void clear();

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<SeasonListItem> items;
};

#endif // SEASONSLISTMODEL_H
