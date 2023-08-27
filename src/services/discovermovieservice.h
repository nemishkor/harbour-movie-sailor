#ifndef DISCOVERMOVIESERVICE_H
#define DISCOVERMOVIESERVICE_H

#include <QDebug>
#include <QObject>

#include "src/api.h"
#include "src/filecache.h"
#include "src/models/discovermovie.h"
#include "src/services/genresmovieservice.h"
#include "src/viewmodels/discovermovieresultlistmodel.h"

class DiscoverMovieService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(DiscoverMovie* form READ getForm CONSTANT)
    Q_PROPERTY(bool initialized READ getInitialized WRITE setInitialized NOTIFY initializedChanged)
    Q_PROPERTY(DiscoverMovieResultListModel* model READ getModel CONSTANT)
public:
    explicit DiscoverMovieService(Api &api, GenresMovieService &genresService, FileCache &cache, QObject *parent);
    Q_INVOKABLE void search();

    bool getInitialized() const;
    void setInitialized(bool newInitialized);

    DiscoverMovieResultListModel *getModel() const;
    DiscoverMovie *getForm() const;

public slots:
    void apiRequestDone(const QByteArray &data);

private:
    Api &api;
    DiscoverMovie* form;
    GenresMovieService &genresService;
    DiscoverMovieResultListModel* model;
    bool initialized;

signals:
    void initializedChanged();

};

#endif // DISCOVERMOVIESERVICE_H
