#include "languageslistmodel.h"

LanguagesListModel::LanguagesListModel(QObject *parent) : QAbstractListModel(parent)
{

}

int LanguagesListModel::rowCount(const QModelIndex &) const{
    return items.size();
}

QVariant LanguagesListModel::data(const QModelIndex &index, int role) const{
    if (index.row() < 0 || index.row() >= items.count())
        return QVariant();
    const Language &language = items[index.row()];
    if(role == IdRole)
        return language.getId();
    if(role == EnglishNameRole)
        return language.getEnglishName();
    if(role == NameRole)
        return language.getName();
    if(role == SectionRole)
        return language.getSection();
    if(role == PrimaryRole)
        return language.getIsPrimary();
    return QVariant();
}

void LanguagesListModel::add(const Language &language)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    items << language;
    endInsertRows();
    emit countChanged();
}

QHash<int, QByteArray> LanguagesListModel::roleNames() const{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[EnglishNameRole] = "englishName";
    roles[NameRole] = "name";
    roles[SectionRole] = "section";
    roles[PrimaryRole] = "isPrimary";
    return roles;
}
