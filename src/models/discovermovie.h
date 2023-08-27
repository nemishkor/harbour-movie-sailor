#ifndef DISCOVERMOVIE_H
#define DISCOVERMOVIE_H

#include <QObject>

#include "src/models/country.h"
#include "src/models/language.h"

class DiscoverMovie : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int page READ getPage WRITE setPage NOTIFY pageChanged)
    Q_PROPERTY(Country* originCountry READ getOriginCountry CONSTANT)
    Q_PROPERTY(Language* language READ getLanguage CONSTANT)
    Q_PROPERTY(Language* originLanguage READ getOriginLanguage CONSTANT)
public:
    explicit DiscoverMovie(QObject *parent);

    int getPage() const;
    void setPage(int newPage);
    Country *getOriginCountry() const;
    Language *getLanguage() const;
    Language *getOriginLanguage() const;

signals:
    void pageChanged();

private:
    int page;
    Country *originCountry;
    Language *language;
    Language *originLanguage;
};

#endif // DISCOVERMOVIE_H
