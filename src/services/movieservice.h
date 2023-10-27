#ifndef MOVIESERVICE_H
#define MOVIESERVICE_H

#include <QDebug>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>

#include "src/api.h"
#include "src/system.h"
#include "src/models/movie.h"
#include "src/models/medialistitem.h"
#include "src/services/historyservice.h"

class MovieService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Movie* model READ getModel CONSTANT)
    Q_PROPERTY(RequestInfo* request READ getRequest CONSTANT)

public:
    MovieService(Api &api, System &system, HistoryService &historyService, QObject *parent);

    Q_INVOKABLE void toggleFavorite();
    Q_INVOKABLE void toggleWatchlist();
    Q_INVOKABLE void addRating(int rating);
    Q_INVOKABLE void removeRating();
    Q_INVOKABLE void load(int id);
    Q_INVOKABLE void load(Movie *movie, int id);

    Movie *getModel() const;

    RequestInfo *getRequest() const;

private:
    Api &api;
    System &system;
    HistoryService &historyService;
    Movie *model;
    RequestInfo *request;

public slots:
    void apiRequestDone(const QByteArray &data);
    void favoriteDone(const QByteArray &data);
    void toggleWatchlistDone(const QByteArray &data);
    void addRatingDone(const QByteArray &data);
    void removeRatingDone(const QByteArray &data);

};

#endif // MOVIESERVICE_H
