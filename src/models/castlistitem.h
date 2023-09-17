#ifndef CASTLISTITEM_H
#define CASTLISTITEM_H

#include <QString>

class CastListItem
{
public:
    CastListItem(int id,
         const QString &name,
         const QString &originalName,
         const QString &profilePath,
         const QString &character);

    int getId() const;
    const QString &getName() const;
    const QString &getOriginalName() const;
    const QString &getProfilePath() const;
    const QString &getCharacter() const;

private:
    int id;
    QString name;
    QString originalName;
    QString profilePath;
    QString character;
};

#endif // CASTLISTITEM_H
