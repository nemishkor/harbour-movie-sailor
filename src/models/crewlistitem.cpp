#include "crewlistitem.h"

CrewListItem::CrewListItem(int id,
                           const QString &name,
                           const QString &originalName,
                           const QString &profilePath,
                           const QString &department,
                           const QString &job) :
    id(id),
    name(name),
    originalName(originalName),
    profilePath(profilePath),
    department(department),
    job(job)
{

}

int CrewListItem::getId() const
{
    return id;
}

const QString &CrewListItem::getName() const
{
    return name;
}

const QString &CrewListItem::getOriginalName() const
{
    return originalName;
}

const QString &CrewListItem::getProfilePath() const
{
    return profilePath;
}

const QString &CrewListItem::getDepartment() const
{
    return department;
}

const QString &CrewListItem::getJob() const
{
    return job;
}
