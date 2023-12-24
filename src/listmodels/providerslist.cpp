#include "providerslist.h"

ProvidersList::ProvidersList(QObject *parent) : QAbstractListModel(parent)
{

}

int ProvidersList::rowCount(const QModelIndex &) const
{
    return items.size();
}

QVariant ProvidersList::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= items.count())
        return QVariant();
    const ProviderListItem &item = items[index.row()];
    if(role == IdRole)
        return item.getId();
    if(role == StateRole)
        return item.getState();
    if(role == NameRole)
        return item.getName();
    if(role == LogoRole)
        return item.getLogo();
    return QVariant();
}

bool ProvidersList::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.row() < 0 || index.row() >= items.count())
        return false;

    ProviderListItem &item = items[index.row()];
    if(role == StateRole){
        item.setState(value.toInt());
        emit dataChanged(index, index, QVector<int>{role});
        return true;
    }

    return false;
}

void ProvidersList::add(const ProviderListItem &item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    items.append(item);
    endInsertRows();
    emit countChanged();
}

void ProvidersList::clear()
{
    beginRemoveRows(QModelIndex(), 0, items.count() - 1);
    items.clear();
    endRemoveRows();
}

void ProvidersList::fillFromCache(const QJsonDocument &json)
{
    QJsonArray jsonProviders = json.array();
    for (QJsonValue jsonProvidersItem : jsonProviders) {
        QJsonObject jsonProvider = jsonProvidersItem.toObject();
        ProviderListItem provider(
            jsonProvider["id"].toInt(),
            jsonProvider["logo"].toString(),
            jsonProvider["name"].toString()
        );
        add(provider);
    }
}

const QJsonDocument ProvidersList::fillFromAPI(const QJsonDocument &json)
{
    QJsonArray jsonItems = json.object()["results"].toArray();
    QList<ProviderListItem> items;
    QJsonArray::iterator it = jsonItems.begin();

    while (it != jsonItems.end()) {
        QJsonObject jsonItem = (*it).toObject();
        ProviderListItem provider(
            jsonItem["provider_id"].toInt(),
            jsonItem["logo_path"].toString(),
            jsonItem["provider_name"].toString(),
            jsonItem["display_priority"].toInt()
        );
        items.append(provider);
        jsonItems.erase(it);
    }

    std::sort(items.begin(), items.end(), [](const ProviderListItem &a, const ProviderListItem &b)
    {
        return QString(a.getPriority()).append(a.getName()) < QString(b.getPriority()).append(b.getName());
    });

    for (int i = 0; i < items.count(); i++) {
        const ProviderListItem &item = items.at(i);
        add(item);
        QJsonObject jsonItem;
        jsonItem.insert("id", item.getId());
        jsonItem.insert("name", item.getName());
        jsonItem.insert("logo", item.getLogo());
        jsonItems.append(jsonItem);
    }

    return QJsonDocument(jsonItems);
}

QHash<int, QByteArray> ProvidersList::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[StateRole] = "state";
    roles[IdRole] = "id";
    roles[NameRole] = "name";
    roles[LogoRole] = "logo";
    return roles;
}

const QList<ProviderListItem> &ProvidersList::getItems() const
{
    return items;
}
