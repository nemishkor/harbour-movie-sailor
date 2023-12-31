#ifndef VIDEOLISTITEM_H
#define VIDEOLISTITEM_H

#include <QString>

class VideoListItem
{
public:
    VideoListItem();

    const QString &getName() const;
    void setName(const QString &newName);

    const QString &getKey() const;
    void setKey(const QString &newKey);

    const QString &getSite() const;
    void setSite(const QString &newSite);

    const QString &getType() const;
    void setType(const QString &newType);

    bool getOfficial() const;
    void setOfficial(bool newOfficial);

private:
    QString name;
    QString key;
    QString site;
    QString type;
    bool official;
};

#endif // VIDEOLISTITEM_H
