#ifndef ACCOUNTMOVIESFORM_H
#define ACCOUNTMOVIESFORM_H

#include <QObject>
#include <QString>

class AccountMoviesForm : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int page READ getPage WRITE setPage NOTIFY pageChanged)
    Q_PROPERTY(QString sortBy READ getSortBy WRITE setSortBy NOTIFY sortByChanged)

public:
    AccountMoviesForm(QObject *parent);

    int getPage() const;
    void setPage(int newPage);

    const QString &getSortBy() const;
    void setSortBy(const QString &newSortBy);

    bool getDirty() const;
    void setDirty(bool newDirty);

private:
    int page;
    QString sortBy;
    bool dirty;

signals:
    void pageChanged();
    void sortByChanged();

};

#endif // ACCOUNTMOVIESFORM_H
