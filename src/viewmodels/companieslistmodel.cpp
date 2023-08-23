#include "companieslistmodel.h"

CompaniesListModel::CompaniesListModel(QObject *parent) :
    QAbstractListModel(parent),
    andMode(true)
{

}

int CompaniesListModel::rowCount(const QModelIndex &) const
{
    return items.size();
}

QVariant CompaniesListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= items.count())
        return QVariant();
    const Company &item = items[index.row()];
    if(role == IdRole)
        return item.getId();
    if(role == LogoRole)
        return item.getLogo();
    if(role == NameRole)
        return item.getName();
    if(role == CountryRole)
        return item.getCountry();
    return QVariant();
}

void CompaniesListModel::add(const Company &item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    items.insert(item.getId(), item);
    ids.append(item.getId());
    endInsertRows();
    emit countChanged();
    updateSummary();
}

void CompaniesListModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, items.count() - 1);
    items.clear();
    ids.clear();
    endRemoveRows();
    emit countChanged();
    updateSummary();
}

void CompaniesListModel::removeOneById(int id)
{
    QMutableListIterator<Company> it(items);
    int i = 0;
    while (it.hasNext()) {
        const Company &item = it.next();
        if (item.getId() == id) {
            beginRemoveRows(QModelIndex(), i, i);
            ids.removeOne(item.getId());
            it.remove();
            endRemoveRows();
            emit countChanged();
            updateSummary();
            return;
        }
        i++;
    }
}

bool CompaniesListModel::getAndMode() const
{
    return andMode;
}

void CompaniesListModel::setAndMode(bool newAndMode)
{
    if (andMode == newAndMode)
        return;
    andMode = newAndMode;
    emit andModeChanged();
    updateSummary();
}

const QString &CompaniesListModel::getSummary() const
{
    return summary;
}

void CompaniesListModel::setSummary(const QString &newSummary)
{
    if (summary == newSummary)
        return;
    summary = newSummary;
    emit summaryChanged();
}

QHash<int, QByteArray> CompaniesListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[LogoRole] = "logo";
    roles[NameRole] = "name";
    roles[CountryRole] = "country";
    return roles;
}

void CompaniesListModel::updateSummary()
{
    QString newSummary = "";
    QString joinOperator = andMode ? " and " : " or ";
    for (QList<Company>::const_iterator it = items.constBegin(); it != items.constEnd(); it++) {
        if (!newSummary.isEmpty())
            newSummary.append(joinOperator);
        newSummary.append("\"").append((*it).getName()).append("\"");
    }
    setSummary(newSummary);
}

const QList<int> &CompaniesListModel::getIds() const
{
    return ids;
}
