#ifndef DISCOVERMOVIE_H
#define DISCOVERMOVIE_H

#include <QObject>

#include "src/models/country.h"

class DiscoverMovie : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Country* originCountry READ getOriginCountry NOTIFY originCountryChanged)
public:
    explicit DiscoverMovie(QObject *parent);

    Country *getOriginCountry();

private:
    Country originCountry;

signals:
    void originCountryChanged();
};

#endif // DISCOVERMOVIE_H
