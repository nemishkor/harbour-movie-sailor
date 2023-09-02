#ifndef COUNTRIESLISTMODEL_H
#define COUNTRIESLISTMODEL_H

#include <QAbstractListModel>

#include "src/models/countrylistitem.h"

class CountriesListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum CountryRoles {
        IdRole = Qt::UserRole + 1,
        NameRole
    };
    CountriesListModel(QObject *parent);
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void add(const CountryListItem &item);
    void clear();

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<CountryListItem> items;
};

#endif // COUNTRIESLISTMODEL_H
