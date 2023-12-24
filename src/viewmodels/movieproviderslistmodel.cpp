#include "movieproviderslistmodel.h"

MovieProvidersListModel::MovieProvidersListModel(QObject *parent) : QAbstractListModel(parent)
{

}

int MovieProvidersListModel::rowCount(const QModelIndex &) const{
    return items.size();
}

QVariant MovieProvidersListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= items.count())
        return QVariant();
    const MovieProvider &item = items[index.row()];
    if(role == CheckStateRole)
        return item.getChecked();
    if(role == IdRole)
        return item.getId();
    if(role == NameRole)
        return item.getName();
    if(role == LogoRole)
        return item.getLogo();
    return QVariant();
}

bool MovieProvidersListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.row() < 0 || index.row() >= items.count())
        return false;

    MovieProvider &item = items[index.row()];
    if(role == CheckStateRole){
        item.setChecked(value.toBool());
        emit dataChanged(index, index, QVector<int>{role});
        return true;
    }

    return false;
}

Qt::ItemFlags MovieProvidersListModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return Qt::ItemIsUserCheckable;
}

void MovieProvidersListModel::add(const MovieProvider &item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    items.append(item);
    endInsertRows();
    emit countChanged();
}

void MovieProvidersListModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, items.count() - 1);
    items.clear();
    endRemoveRows();
}

void MovieProvidersListModel::fillFromCache(const QJsonDocument &json)
{
    QJsonArray jsonProviders = json.array();
    for (QJsonValue jsonProvidersItem : jsonProviders) {
        QJsonObject jsonProvider = jsonProvidersItem.toObject();
        MovieProvider provider;
        provider.setId(jsonProvider["id"].toInt());
        provider.setName(jsonProvider["name"].toString());
        provider.setLogo(jsonProvider["logo"].toString());
        add(provider);
    }
}

const QJsonDocument MovieProvidersListModel::fillFromAPI(const QJsonDocument &json)
{
    QJsonArray jsonItems = json.object()["results"].toArray();
    QList<MovieProvider> items;
    QJsonArray::iterator it = jsonItems.begin();

    while (it != jsonItems.end()) {
        QJsonObject jsonItem = (*it).toObject();
        MovieProvider provider;
        provider.setId(jsonItem["provider_id"].toInt());
        provider.setName(jsonItem["provider_name"].toString());
        provider.setLogo(jsonItem["logo_path"].toString());
        provider.setPriority(jsonItem["display_priority"].toInt());
        items.append(provider);
        jsonItems.erase(it);
    }

    std::sort(items.begin(), items.end(), [](const MovieProvider &a, const MovieProvider &b)
    {
        return QString(a.getPriority()).append(a.getName()) < QString(b.getPriority()).append(b.getName());
    });

    qDebug() << "MovieProvidersListModel: sorted";

    for (int i = 0; i < items.count(); i++) {
        const MovieProvider &item = items.at(i);
        add(item);
        QJsonObject jsonItem;
        jsonItem.insert("id", item.getId());
        jsonItem.insert("name", item.getName());
        jsonItem.insert("logo", item.getLogo());
        jsonItems.append(jsonItem);
    }

    return QJsonDocument(jsonItems);
}

QString MovieProvidersListModel::toQueryString() const
{
    QString separator = "|";
    QString str = "";
    for (QList<MovieProvider>::const_iterator it = items.constBegin(); it != items.constEnd(); it++) {
        if (it->getChecked()) {
            if (str != "") {
                str.append(separator);
            }
            str.append(QString::number(it->getId()));
        }
    }

    return str;
}

QHash<int, QByteArray> MovieProvidersListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[CheckStateRole] = "checked";
    roles[IdRole] = "id";
    roles[NameRole] = "name";
    roles[LogoRole] = "logo";
    return roles;
}
