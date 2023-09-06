#ifndef CREWLISTITEM_H
#define CREWLISTITEM_H

#include <QString>

class CrewListItem
{
public:
    CrewListItem(int id,
                 const QString &name,
                 const QString &originalName,
                 const QString &profilePath,
                 const QString &department,
                 const QString &job);

    int getId() const;

    const QString &getName() const;

    const QString &getOriginalName() const;

    const QString &getProfilePath() const;

    const QString &getDepartment() const;

    const QString &getJob() const;

private:
    int id;
    QString name;
    QString originalName;
    QString profilePath;
    QString department;
    QString job;
};

#endif // CREWLISTITEM_H
