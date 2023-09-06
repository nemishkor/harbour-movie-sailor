#include "credits.h"

Credits::Credits(QObject *parent) :
    QObject(parent),
    cast(new CastsList(this)),
    crew(new CrewList(this))
{

}

CastsList *Credits::getCast() const
{
    return cast;
}

CrewList *Credits::getCrew() const
{
    return crew;
}
