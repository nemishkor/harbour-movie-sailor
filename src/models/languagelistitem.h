#ifndef LANGUAGELISTITEM_H
#define LANGUAGELISTITEM_H

#include <QString>

class LanguageListItem
{
public:
    LanguageListItem(const QString &id, const QString &name);
    const QString &getId() const;

    const QString &getName() const;

private:
    QString id;
    QString name;
};

#endif // LANGUAGELISTITEM_H
