#include "cachekey.h"

CacheKey::CacheKey(const QString &section, const QString &name, const QString version) :
    section(section),
    name(name),
    key(""),
    version(version)
{

}
