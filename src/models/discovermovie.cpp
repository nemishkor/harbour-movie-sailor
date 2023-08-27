#include "discovermovie.h"

DiscoverMovie::DiscoverMovie(QObject *parent) :
    QObject(parent),
    page(1),
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

int DiscoverMovie::getPage() const
{
    return page;
}

void DiscoverMovie::setPage(int newPage)
{
    if (page == newPage)
        return;
    page = newPage;
    emit pageChanged();
}
