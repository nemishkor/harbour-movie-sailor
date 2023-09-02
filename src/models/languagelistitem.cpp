#include "languagelistitem.h"

LanguageListItem::LanguageListItem(const QString &id, const QString &name) :
    id(id),
    name(name)
{

}

const QString &LanguageListItem::getId() const
{
    return id;
}

const QString &LanguageListItem::getName() const
{
    return name;
}
