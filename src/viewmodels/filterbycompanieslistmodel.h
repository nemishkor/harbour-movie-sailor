#ifndef FILTERBYCOMPANIESLISTMODEL_H
#define FILTERBYCOMPANIESLISTMODEL_H

#include <QAbstractListModel>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QMutableMapIterator>

#include "src/models/company.h"
#include "src/viewmodels/companieslistmodel.h"

class FilterByCompaniesListModel : public CompaniesListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
    Q_PROPERTY(bool andMode READ getAndMode WRITE setAndMode NOTIFY andModeChanged)
    Q_PROPERTY(QString summary READ getSummary NOTIFY summaryChanged)

public:
    FilterByCompaniesListModel(QObject *parent);
    void add(const Company &item);
    Q_INVOKABLE void clear();
    Q_INVOKABLE void removeOneById(int id);
    const QList<int> &getIds() const;

    bool getAndMode() const;
    void setAndMode(bool newAndMode);

    const QString &getSummary() const;
    void setSummary(const QString &newSummary);

    const QString toQueryString();

private:
    QList<int> ids;
    bool andMode;
    QString summary;
    void updateSummary();

signals:
    void countChanged();
    void summaryChanged();
    void andModeChanged();
};

#endif // FILTERBYCOMPANIESLISTMODEL_H
