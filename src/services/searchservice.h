#ifndef SEARCHSERVICE_H
#define SEARCHSERVICE_H

#include <QDebug>
#include <QObject>

#include "src/api.h"
#include "src/models/searchform.h"
#include "src/models/requestinfo.h"
#include "src/services/movieservice.h"
#include "src/services/tvservice.h"
#include "src/services/personservice.h"
#include "src/viewmodels/genreslistmodel.h"
#include "src/viewmodels/medialistmodel.h"

class SearchService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(SearchForm* form READ getForm CONSTANT)
    Q_PROPERTY(RequestInfo* request READ getRequest CONSTANT)
    Q_PROPERTY(MediaListModel* list READ getList CONSTANT)

public:
    SearchService(Api &api,
                  MovieService &movieService,
                  TvService &tvService,
                  PersonService &personService,
                  GenresListModel *genresListModel,
                  QObject *parent);

    Q_INVOKABLE void search();
    SearchForm *getForm() const;
    RequestInfo *getRequest() const;
    MediaListModel *getList() const;

private:
    const Api::WorkerName apiWorkerName;
    Api &api;
    MovieService &movieService;
    TvService &tvService;
    PersonService &personService;
    GenresListModel *genresListModel;
    SearchForm *form;
    RequestInfo *request;
    MediaListModel *list;

    void fillFromApi(QByteArray &data);

};

#endif // SEARCHSERVICE_H
