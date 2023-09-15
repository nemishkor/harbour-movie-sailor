#include "countrieslistmodel.h"

CountriesListModel::CountriesListModel(QObject *parent) : QAbstractListModel(parent)
{

}

int CountriesListModel::rowCount(const QModelIndex &) const
{
    return items.size();
}

QVariant CountriesListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= items.count())
        return QVariant();
    const CountryListItem &item = items[index.row()];
    if(role == IdRole)
        return item.getId();
    if(role == NameRole)
        return item.getName();
    return QVariant();
}

void CountriesListModel::add(const CountryListItem &item)
{
    qDebug() << "CountriesListModel: add";
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    items << item;
    endInsertRows();
}

void CountriesListModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, items.count() - 1);
    items.clear();
    endRemoveRows();
}

QHash<int, QByteArray> CountriesListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[NameRole] = "name";
    return roles;
}
