#ifndef CREDITS_H
#define CREDITS_H

#include <QObject>

#include "src/listmodels/castslist.h"
#include "src/listmodels/crewlist.h"

class Credits : public QObject
{
    Q_OBJECT
    Q_PROPERTY(CastsList* cast READ getCast CONSTANT)
    Q_PROPERTY(CrewList* crew READ getCrew CONSTANT)

public:
    Credits(QObject *parent);

    CastsList *getCast() const;
    CrewList *getCrew() const;

private:
    CastsList *cast;
    CrewList *crew;

};

#endif // CREDITS_H
