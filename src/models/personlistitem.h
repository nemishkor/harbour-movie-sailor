#ifndef PERSONLISTITEM_H
#define PERSONLISTITEM_H

#include <QString>

class PersonListItem
{
public:
    PersonListItem(int id,
                   const QString &creditId,
                   const QString &name,
                   int gender,
                   const QString &profilePath);

    int getId() const;

    const QString &getCreditId() const;

    const QString &getName() const;

    int getGender() const;

    const QString &getProfilePath() const;

private:
    int id;
    QString creditId;
    QString name;
    int gender;
    QString profilePath;

};

#endif // PERSONLISTITEM_H
