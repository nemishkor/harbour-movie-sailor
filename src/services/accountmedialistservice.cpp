#include "accountmedialistservice.h"

AccountMediaListService::AccountMediaListService(
        Api::WorkerName workerName,
        Api &api,
        GenresListModel *genresListModel,
        MovieService &movieService,
        QObject *parent) :
    QObject(parent),
    workerName(workerName),
    api(api),
    genresListModel(genresListModel),
    movieService(movieService),
    form(new AccountMoviesForm(this)),
    list(new MoviesListModel(this)),
    request(api.getRequestInfo(workerName))
{

}

void AccountMediaListService::search()
{
    if (!list->getDirty() && !form->getDirty())
        return;
    list->clear();
    form->setPage(1);
    api.loadAccountMediaList(workerName, form);
}

void AccountMediaListService::select(int id)
{
    QList<MovieListItem>::const_iterator it;
    for (it = list->getItems().constBegin(); it != list->getItems().constEnd(); it++) {
        if (it->getId() == id) {
            movieService.fillWithListItemAndLoad(*it);
            return;
        }
    }
}

AccountMoviesForm *AccountMediaListService::getForm() const
{
    return form;
}

MoviesListModel *AccountMediaListService::getList() const
{
    return list;
}

RequestInfo *AccountMediaListService::getRequest() const
{
    return request;
}

void AccountMediaListService::fillModelFromApi(QByteArray &data)
{
    list->fillFromAPI(QJsonDocument::fromJson(data), genresListModel->getItems());
    list->setDirty(false);
    form->setDirty(false);
}
