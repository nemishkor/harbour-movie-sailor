#include "genre.h"

Genre::Genre(int id, const QString &name) :
    id(id),
    name(name),
    checked(false)
{

}

bool Genre::operator==(const Genre &other)
{
    return id == other.id;
}

int Genre::getId() const
{
    return id;
}

const QString &Genre::getName() const
{
    return name;
}

bool Genre::getChecked() const
{
    return checked;
}

void Genre::setChecked(bool newChecked)
{
    checked = newChecked;
}
