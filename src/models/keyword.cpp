#include "keyword.h"

Keyword::Keyword(int id, const QString &name) : id(id), name(name)
{

}

int Keyword::getId() const
{
    return id;
}

const QString &Keyword::getName() const
{
    return name;
}

bool Keyword::operator==(const Keyword &other)
{
    return id == other.id;
}
