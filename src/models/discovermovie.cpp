#include "discovermovie.h"

DiscoverMovie::DiscoverMovie(QObject *parent) :
    QObject(parent),
    originCountry(this)
{

}

Country *DiscoverMovie::getOriginCountry()
{
    return &originCountry;
}
