#ifndef COUNTRYLISTITEM_H
#define COUNTRYLISTITEM_H

#include <QString>

class CountryListItem
{
public:
    CountryListItem(const QString &id, const QString &name);

    const QString &getId() const;

    const QString &getName() const;

private:
    QString id;
    QString name;
};

#endif // COUNTRYLISTITEM_H
