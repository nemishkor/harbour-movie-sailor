#ifndef TVNETWORKLISTITEM_H
#define TVNETWORKLISTITEM_H

#include <QString>

class TVNetworkListItem
{
public:
    TVNetworkListItem(int id, const QString &name);

    int getId() const;

    const QString &getName() const;

private:
    int id;
    QString name;
};

#endif // TVNETWORKLISTITEM_H
