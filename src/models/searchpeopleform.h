#ifndef SEARCHPEOPLEFORM_H
#define SEARCHPEOPLEFORM_H

#include <QObject>
#include <QString>

class SearchPeopleForm : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString query READ getQuery WRITE setQuery NOTIFY queryChanged)
    Q_PROPERTY(bool withAdult READ getWithAdult WRITE setWithAdult NOTIFY withAdultChanged)
    Q_PROPERTY(int page READ getPage WRITE setPage NOTIFY pageChanged)
public:
    explicit SearchPeopleForm(QObject *parent);

    const QString &getQuery() const;
    void setQuery(const QString &newQuery);

    bool getWithAdult() const;
    void setWithAdult(bool newWithAdult);

    int getPage() const;
    void setPage(int newPage);

private:
    QString query;
    bool withAdult;
    int page;

signals:
    void queryChanged();
    void withAdultChanged();
    void pageChanged();
};

#endif // SEARCHPEOPLEFORM_H
