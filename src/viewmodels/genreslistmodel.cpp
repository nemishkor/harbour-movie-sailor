#include "genreslistmodel.h"

GenresListModel::GenresListModel(QObject *parent) :
    QAbstractListModel(parent),
    summary(""),
    andMode(true)
{

}

int GenresListModel::rowCount(const QModelIndex &) const
{
    return items.size();
}

QVariant GenresListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= items.count())
        return QVariant();
    const Genre &item = items[index.row()];
    if (role == IdRole)
        return item.getId();
    if (role == NameRole)
        return item.getName();
    if (role == CheckedRole)
        return item.getChecked();
    return QVariant();
}

bool GenresListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.row() < 0 || index.row() >= items.count())
        return false;

    Genre &item = items[index.row()];
    if (role == CheckedRole) {
        item.setChecked(value.toBool());
        emit dataChanged(index, index, QVector<int>{role});
        updateSummary();
        return true;
    }

    return false;
}

void GenresListModel::add(const Genre &item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    items.append(item);
    endInsertRows();
    emit countChanged();
}

void GenresListModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, items.count() - 1);
    items.clear();
    endRemoveRows();
    emit countChanged();
    updateSummary();
}

void GenresListModel::fillFromCache(const QJsonDocument &json)
{
    QJsonArray jsonItems = json.array();
    for (QJsonValue jsonItem : jsonItems) {
        QJsonObject jsonObj = jsonItem.toObject();
        add(Genre(jsonObj["id"].toInt(), jsonObj["name"].toString()));
    }
}

const QJsonDocument GenresListModel::fillFromAPI(const QJsonDocument &json)
{
    QJsonArray jsonItems = json.object()["genres"].toArray();
    QJsonArray newJsonItems;

    for (QJsonArray::const_iterator it = jsonItems.constBegin(); it != jsonItems.constEnd(); it++) {
        QJsonObject jsonObj = (*it).toObject();
        Genre model(jsonObj["id"].toInt(), jsonObj["name"].toString());
        add(model);
        QJsonObject newJsonItem;
        newJsonItem.insert("id", model.getId());
        newJsonItem.insert("name", model.getName());
        newJsonItems.append(newJsonItem);
    }

    return QJsonDocument(newJsonItems);
}

QList<Genre> &GenresListModel::getItems()
{
    return items;
}

QHash<int, QByteArray> GenresListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[NameRole] = "name";
    roles[CheckedRole] = "checked";
    return roles;
}

const QString &GenresListModel::getSummary() const
{
    return summary;
}

void GenresListModel::setSummary(const QString &newSummary)
{
    if (summary == newSummary)
        return;
    summary = newSummary;
    emit summaryChanged();
}

bool GenresListModel::getAndMode() const
{
    return andMode;
}

void GenresListModel::setAndMode(bool newAndMode)
{
    if (andMode == newAndMode)
        return;
    andMode = newAndMode;
    emit andModeChanged();
    updateSummary();
}

QString GenresListModel::toQueryString()
{
    QString genresSeparator = andMode ? "," : "|";
    QString genresString = "";
    for (QList<Genre>::const_iterator it = items.constBegin(); it != items.constEnd(); it++) {
        if (it->getChecked()) {
            if (genresString != "") {
                genresString.append(genresSeparator);
            }
            genresString.append(QString::number(it->getId()));
        }
    }

    return genresString;
}

void GenresListModel::updateSummary()
{
    QString newSummary = "";
    QString joinOperator = andMode ? " and " : " or ";
    for (QList<Genre>::const_iterator it = items.constBegin(); it != items.constEnd(); it++) {
        if (it->getChecked()) {
            if (!newSummary.isEmpty())
                newSummary.append(joinOperator);
            newSummary.append("\"").append((*it).getName()).append("\"");
        }
    }
    setSummary(newSummary);
}
