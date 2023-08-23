#include "configurationlistmodel.h"

ConfigurationListModel::ConfigurationListModel(System &system, QObject *parent) :
    QAbstractListModel(parent),
    system(system)
{

}

int ConfigurationListModel::rowCount(const QModelIndex &) const{
    return items.size();
}

QVariant ConfigurationListModel::data(const QModelIndex &index, int role) const{
    if (index.row() < 0 || index.row() >= items.count())
        return QVariant();
    const ConfigurationListItem &item = items[index.row()];
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

void ConfigurationListModel::add(const ConfigurationListItem &item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    items << item;
    endInsertRows();
    emit countChanged();
}

void ConfigurationListModel::prepend(const ConfigurationListItem &item)
{
    beginInsertRows(QModelIndex(), 0, 0);
    items.prepend(item);
    endInsertRows();
    emit countChanged();
}

void ConfigurationListModel::removeOneById(const QString &id)
{
    QMutableListIterator<ConfigurationListItem> it(items);
    int i = 0;
    while (it.hasNext()) {
        ConfigurationListItem &configuration = it.next();
        if (configuration.getId() == id) {
            beginRemoveRows(QModelIndex(), i, i);
            it.remove();
            endRemoveRows();
            emit countChanged();
            return;
        }
        i++;
    }
}

void ConfigurationListModel::fillFromCache(const QJsonDocument &json)
{
    add(ConfigurationListItem("", "All countries", true));
    QJsonArray items = json.array();
    for (QJsonArray::const_iterator it = items.constBegin(); it != items.constEnd(); it++) {
        add(ConfigurationListItem((*it).toObject()));
    }
}

const QJsonDocument ConfigurationListModel::fillFromAPI(const QJsonDocument &json)
{
    QJsonArray jsonItems = json.array();
    QList<ConfigurationListItem> items;

    for (QJsonArray::const_iterator it = jsonItems.constBegin(); it != jsonItems.constEnd(); it++) {
        QJsonObject json = (*it).toObject();
        QString id = json["iso_3166_1"].toString();
        QString englishName = json["english_name"].toString();
        items.append(ConfigurationListItem(id, englishName, false));
        if (id == system.getCountry()) {
            items.append(ConfigurationListItem(id, englishName, true));
        }
    }

    std::sort(items.begin(), items.end(), [](const ConfigurationListItem &a, const ConfigurationListItem &b)
    {
        return (a.getIsPrimary() ? "" : a.getLabel()) < (b.getIsPrimary() ? "" : b.getLabel());
    });

    add(ConfigurationListItem("", "All countries", true));

    for (int i = 0; i < items.count(); i++) {
        const ConfigurationListItem &configuration = items.at(i);
        add(configuration);
        jsonItems.replace(i, configuration.toJson());
    }

    return QJsonDocument(jsonItems);
}

QHash<int, QByteArray> ConfigurationListModel::roleNames() const{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[LabelRole] = "label";
    roles[SectionRole] = "section";
    roles[PrimaryRole] = "isPrimary";
    return roles;
}
