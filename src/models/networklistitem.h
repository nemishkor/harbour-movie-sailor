#ifndef NETWORK_H
#define NETWORK_H

#include <QString>

class NetworkListItem
{
public:
    NetworkListItem(int id,
            const QString &logoPath,
            const QString &name,
            const QString &originCountry);

    int getId() const;
    const QString &getLogoPath() const;
    const QString &getName() const;
    const QString &getOriginCountry() const;

private:
    int id;
    QString logoPath;
    QString name;
    QString originCountry;

};

#endif // NETWORK_H
