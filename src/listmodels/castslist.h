#ifndef CASTSLIST_H
#define CASTSLIST_H

#include <QAbstractListModel>

#include "src/models/cast.h"

class CastsList : public QAbstractListModel
{
    Q_OBJECT

public:
    CastsList(QObject *parent);

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void add(const Cast &item);
    void clear();

protected:
    enum CastRoles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        OriginalNameRole,
        ProfilePathRole,
        CharacterRole,
        OrderRole
    };
    QList<Cast> items;
    QHash<int, QByteArray> roleNames() const override;
};

#endif // CASTSLIST_H
