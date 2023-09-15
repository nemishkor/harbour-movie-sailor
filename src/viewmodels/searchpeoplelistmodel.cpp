#include "searchpeoplelistmodel.h"

SearchPeopleListModel::SearchPeopleListModel(QObject *parent) :
    QAbstractListModel(parent),
    summary(""),
    andMode(true)
{

}

int SearchPeopleListModel::rowCount(const QModelIndex &) const
{
    return items.size();
}

QVariant SearchPeopleListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= items.count())
        return QVariant();
    const SearchPersonListItem &item = items[index.row()];
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

void SearchPeopleListModel::add(const SearchPersonListItem &item)
{
    qDebug() << "SearchPeopleListModel: add" << item.getId() << "to the role model";
    if (ids.contains(item.getId())) {
        return;
    }
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    ids.append(item.getId());
    items.append(item);
    endInsertRows();
    emit countChanged();
    updateSummary();
}

void SearchPeopleListModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, items.count() - 1);
    ids.clear();
    items.clear();
    endRemoveRows();
    emit countChanged();
    updateSummary();
}

void SearchPeopleListModel::remove(int id)
{
    qDebug() << "SearchPeopleListModel: remove the person" << id << "from the list model";
    for (int row = 0; row < items.count(); row++) {
        if (id == items.at(row).getId()) {
            qDebug() << "SearchPeopleListModel: found the person to remove";
            beginRemoveRows(QModelIndex(), row, row);
            ids.removeAt(row);
            items.removeAt(row);
            endRemoveRows();
            emit countChanged();
            updateSummary();
            break;
        }
    }
}

QHash<int, QByteArray> SearchPeopleListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[NameRole] = "name";
    roles[KnownForDepartment] = "knownForDepartment";
    roles[ProfilePath] = "profilePath";
    return roles;
}

const QList<int> &SearchPeopleListModel::getIds() const
{
    return ids;
}

const QString SearchPeopleListModel::toQueryString()
{
    QString separator = andMode ? "," : "|";
    QString str = "";
    for (QList<SearchPersonListItem>::const_iterator it = items.constBegin(); it != items.constEnd(); it++) {
        if (str != "") {
            str.append(separator);
        }
        str.append(QString::number(it->getId()));
    }

    return str;
}

void SearchPeopleListModel::updateSummary()
{
    QString newSummary = "";
    QString joinOperator = andMode ? " and " : " or ";
    for (QList<SearchPersonListItem>::const_iterator it = items.constBegin(); it != items.constEnd(); it++) {
        if (!newSummary.isEmpty())
            newSummary.append(joinOperator);
        newSummary.append("\"").append((*it).getName()).append("\"");
    }
    setSummary(newSummary);
}

const QString &SearchPeopleListModel::getSummary() const
{
    return summary;
}

void SearchPeopleListModel::setAndMode(bool newAndMode)
{
    if (andMode == newAndMode)
        return;
    andMode = newAndMode;
    emit andModeChanged();
    updateSummary();
}

void SearchPeopleListModel::setSummary(const QString &newSummary)
{
    if (summary == newSummary)
        return;
    summary = newSummary;
    emit summaryChanged();
}

bool SearchPeopleListModel::getAndMode() const
{
    return andMode;
}
