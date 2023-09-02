#ifndef COMPANIESLISTMODEL_H
#define COMPANIESLISTMODEL_H

#include <QAbstractListModel>
#include <QDebug>

#include "src/models/company.h"

class CompaniesListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    CompaniesListModel(QObject *parent);
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void add(const Company &item);
    void clear();

protected:
    enum CompanyRoles {
        IdRole = Qt::UserRole + 1,
        LogoRole,
        NameRole,
        CountryRole
    };
    QList<Company> items;
    QHash<int, QByteArray> roleNames() const override;
};

#endif // COMPANIESLISTMODEL_H
