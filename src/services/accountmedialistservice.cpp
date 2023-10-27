#include "accountmedialistservice.h"

AccountMediaListService::AccountMediaListService(
        Api::WorkerName workerName,
        MediaListItem::MediaType mediaType,
        Api &api,
        GenresListModel *genresListModel,
        MovieService &movieService,
        TvService &tvService,
        QObject *parent) :
    QObject(parent),
    workerName(workerName),
    mediaType(mediaType),
    api(api),
    genresListModel(genresListModel),
    movieService(movieService),
    tvService(tvService),
    form(new AccountMoviesForm(this)),
    list(new MediaListModel(this)),
    request(api.getRequestInfo(workerName))
{

}

void AccountMediaListService::search()
{
    qDebug() << "AccountMediaListService: search";
    if (!list->getDirty() && !form->isDirty())
        return;
    list->clear();
    form->setPage(1);
    api.getResource(workerName, *form);
}

AccountMoviesForm *AccountMediaListService::getForm() const
{
    return form;
}

MediaListModel *AccountMediaListService::getList() const
{
    return list;
}

RequestInfo *AccountMediaListService::getRequest() const
{
    return request;
}

void AccountMediaListService::fillModelFromApi(QByteArray &data)
{
    qDebug() << "AccountMediaListService: search - got data";
    list->fillFromAPI(genresListModel->getItems(), QJsonDocument::fromJson(data), mediaType);
    list->setDirty(false);
    form->setDirty(false);
    qDebug() << "AccountMediaListService: search - done";
}
