#ifndef SEARCHPERSONLISTITEM_H
#define SEARCHPERSONLISTITEM_H

#include <QString>

class SearchPersonListItem
{
public:
    enum PersonRole {
        AnyRole = 0,
        CastRole,
        CrewRole
    };

    SearchPersonListItem();

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

    PersonRole getRole() const;
    void setRole(PersonRole newRole);

private:
    int id;
    QString name;
    bool checked;
    QString knownForDepartment;
    QString profilePath;
    PersonRole role;
};

#endif // SEARCHPERSONLISTITEM_H
