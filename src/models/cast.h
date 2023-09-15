#ifndef CAST_H
#define CAST_H

#include <QString>

class Cast
{
public:
    Cast(int id,
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

#endif // CAST_H
