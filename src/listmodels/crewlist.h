#ifndef CREWLIST_H
#define CREWLIST_H

#include <QAbstractListModel>

#include "src/models/crewlistitem.h"

class CrewList : public QAbstractListModel
{
    Q_OBJECT

public:
    CrewList(QObject *parent);

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void add(const CrewListItem &item);
    void clear();

protected:
    enum CrewRoles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        OriginalNameRole,
        ProfilePathRole,
        DepartmentRole,
        JobRole
    };
    QList<CrewListItem> items;
    QHash<int, QByteArray> roleNames() const override;

};

#endif // CREWLIST_H
