#ifndef SYSTEM_H
#define SYSTEM_H

#include <QLocale>
#include <QString>

class System
{
public:
    System();

    const QLocale &getLocale() const;

    const QString &getLanguage() const;

    const QString &getCountry() const;

private:
    QLocale locale;
    QString language;
    QString country;
};

#endif // SYSTEM_H
