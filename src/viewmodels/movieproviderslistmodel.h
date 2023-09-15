#ifndef MOVIEPROVIDERSLISTMODEL_H
#define MOVIEPROVIDERSLISTMODEL_H

#include <QAbstractListModel>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>

#include "src/models/movieprovider.h"

class MovieProvidersListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
public:
    enum MovieProviderRoles {
        CheckStateRole = Qt::CheckStateRole,
        IdRole = Qt::UserRole + 1,
        NameRole,
        LogoRole
    };

    explicit MovieProvidersListModel(QObject *parent);

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    Q_INVOKABLE bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    void add(const MovieProvider &item);
    void clear();
    void fillFromCache(const QJsonDocument &json);
    const QJsonDocument fillFromAPI(const QJsonDocument &json);
    QString toQueryString() const;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<MovieProvider> items;

signals:
    void countChanged();
};

#endif // MOVIEPROVIDERSLISTMODEL_H
