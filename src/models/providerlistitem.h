#ifndef PROVIDERLISTITEM_H
#define PROVIDERLISTITEM_H

#include <QString>

class ProviderListItem
{
public:
    ProviderListItem(int id, const QString &logo, const QString &name);
    ProviderListItem(int id, const QString &logo, const QString &name, int priority);

    int getId() const;
    void setId(int newId);

    int getState() const;
    void setState(int newState);

    const QString &getLogo() const;
    void setLogo(const QString &newLogo);

    const QString &getName() const;
    void setName(const QString &newName);

    int getPriority() const;
    void setPriority(int newPriority);

private:
    int id;
    int state;
    QString logo;
    QString name;
    int priority;
};

#endif // PROVIDERLISTITEM_H
