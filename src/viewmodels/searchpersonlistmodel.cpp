#include "searchpersonlistmodel.h"

SearchPersonListModel::SearchPersonListModel(QObject *parent) : QAbstractListModel(parent)
{

}

int SearchPersonListModel::rowCount(const QModelIndex &) const
{
    return items.size();
}

QVariant SearchPersonListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= items.count())
        return QVariant();
    const SearchPersonListItem &item = items[index.row()];
    if (role == CheckStateRole)
        return item.getChecked();
    if (role == IdRole)
        return item.getId();
    if (role == NameRole)
        return item.getName();
    if (role == KnownForDepartment)
        return item.getKnownForDepartment();
    if (role == ProfilePath)
        return item.getProfilePath();
    if (role == RoleRole)
        return item.getRole();
    return QVariant();
}

bool SearchPersonListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.row() < 0 || index.row() >= items.count())
        return false;

    SearchPersonListItem &item = items[index.row()];
    if(role == CheckStateRole){
        item.setChecked(value.toBool());
        emit dataChanged(index, index, QVector<int>{role});
        return true;
    }
    if(role == RoleRole){
        item.setRole(static_cast<SearchPersonListItem::PersonRole>(value.toInt()));
        emit dataChanged(index, index, QVector<int>{role});
        return true;
    }

    return false;
}

Qt::ItemFlags SearchPersonListModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return Qt::ItemIsUserCheckable;
}

void SearchPersonListModel::add(const SearchPersonListItem &item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    items.append(item);
    endInsertRows();
    emit countChanged();
}

void SearchPersonListModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, items.count() - 1);
    items.clear();
    endRemoveRows();
    emit countChanged();
}

void SearchPersonListModel::fillFromCache(const QJsonDocument &json)
{
    QJsonArray jsonItems = json.array();
    for (QJsonValue jsonItem : jsonItems) {
        QJsonObject jsonObj = jsonItem.toObject();
        SearchPersonListItem model;
        model.setId(jsonObj["id"].toInt());
        model.setName(jsonObj["name"].toString());
        model.setKnownForDepartment(jsonObj["knownForDepartment"].toString());
        QJsonValue profilePath = jsonObj["profilePath"];
        if (profilePath.isString())
            model.setProfilePath(profilePath.toString());
        add(model);
    }
}

const QJsonDocument SearchPersonListModel::fillFromAPI(const QJsonDocument &json)
{
    QJsonArray jsonItems = json.object()["results"].toArray();
    QJsonArray newJsonItems;

    for (QJsonArray::const_iterator it = jsonItems.constBegin(); it != jsonItems.constEnd(); it++) {
        QJsonObject jsonObj = (*it).toObject();
        SearchPersonListItem model;
        model.setId(jsonObj["id"].toInt());
        model.setName(jsonObj["name"].toString());
        model.setKnownForDepartment(jsonObj["known_for_department"].toString());
        QJsonValue profilePath = jsonObj["profile_path"];
        if (profilePath.isString())
            model.setProfilePath(jsonObj["profile_path"].toString());
        add(model);
        QJsonObject newJsonItem;
        newJsonItem.insert("id", model.getId());
        newJsonItem.insert("name", model.getName());
        newJsonItem.insert("knownForDepartment", model.getKnownForDepartment());
        newJsonItem.insert("profilePath", model.getProfilePath().isEmpty() ? QJsonValue() : model.getProfilePath());
        newJsonItems.append(newJsonItem);
    }

    return QJsonDocument(newJsonItems);
}

QHash<int, QByteArray> SearchPersonListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[CheckStateRole] = "checked";
    roles[IdRole] = "id";
    roles[NameRole] = "name";
    roles[KnownForDepartment] = "knownForDepartment";
    roles[ProfilePath] = "profilePath";
    roles[RoleRole] = "role";
    return roles;
}

const QList<SearchPersonListItem> &SearchPersonListModel::getItems() const
{
    return items;
}
