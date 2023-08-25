#include "discovermovie.h"

DiscoverMovie::DiscoverMovie(QObject *parent) :
    QObject(parent),
    originCountry(new Country(this)),
    language(new Language(this)),
    originLanguage(new Language(this))
{

}

Country *DiscoverMovie::getOriginCountry() const
{
    return originCountry;
}

Language *DiscoverMovie::getLanguage() const
{
    return language;
}

Language *DiscoverMovie::getOriginLanguage() const
{
    return originLanguage;
}
