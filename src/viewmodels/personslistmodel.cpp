#include "personslistmodel.h"

PersonsListModel::PersonsListModel(QObject *parent) : QAbstractListModel(parent)
{

}

int PersonsListModel::rowCount(const QModelIndex &) const
{
    return items.size();
}

QVariant PersonsListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= items.count())
        return QVariant();
    const PersonListItem &item = items[index.row()];
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
    return QVariant();
}

bool PersonsListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.row() < 0 || index.row() >= items.count())
        return false;

    PersonListItem &item = items[index.row()];
    if(role == CheckStateRole){
        item.setChecked(value.toBool());
        emit dataChanged(index, index, QVector<int>{role});
        return true;
    }

    return false;
}

Qt::ItemFlags PersonsListModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return Qt::ItemIsUserCheckable;
}

void PersonsListModel::add(const PersonListItem &item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    items.append(item);
    endInsertRows();
    emit countChanged();
}

void PersonsListModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, items.count() - 1);
    items.clear();
    endRemoveRows();
    emit countChanged();
}

void PersonsListModel::fillFromCache(const QJsonDocument &json)
{
    QJsonArray jsonItems = json.array();
    for (QJsonValue jsonItem : jsonItems) {
        QJsonObject jsonObj = jsonItem.toObject();
        PersonListItem model;
        model.setId(jsonObj["id"].toInt());
        model.setName(jsonObj["name"].toString());
        model.setKnownForDepartment(jsonObj["knownForDepartment"].toString());
        model.setProfilePath(jsonObj["profilePath"].toString());
        add(model);
    }
}

const QJsonDocument PersonsListModel::fillFromAPI(const QJsonDocument &json)
{
    QJsonArray jsonItems = json.object()["results"].toArray();
    QJsonArray newJsonItems;

    for (QJsonArray::const_iterator it = jsonItems.constBegin(); it != jsonItems.constEnd(); it++) {
        QJsonObject jsonObj = (*it).toObject();
        PersonListItem model;
        model.setId(jsonObj["id"].toInt());
        model.setName(jsonObj["name"].toString());
        model.setKnownForDepartment(jsonObj["known_for_department"].toString());
        model.setProfilePath(jsonObj["profile_path"].toString());
        add(model);
        QJsonObject newJsonItem;
        newJsonItem.insert("id", model.getId());
        newJsonItem.insert("name", model.getName());
        newJsonItem.insert("knownForDepartment", model.getKnownForDepartment());
        newJsonItem.insert("profilePath", model.getProfilePath());
        newJsonItems.append(newJsonItem);
    }

    return QJsonDocument(newJsonItems);
}

QHash<int, QByteArray> PersonsListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[CheckStateRole] = "checked";
    roles[IdRole] = "id";
    roles[NameRole] = "name";
    roles[KnownForDepartment] = "knownForDepartment";
    roles[ProfilePath] = "profilePath";
    return roles;
}

const QList<PersonListItem> &PersonsListModel::getItems() const
{
    return items;
}
