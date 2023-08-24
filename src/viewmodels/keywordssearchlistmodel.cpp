#include "keywordssearchlistmodel.h"

KeywordsSearchListModel::KeywordsSearchListModel(const QList<Keyword> &selection, QObject *parent) :
    QAbstractListModel(parent),
    selection(selection)
{

}

int KeywordsSearchListModel::rowCount(const QModelIndex &) const
{
    return items.size();
}

QVariant KeywordsSearchListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= items.count())
        return QVariant();
    const Keyword &item = items[index.row()];
    if (role == IdRole)
        return item.getId();
    if (role == NameRole)
        return item.getName();
    if (role == SelectedRole)
        return selection.contains(item);
    return QVariant();
}

void KeywordsSearchListModel::selectChanged(const Keyword &item)
{
    QModelIndex index = createIndex(items.indexOf(item), 0);

    if (index.row() < 0)
        return;

    emit dataChanged(index, index, QVector<int>{SelectedRole});
}

void KeywordsSearchListModel::add(const Keyword &item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    items.append(item);
    endInsertRows();
}

void KeywordsSearchListModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, items.count() - 1);
    items.clear();
    endRemoveRows();
}

void KeywordsSearchListModel::fillFromCache(const QJsonDocument &json)
{
    QJsonArray jsonItems = json.array();
    for (QJsonValue jsonItem : jsonItems) {
        QJsonObject jsonObj = jsonItem.toObject();
        add(Keyword(jsonObj["id"].toInt(), jsonObj["name"].toString()));
    }
}

const QJsonDocument KeywordsSearchListModel::fillFromAPI(const QJsonDocument &json)
{
    QJsonArray jsonItems = json.object()["results"].toArray();
    QJsonArray newJsonItems;

    for (QJsonArray::const_iterator it = jsonItems.constBegin(); it != jsonItems.constEnd(); it++) {
        QJsonObject jsonObj = (*it).toObject();
        Keyword model(jsonObj["id"].toInt(), jsonObj["name"].toString());
        add(model);
        QJsonObject newJsonItem;
        newJsonItem.insert("id", model.getId());
        newJsonItem.insert("name", model.getName());
        newJsonItems.append(newJsonItem);
    }

    return QJsonDocument(newJsonItems);
}

const QList<Keyword> &KeywordsSearchListModel::getItems() const
{
    return items;
}

QHash<int, QByteArray> KeywordsSearchListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[NameRole] = "name";
    roles[SelectedRole] = "selected";
    return roles;
}
