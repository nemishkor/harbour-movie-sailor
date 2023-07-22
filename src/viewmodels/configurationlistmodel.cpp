#include "configurationlistmodel.h"

ConfigurationListModel::ConfigurationListModel(QObject *parent) : QAbstractListModel(parent)
{

}

int ConfigurationListModel::rowCount(const QModelIndex &) const{
    return items.size();
}

QVariant ConfigurationListModel::data(const QModelIndex &index, int role) const{
    if (index.row() < 0 || index.row() >= items.count())
        return QVariant();
    const Configuration &item = items[index.row()];
    if(role == IdRole)
        return item.getId();
    if(role == LabelRole)
        return item.getLabel();
    if(role == SectionRole)
        return item.getSection();
    if(role == PrimaryRole)
        return item.getIsPrimary();
    return QVariant();
}

void ConfigurationListModel::add(const Configuration &item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    items << item;
    endInsertRows();
    emit countChanged();
}

QHash<int, QByteArray> ConfigurationListModel::roleNames() const{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[LabelRole] = "label";
    roles[SectionRole] = "section";
    roles[PrimaryRole] = "isPrimary";
    return roles;
}
