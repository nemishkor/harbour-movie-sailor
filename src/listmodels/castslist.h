#ifndef CASTSLIST_H
#define CASTSLIST_H

#include <QAbstractListModel>

#include "src/models/castlistitem.h"

class CastsList : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)

public:
    CastsList(QObject *parent);

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void add(const CastListItem &item);
    void clear();

    const QList<CastListItem> &getItems() const;

signals:
    void countChanged();

protected:
    enum CastRoles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        OriginalNameRole,
        ProfilePathRole,
        CharacterRole,
        OrderRole
    };
    QList<CastListItem> items;
    QHash<int, QByteArray> roleNames() const override;
};

#endif // CASTSLIST_H
