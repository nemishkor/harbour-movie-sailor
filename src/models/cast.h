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
         int castId,
         const QString &character,
         const QString &creditId);

    int getId() const;

    const QString &getName() const;

    const QString &getOriginalName() const;

    const QString &getProfilePath() const;

    int getCastId() const;

    const QString &getCharacter() const;

    const QString &getCreditId() const;

private:
    int id;
    QString name;
    QString originalName;
    QString profilePath;
    int castId;
    QString character;
    QString creditId;
};

#endif // CAST_H
