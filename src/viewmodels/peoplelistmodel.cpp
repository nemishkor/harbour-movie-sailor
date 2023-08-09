#include "peoplelistmodel.h"

PeopleListModel::PeopleListModel(QObject *parent) :
    QAbstractListModel(parent),
    summary(""),
    andMode(true)
{

}

int PeopleListModel::rowCount(const QModelIndex &) const
{
    return items.size();
}

QVariant PeopleListModel::data(const QModelIndex &index, int role) const
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

void PeopleListModel::add(const SearchPersonListItem &item)
{
    for (QList<SearchPersonListItem>::const_iterator it = items.constBegin(); it != items.constEnd(); it++) {
        if (item.getId() == (*it).getId()) {
            return;
        }
    }
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    items.append(item);
    endInsertRows();
    emit countChanged();
    updateSummary();
}

void PeopleListModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, items.count() - 1);
    items.clear();
    endRemoveRows();
    emit countChanged();
    updateSummary();
}

void PeopleListModel::remove(int id)
{
    for (int row = 0; row < items.count(); row++) {
        if (id == items.at(row).getId()) {
            beginRemoveRows(QModelIndex(), row, row);
            items.removeAt(row);
            endRemoveRows();
            emit countChanged();
            updateSummary();
            break;
        }
    }
}

QHash<int, QByteArray> PeopleListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[NameRole] = "name";
    roles[KnownForDepartment] = "knownForDepartment";
    roles[ProfilePath] = "profilePath";
    return roles;
}

void PeopleListModel::updateSummary()
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

const QString &PeopleListModel::getSummary() const
{
    return summary;
}

void PeopleListModel::setAndMode(bool newAndMode)
{
    if (andMode == newAndMode)
        return;
    andMode = newAndMode;
    emit andModeChanged();
    updateSummary();
}

void PeopleListModel::setSummary(const QString &newSummary)
{
    if (summary == newSummary)
        return;
    summary = newSummary;
    emit summaryChanged();
}

bool PeopleListModel::getAndMode() const
{
    return andMode;
}
