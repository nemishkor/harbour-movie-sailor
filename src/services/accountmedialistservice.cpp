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
    if (!list->getDirty() && !form->isDirty())
        return;
    list->clear();
    form->setPage(1);
    api.getResource(workerName, *form);
}

void AccountMediaListService::select(int id)
{
    QList<MediaListItem>::const_iterator it;
    for (it = list->getItems().constBegin(); it != list->getItems().constEnd(); it++) {
        if (it->getId() == id) {
            switch (mediaType) {
            case MediaListItem::Unknown:
                qWarning() << "Unknown media type of the media entity" << it->getId();
                break;
            case MediaListItem::MovieType:
                movieService.fillWithListItemAndLoad(*it);
                break;
            case MediaListItem::TvType:
                tvService.fillWithListItemAndLoad(*it);
                break;
            case MediaListItem::PersonType:
                break;
            }
            return;
        }
    }
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
    list->fillFromAPI(QJsonDocument::fromJson(data), genresListModel->getItems(), mediaType);
    list->setDirty(false);
    form->setDirty(false);
}
