#ifndef KEYWORD_H
#define KEYWORD_H

#include <QString>

class Keyword
{
public:
    Keyword(int id, const QString &name);
    int getId() const;

    const QString &getName() const;
    bool operator==(const Keyword &other);

private:
    int id;
    QString name;
};

#endif // KEYWORD_H
