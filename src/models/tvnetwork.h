#ifndef TVNETWORK_H
#define TVNETWORK_H

#include <QString>

class TVNetwork
{
public:
    TVNetwork(int id, const QString &name);

    int getId() const;

    const QString &getName() const;

private:
    int id;
    QString name;
};

#endif // TVNETWORK_H
