#ifndef PROVIDER_H
#define PROVIDER_H

#include <QString>

class Provider
{
public:
    Provider(int id, const QString &name);

    int getId() const;

    const QString &getName() const;

private:
    int id;
    QString name;
};

#endif // PROVIDER_H
