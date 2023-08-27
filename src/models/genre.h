#ifndef GENRE_H
#define GENRE_H

#include <QString>

class Genre
{
public:
    Genre(int id, const QString &name);

    bool operator==(const Genre &other);

    int getId() const;

    const QString &getName() const;

    bool getChecked() const;
    void setChecked(bool newChecked);

private:
    int id;
    QString name;
    bool checked;
};

#endif // GENRE_H
