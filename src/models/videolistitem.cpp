#include "videolistitem.h"

VideoListItem::VideoListItem()
{

}

const QString &VideoListItem::getName() const
{
    return name;
}

void VideoListItem::setName(const QString &newName)
{
    name = newName;
}

const QString &VideoListItem::getKey() const
{
    return key;
}

void VideoListItem::setKey(const QString &newKey)
{
    key = newKey;
}

const QString &VideoListItem::getSite() const
{
    return site;
}

void VideoListItem::setSite(const QString &newSite)
{
    site = newSite;
}

const QString &VideoListItem::getType() const
{
    return type;
}

void VideoListItem::setType(const QString &newType)
{
    type = newType;
}

bool VideoListItem::getOfficial() const
{
    return official;
}

void VideoListItem::setOfficial(bool newOfficial)
{
    official = newOfficial;
}
