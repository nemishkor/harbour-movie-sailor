#include "searchservice.h"

SearchService::SearchService(Api &api,
                             HistoryService &historyService,
                             MovieService &movieService,
                             TvService &tvService,
                             PersonService &personService,
                             GenresListModel *genresListModel,
                             QObject *parent) :
    QObject(parent),
    apiWorkerName(Api::SearchMedia),
    api(api),
    historyService(historyService),
    movieService(movieService),
    tvService(tvService),
    personService(personService),
    genresListModel(genresListModel),
    form(new SearchForm(this)),
    request(api.getRequestInfo(apiWorkerName)),
    list(new MediaListModel(this))
{
    connect(&api, &Api::searchMediaDone, this, &SearchService::fillFromApi);
}

void SearchService::search()
{
    qDebug() << "SearchService: search";
    if (list->getDirty() || form->isDirty()) {
        list->clear();
        form->setPage(1);
    }

    list->setDirty(false);
    form->setDirty(false);

    qDebug() << "type" << form->getType();
    historyService.addSearch(form->getType(), form->getQuery());
    api.searchMedia(apiWorkerName, *form);
}

void SearchService::loadSearchHistory()
{
    historyService.loadSearchHistory(*form);
}

SearchForm *SearchService::getForm() const
{
    return form;
}

RequestInfo *SearchService::getRequest() const
{
    return request;
}

MediaListModel *SearchService::getList() const
{
    return list;
}

void SearchService::fillFromApi(QByteArray &data)
{
    qDebug() << "SearchService: search - got data";
    MediaListItem::MediaType mediaType = MediaListItem::MediaType::MovieType;
    switch (form->getType()) {
    case SearchForm::Any:
        break;
    case SearchForm::Movie:
        mediaType = MediaListItem::MediaType::MovieType;
        break;
    case SearchForm::Tv:
        mediaType = MediaListItem::MediaType::TvType;
        break;
    case SearchForm::Person:
        mediaType = MediaListItem::MediaType::PersonType;
        break;
    }
    list->fillFromAPI(genresListModel->getItems(), QJsonDocument::fromJson(data), mediaType);
    qDebug() << "SearchService: search - done";
}

