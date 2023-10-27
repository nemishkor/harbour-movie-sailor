#ifndef ACCOUNTMEDIALISTSERVICE_H
#define ACCOUNTMEDIALISTSERVICE_H

#include <QObject>

#include "src/api.h"
#include "src/models/accountmoviesform.h"
#include "src/models/form.h"
#include "src/models/requestinfo.h"
#include "src/services/movieservice.h"
#include "src/services/tvservice.h"
#include "src/viewmodels/medialistmodel.h"
#include "src/viewmodels/genreslistmodel.h"

class AccountMediaListService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(AccountMoviesForm* form READ getForm CONSTANT)
    Q_PROPERTY(MediaListModel* list READ getList CONSTANT)
    Q_PROPERTY(RequestInfo* request READ getRequest CONSTANT)

public:
    AccountMediaListService(Api::WorkerName workerName,
                            MediaListItem::MediaType mediaType,
                            Api &api,
                            GenresListModel *genresListModel,
                            MovieService &movieService,
                            TvService &tvService,
                            QObject *parent);

    Q_INVOKABLE void search();
    AccountMoviesForm *getForm() const;
    MediaListModel *getList() const;
    RequestInfo *getRequest() const;

private:
    Api::WorkerName workerName;
    const MediaListItem::MediaType mediaType;
    Api &api;
    GenresListModel *genresListModel;
    MovieService &movieService;
    TvService &tvService;
    AccountMoviesForm *form;
    MediaListModel *list;
    RequestInfo *request;

public slots:
    void fillModelFromApi(QByteArray &data);

};

#endif // ACCOUNTMEDIALISTSERVICE_H
