#ifndef VIDEOSLIST_H
#define VIDEOSLIST_H

#include <QAbstractListModel>

#include "src/models/videolistitem.h"

class VideosList : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)

public:
    VideosList(QObject *parent);

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    void add(const VideoListItem &item);

signals:
    void countChanged();

protected:
    enum VideoRoles {
        NameRole = Qt::DisplayRole,
        KeyRole = Qt::UserRole + 1,
        SiteRole,
        TypeRole,
        OfficialRole
    };
    QList<VideoListItem> items;
    QHash<int, QByteArray> roleNames() const override;
};

#endif // VIDEOSLIST_H
