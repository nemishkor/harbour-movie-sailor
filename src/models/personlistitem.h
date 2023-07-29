#ifndef PERSONLISTITEM_H
#define PERSONLISTITEM_H

#include <QString>

class PersonListItem
{
public:
    PersonListItem();

    int getId() const;
    void setId(int newId);

    const QString &getName() const;
    void setName(const QString &newName);

    bool getChecked() const;
    void setChecked(bool newChecked);

    const QString &getKnownForDepartment() const;
    void setKnownForDepartment(const QString &newKnownForDepartment);

    const QString &getProfilePath() const;
    void setProfilePath(const QString &newProfilePath);

private:
    int id;
    QString name;
    bool checked;
    QString knownForDepartment;
    QString profilePath;
};

#endif // PERSONLISTITEM_H
