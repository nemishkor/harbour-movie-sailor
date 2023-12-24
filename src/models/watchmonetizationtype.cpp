#include "watchmonetizationtype.h"

WatchMonetizationType::WatchMonetizationType(const QString &id, const QString &label):
    id(id),
    label(label)
{

}

const QString &WatchMonetizationType::getId() const
{
    return id;
}

const QString &WatchMonetizationType::getLabel() const
{
    return label;
}
