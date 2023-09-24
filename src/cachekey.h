#ifndef CACHEKEY_H
#define CACHEKEY_H

#include <QString>

class CacheKey
{
public:
    CacheKey(const QString &section, const QString &name, const QString version);
    const QString section;
    const QString name;
    QString key;
    const QString version;
};

#endif // CACHEKEY_H
