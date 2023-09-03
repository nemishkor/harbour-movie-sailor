#ifndef TVSERVICE_H
#define TVSERVICE_H

#include <QDebug>
#include <QObject>

#include "src/api.h"
#include "src/models/medialistitem.h"
#include "src/models/tv.h"
#include "src/models/requestinfo.h"

class TvService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Tv* model READ getModel CONSTANT)
    Q_PROPERTY(RequestInfo* request READ getRequest CONSTANT)
    Q_PROPERTY(RequestInfo* requestFavorite READ getRequestFavorite CONSTANT)
    Q_PROPERTY(RequestInfo* requestWatchlist READ getRequestWatchlist CONSTANT)
    Q_PROPERTY(RequestInfo* requestAddRating READ getRequestAddRating CONSTANT)
    Q_PROPERTY(RequestInfo* requestRemoveRating READ getRequestRemoveRating CONSTANT)

public:
    TvService(Api &api, QObject *parent);

    Q_INVOKABLE void toggleFavorite();
    Q_INVOKABLE void toggleWatchlist();
    Q_INVOKABLE void addRating(int rating);
    Q_INVOKABLE void removeRating();

    void fillWithListItemAndLoad(const MediaListItem &result);

    Tv *getModel() const;
    RequestInfo *getRequest() const;
    RequestInfo *getRequestFavorite() const;
    RequestInfo *getRequestWatchlist() const;
    RequestInfo *getRequestAddRating() const;
    RequestInfo *getRequestRemoveRating() const;

private:
    Api &api;
    Tv *model;
    RequestInfo *request;
    RequestInfo *requestFavorite;
    RequestInfo *requestWatchlist;
    RequestInfo *requestAddRating;
    RequestInfo *requestRemoveRating;

private slots:
    void apiRequestDone(QByteArray &data);
    void favoriteDone(const QByteArray &data);
    void toggleWatchlistDone(const QByteArray &data);
    void addRatingDone(const QByteArray &data);
    void removeRatingDone(const QByteArray &data);

};

#endif // TVSERVICE_H
