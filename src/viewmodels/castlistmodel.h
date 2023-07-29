#ifndef CASTLISTMODEL_H
#define CASTLISTMODEL_H

#include <QAbstractListModel>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>

#include "src/models/personlistitem.h"

class CastListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
public:
    enum CastRoles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        KnownForDepartment,
        ProfilePath
    };
    explicit CastListModel(QObject *parent);

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void add(const PersonListItem &item);
    void clear();
    Q_INVOKABLE void remove(int id);

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<PersonListItem> items;

signals:
    void countChanged();
};

#endif // CASTLISTMODEL_H
