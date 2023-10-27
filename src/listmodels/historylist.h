#ifndef HISTORYLIST_H
#define HISTORYLIST_H

#include <QAbstractListModel>
#include <QDebug>
#include <QList>

#include "src/models/medialistitem.h"

class HistoryList : public QAbstractListModel
{
public:
    HistoryList(QObject *parent);

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

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
        KnownForRole
    };
    QList<MediaListItem> items;
    QHash<int, QByteArray> roleNames() const override;
    bool dirty;
};

#endif // HISTORYLIST_H
