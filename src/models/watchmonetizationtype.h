#ifndef WATCHMONETIZATIONTYPE_H
#define WATCHMONETIZATIONTYPE_H

#include <QString>

class WatchMonetizationType
{
public:
    WatchMonetizationType(const QString &id, const QString &label);

    const QString &getId() const;

    const QString &getLabel() const;

private:
    QString id;
    QString label;
};

#endif // WATCHMONETIZATIONTYPE_H
