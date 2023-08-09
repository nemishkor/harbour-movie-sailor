#ifndef SEARCHPERSONLISTMODEL_H
#define SEARCHPERSONLISTMODEL_H

#include <QAbstractListModel>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>

#include "src/models/searchpersonlistitem.h"

class SearchPersonListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
public:
    enum PersonRoles {
        CheckStateRole = Qt::CheckStateRole,
        IdRole = Qt::UserRole + 1,
        NameRole,
        KnownForDepartment,
        ProfilePath,
        RoleRole,
    };
    explicit SearchPersonListModel(QObject *parent);

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    Q_INVOKABLE bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    void add(const SearchPersonListItem &item);
    void clear();
    void fillFromCache(const QJsonDocument &json);
    const QJsonDocument fillFromAPI(const QJsonDocument &json);

    const QList<SearchPersonListItem> &getItems() const;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<SearchPersonListItem> items;

signals:
    void countChanged();
};

#endif // SEARCHPERSONLISTMODEL_H
