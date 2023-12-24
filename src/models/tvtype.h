#ifndef TVTYPE_H
#define TVTYPE_H


class TVType
{
    enum Type {
        DOCUMENTARY = 0,
        NEWS = 1,
        MINISERIES = 2,
        REALITY = 3,
        SCRIPTED = 4,
        TALK_SHOW = 5,
        VIDEO = 6,
    };
public:
    TVType();
};

#endif // TVTYPE_H
