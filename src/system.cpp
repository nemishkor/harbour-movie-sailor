#include "system.h"

System::System()
{
    QLocale locale;
    QString localeName = locale.name();
    int separatorPosition = localeName.indexOf('_');
    if (separatorPosition != -1 && localeName.length() >= (separatorPosition + 3)) {
        language = localeName.mid(0, separatorPosition);
        country = localeName.mid(separatorPosition + 1, separatorPosition + 3);
    }
}

const QString &System::getLanguage() const
{
    return language;
}

const QString &System::getCountry() const
{
    return country;
}
