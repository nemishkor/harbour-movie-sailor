#include "companieslistmodel.h"

CompaniesListModel::CompaniesListModel(QObject *parent) :
    QAbstractListModel(parent)
{

}

int CompaniesListModel::rowCount(const QModelIndex &) const
{
    return items.size();
}

QVariant CompaniesListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= items.count())
        return QVariant();
    const Company &item = items[index.row()];
    if(role == IdRole)
        return item.getId();
    if(role == LogoRole)
        return item.getLogo();
    if(role == NameRole)
        return item.getName();
    if(role == CountryRole)
        return item.getCountry();
    return QVariant();
}

void CompaniesListModel::add(const Company &item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    items.insert(item.getId(), item);
    endInsertRows();
}

void CompaniesListModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, items.count() - 1);
    items.clear();
    endRemoveRows();
}

QHash<int, QByteArray> CompaniesListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[LogoRole] = "logo";
    roles[NameRole] = "name";
    roles[CountryRole] = "country";
    return roles;
}
