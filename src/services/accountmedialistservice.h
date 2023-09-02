#ifndef ACCOUNTMEDIALISTSERVICE_H
#define ACCOUNTMEDIALISTSERVICE_H

#include <QObject>

#include "src/api.h"
#include "src/models/requestinfo.h"
#include "src/models/accountmoviesform.h"
#include "src/services/movieservice.h"
#include "src/viewmodels/movieslistmodel.h"
#include "src/viewmodels/genreslistmodel.h"

class AccountMediaListService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(AccountMoviesForm* form READ getForm CONSTANT)
    Q_PROPERTY(MoviesListModel* list READ getList CONSTANT)
    Q_PROPERTY(RequestInfo* request READ getRequest CONSTANT)

public:
    AccountMediaListService(Api::WorkerName workerName,
                            Api &api,
                            GenresListModel *genresListModel,
                            MovieService &movieService,
                            QObject *parent);

    Q_INVOKABLE void search();
    Q_INVOKABLE void select(int id);
    AccountMoviesForm *getForm() const;
    MoviesListModel *getList() const;
    RequestInfo *getRequest() const;

private:
    Api::WorkerName workerName;
    Api &api;
    GenresListModel *genresListModel;
    MovieService &movieService;
    AccountMoviesForm *form;
    MoviesListModel *list;
    RequestInfo *request;

public slots:
    void fillModelFromApi(QByteArray &data);

};

#endif // ACCOUNTMEDIALISTSERVICE_H
