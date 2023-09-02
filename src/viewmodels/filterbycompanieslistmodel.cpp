#include "filterbycompanieslistmodel.h"

FilterByCompaniesListModel::FilterByCompaniesListModel(QObject *parent) :
    CompaniesListModel(parent),
    andMode(true)
{

}

void FilterByCompaniesListModel::add(const Company &item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    items.insert(item.getId(), item);
    ids.append(item.getId());
    endInsertRows();
    emit countChanged();
    updateSummary();
}

void FilterByCompaniesListModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, items.count() - 1);
    items.clear();
    ids.clear();
    endRemoveRows();
    emit countChanged();
    updateSummary();
}

void FilterByCompaniesListModel::removeOneById(int id)
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

bool FilterByCompaniesListModel::getAndMode() const
{
    return andMode;
}

void FilterByCompaniesListModel::setAndMode(bool newAndMode)
{
    if (andMode == newAndMode)
        return;
    andMode = newAndMode;
    emit andModeChanged();
    updateSummary();
}

const QString &FilterByCompaniesListModel::getSummary() const
{
    return summary;
}

void FilterByCompaniesListModel::setSummary(const QString &newSummary)
{
    if (summary == newSummary)
        return;
    summary = newSummary;
    emit summaryChanged();
}

const QString FilterByCompaniesListModel::toQueryString()
{
    QString separator = andMode ? "," : "|";
    QString str = "";
    for (QList<Company>::const_iterator it = items.constBegin(); it != items.constEnd(); it++) {
        if (str != "") {
            str.append(separator);
        }
        str.append(QString::number(it->getId()));
    }

    return str;
}

void FilterByCompaniesListModel::updateSummary()
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

const QList<int> &FilterByCompaniesListModel::getIds() const
{
    return ids;
}
