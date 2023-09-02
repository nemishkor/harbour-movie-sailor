#include "languageslistmodel.h"

LanguagesListModel::LanguagesListModel(QObject *parent) : QAbstractListModel(parent)
{

}

int LanguagesListModel::rowCount(const QModelIndex &) const
{
    return items.size();
}

QVariant LanguagesListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= items.count())
        return QVariant();
    const LanguageListItem &language = items[index.row()];
    if(role == IdRole)
        return language.getId();
    if(role == NameRole)
        return language.getName();
    return QVariant();
}

void LanguagesListModel::add(const LanguageListItem &language)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    items.append(language);
    endInsertRows();
}

void LanguagesListModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, items.count() - 1);
    items.clear();
    endRemoveRows();
}

QHash<int, QByteArray> LanguagesListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[NameRole] = "name";
    return roles;
}
