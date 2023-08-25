#ifndef DISCOVERMOVIE_H
#define DISCOVERMOVIE_H

#include <QObject>

#include "src/models/country.h"
#include "src/models/language.h"

class DiscoverMovie : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Country* originCountry READ getOriginCountry CONSTANT)
    Q_PROPERTY(Language* language READ getLanguage CONSTANT)
    Q_PROPERTY(Language* originLanguage READ getOriginLanguage CONSTANT)
public:
    explicit DiscoverMovie(QObject *parent);

    Country *getOriginCountry() const;
    Language *getLanguage() const;
    Language *getOriginLanguage() const;

private:
    Country *originCountry;
    Language *language;
    Language *originLanguage;
};

#endif // DISCOVERMOVIE_H
