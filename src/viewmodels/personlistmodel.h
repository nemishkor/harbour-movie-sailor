#ifndef PERSONLISTMODEL_H
#define PERSONLISTMODEL_H

#include <QAbstractListModel>

#include "src/models/personlistitem.h"

class PersonListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum PersonRoles {
        IdRole = Qt::UserRole + 1,
        CreditIdTole,
        NameRole,
        GenderRole,
        ProfilePathRole
    };
    PersonListModel(QObject *parent);
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void add(const PersonListItem &item);
    void clear();

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<PersonListItem> items;

};

#endif // PERSONLISTMODEL_H
