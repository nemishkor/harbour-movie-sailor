#ifndef SEARCHMULTIFORM_H
#define SEARCHMULTIFORM_H

#include <QDebug>
#include <QObject>

#include "src/models/form.h"

class SearchForm : public QObject, public Form
{
    Q_OBJECT
    Q_PROPERTY(QString query READ getQuery WRITE setQuery NOTIFY queryChanged)
    Q_PROPERTY(MediaType type READ getType WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString primaryReleaseYear READ getPrimaryReleaseYear WRITE setPrimaryReleaseYear NOTIFY primaryReleaseYearChanged)
    Q_PROPERTY(QString firstAirDateYear READ getFirstAirDateYear WRITE setFirstAirDateYear NOTIFY firstAirDateYearChanged)
    Q_PROPERTY(QString region READ getRegion WRITE setRegion NOTIFY regionChanged)
    Q_PROPERTY(int page READ getPage WRITE setPage NOTIFY pageChanged)
    Q_PROPERTY(QString year READ getYear WRITE setYear NOTIFY yearChanged)

public:
    enum MediaType {
        Any = 0,
        Movie = 1,
        Tv = 2,
        Person = 3
    };
    Q_ENUMS(MediaType)
    SearchForm(QObject *parent);

    Q_INVOKABLE void reset();

    void populateQuery(QUrlQuery &urlQuery) const override;
    QString toString() const override;
    bool isValid() const override;

    MediaType getType() const;
    void setType(MediaType newType);

    const QString &getQuery() const;
    void setQuery(const QString &newQuery);

    const QString &getPrimaryReleaseYear() const;
    void setPrimaryReleaseYear(const QString &newPrimaryReleaseYear);

    int getPage() const;
    void setPage(int newPage);

    const QString &getRegion() const;
    void setRegion(const QString &newRegion);

    const QString &getYear() const;
    void setYear(const QString &newYear);

    const QString &getFirstAirDateYear() const;
    void setFirstAirDateYear(const QString &newFirstAirDateYear);

private:
    MediaType type;
    QString query;
    QString primaryReleaseYear;
    QString firstAirDateYear;
    QString region;
    QString year;
    int page;

signals:
    void queryChanged();
    void pageChanged();

    void typeChanged();
    void primaryReleaseYearChanged();
    void regionChanged();
    void yearChanged();
    void firstAirDateYearChanged();
};

#endif // SEARCHMULTIFORM_H
