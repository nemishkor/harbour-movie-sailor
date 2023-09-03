#ifndef ACCOUNTMOVIESFORM_H
#define ACCOUNTMOVIESFORM_H

#include <QObject>
#include <QString>

#include "src/models/form.h"

class AccountMoviesForm : public QObject, public Form
{
    Q_OBJECT
    Q_PROPERTY(int page READ getPage WRITE setPage NOTIFY pageChanged)
    Q_PROPERTY(QString sortBy READ getSortBy WRITE setSortBy NOTIFY sortByChanged)

public:
    AccountMoviesForm(QObject *parent);

    void populateQuery(QUrlQuery &urlQuery) const override;
    QString toString() const override;

    int getPage() const;
    void setPage(int newPage);

    const QString &getSortBy() const;
    void setSortBy(const QString &newSortBy);

private:
    int page;
    QString sortBy;

signals:
    void pageChanged();
    void sortByChanged();

};

#endif // ACCOUNTMOVIESFORM_H
