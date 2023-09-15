#include "keywordslistmodel.h"

KeywordsListModel::KeywordsListModel(QObject *parent) :
    QAbstractListModel(parent),
    summary(""),
    andMode(true)
{

}

int KeywordsListModel::rowCount(const QModelIndex &) const
{
    return items.size();
}

QVariant KeywordsListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= items.count())
        return QVariant();
    const Keyword &item = items[index.row()];
    if (role == IdRole)
        return item.getId();
    if (role == NameRole)
        return item.getName();
    return QVariant();
}

void KeywordsListModel::add(const Keyword &item)
{
    qDebug() << "KeywordsListModel: sorted";
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    items.append(item);
    endInsertRows();
    emit countChanged();
    updateSummary();
}

void KeywordsListModel::remove(const Keyword &item)
{
    QModelIndex index = createIndex(items.indexOf(item), 0);

    if (index.row() < 0)
        return;

    beginRemoveRows(QModelIndex(), index.row(), index.row());
    items.removeAt(index.row());
    endRemoveRows();
    emit countChanged();
    updateSummary();
}

const QList<Keyword> &KeywordsListModel::getItems() const
{
    return items;
}

const QString &KeywordsListModel::getSummary() const
{
    return summary;
}

void KeywordsListModel::setSummary(const QString &newSummary)
{
    if (summary == newSummary)
        return;
    summary = newSummary;
    emit summaryChanged();
}

bool KeywordsListModel::getAndMode() const
{
    return andMode;
}

void KeywordsListModel::setAndMode(bool newAndMode)
{
    if (andMode == newAndMode)
        return;
    andMode = newAndMode;
    emit andModeChanged();
    updateSummary();
}

const QString KeywordsListModel::toQueryString()
{
    QString separator = andMode ? "," : "|";
    QString str = "";
    for (QList<Keyword>::const_iterator it = items.constBegin(); it != items.constEnd(); it++) {
        if (str != "") {
            str.append(separator);
        }
        str.append(QString::number(it->getId()));
    }

    return str;
}

QHash<int, QByteArray> KeywordsListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[NameRole] = "name";
    return roles;
}

void KeywordsListModel::updateSummary()
{
    QString newSummary = "";
    QString joinOperator = andMode ? " and " : " or ";
    for (QList<Keyword>::const_iterator it = items.constBegin(); it != items.constEnd(); it++) {
        if (!newSummary.isEmpty())
            newSummary.append(joinOperator);
        newSummary.append("\"").append((*it).getName()).append("\"");
    }
    setSummary(newSummary);
}
