#ifndef PERSONSLISTMODEL_H
#define PERSONSLISTMODEL_H

#include <QAbstractListModel>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>

#include "src/models/personlistitem.h"

class PersonsListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
public:
    enum PersonRoles {
        CheckStateRole = Qt::CheckStateRole,
        IdRole = Qt::UserRole + 1,
        NameRole,
        KnownForDepartment,
        ProfilePath
    };
    explicit PersonsListModel(QObject *parent);

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    Q_INVOKABLE bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    void add(const PersonListItem &item);
    void clear();
    void fillFromCache(const QJsonDocument &json);
    const QJsonDocument fillFromAPI(const QJsonDocument &json);

    const QList<PersonListItem> &getItems() const;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<PersonListItem> items;

signals:
    void countChanged();
};

#endif // PERSONSLISTMODEL_H
